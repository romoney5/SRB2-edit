// SONIC ROBO BLAST 2
//-----------------------------------------------------------------------------
// Copyright (C) 1993-1996 by id Software, Inc.
// Copyright (C) 1998-2000 by DooM Legacy Team.
// Copyright (C) 1999-2024 by Sonic Team Junior.
//
// This program is free software distributed under the
// terms of the GNU General Public License, version 2.
// See the 'LICENSE' file for more details.
//-----------------------------------------------------------------------------
/// \file  info.c
/// \brief Thing frame/state LUT

// Data.
#include "doomdef.h"
#include "doomstat.h"
#include "sounds.h"
#include "p_mobj.h"
#include "p_local.h" // DMG_ constants
#include "m_misc.h"
#include "z_zone.h"
#include "d_player.h"
#include "v_video.h" // V_*MAP constants
#include "lzf.h"
#ifdef HWRENDER
#include "hardware/hw_light.h"
#endif


// Hey, moron! If you change this table, don't forget about the sprite enum in info.h and the sprite lights in hw_light.c!
// For the sake of constant merge conflicts, let's spread this out
char sprnames[NUMSPRITES + 1][MAXSPRITENAME + 1] =
{
	"NULL", // invisible object
	"UNKN",

	"THOK", // Thok! mobj
	"PLAY",

	// Enemies
	"POSS", // Crawla (Blue)
	"SPOS", // Crawla (Red)
	"FISH", // SDURF
	"BUZZ", // Buzz (Gold)
	"RBUZ", // Buzz (Red)
	"JETB", // Jetty-Syn Bomber
	"JETG", // Jetty-Syn Gunner
	"CCOM", // Crawla Commander
	"DETN", // Deton
	"SKIM", // Skim mine dropper
	"TRET", // Industrial Turret
	"TURR", // Pop-Up Turret
	"SHRP", // Sharp
	"CRAB", // Crushstacean
	"CR2B", // Banpyura
	"CSPR", // Banpyura spring
	"JJAW", // Jet Jaw
	"SNLR", // Snailer
	"VLTR", // BASH
	"PNTY", // Pointy
	"ARCH", // Robo-Hood
	"CBFS", // Castlebot Facestabber
	"STAB", // Castlebot Facestabber spear aura
	"SPSH", // Egg Guard
	"ESHI", // Egg Guard's shield
	"GSNP", // Green Snapper
	"GSNL", // Green Snapper leg
	"GSNH", // Green Snapper head
	"MNUS", // Minus
	"MNUD", // Minus dirt
	"SSHL", // Spring Shell
	"UNID", // Unidus
	"CANA", // Canarivore
	"CANG", // Canarivore gas
	"PYRE", // Pyre Fly
	"PTER", // Pterabyte
	"DRAB", // Dragonbomber

	// Generic Boss Items
	"JETF", // Boss jet fumes

	// Boss 1 (Greenflower)
	"EGGM", // Boss 1
	"EGLZ", // Boss 1 Junk

	// Boss 2 (Techno Hill)
	"EGGN", // Boss 2
	"TANK", // Boss 2 Junk
	"GOOP", // Boss 2 Goop

	// Boss 3 (Deep Sea)
	"EGGO", // Boss 3
	"SEBH", // Boss 3 Junk
	"FAKE", // Boss 3 Fakemobile
	"SHCK", // Boss 3 Shockwave

	// Boss 4 (Castle Eggman)
	"EGGP",
	"EFIR", // Boss 4 jet flame
	"EGR1", // Boss 4 Spectator Eggrobo

	// Boss 5 (Arid Canyon)
	"FANG", // replaces EGGQ
	"BRKN", // broken robot chunk
	"WHAT", // alart
	"VWRE",
	"PROJ", // projector light
	"FBOM",
	"FSGN",
	"BARX", // bomb explosion (also used by barrel)
	"BARD", // bomb dust (also used by barrel)

	// Boss 6 (Red Volcano)
	"EGGR",

	// Boss 7 (Dark City)
	"BRAK",
	"BGOO", // Goop
	"BMSL",

	// Boss 8 (Egg Rock)
	"EGGT",

	// Cy-Brak-Demon; uses "BRAK" as well, but has some extras
	"RCKT", // Rockets!
	"ELEC", // Electricity!
	"TARG", // Targeting reticules!
	"NPLM", // Big napalm bombs!
	"MNPL", // Mini napalm bombs!

	// Metal Sonic
	"METL",
	"MSCF",
	"MSCB",

	// Collectible Items
	"RING",
	"TRNG", // Team Rings
	"TOKE", // Special Stage Token
	"RFLG", // Red CTF Flag
	"BFLG", // Blue CTF Flag
	"SPHR", // Sphere
	"NCHP", // NiGHTS chip
	"NSTR", // NiGHTS star
	"EMBM", // Emblem
	"CEMG", // Chaos Emeralds
	"SHRD", // Emerald hunt shards

	// Interactive Objects
	"BBLS", // water bubble source
	"SIGN", // Level end sign
	"SPIK", // Spike Ball
	"SFLM", // Spin fire
	"TFLM", // Spin fire (team)
	"USPK", // Floor spike
	"WSPK", // Wall spike
	"WSPB", // Wall spike base
	"STPT", // Starpost
	"BMNE", // Big floating mine
	"PUMI", // Rollout Rock

	// Monitor Boxes
	"MSTV", // MiSc TV sprites
	"XLTV", // eXtra Large TV sprites

	"TRRI", // Red team:  10 RIngs
	"TBRI", // Blue team: 10 RIngs

	"TVRI", // 10 RIng
	"TVPI", // PIty shield
	"TVAT", // ATtraction shield
	"TVFO", // FOrce shield
	"TVAR", // ARmageddon shield
	"TVWW", // WhirlWind shield
	"TVEL", // ELemental shield
	"TVSS", // Super Sneakers
	"TVIV", // InVincibility
	"TV1U", // 1Up
	"TV1P", // 1uP (textless)
	"TVEG", // EGgman
	"TVMX", // MiXup
	"TVMY", // MYstery
	"TVGV", // GraVity boots
	"TVRC", // ReCycler
	"TV1K", // 1,000 points  (1 K)
	"TVTK", // 10,000 points (Ten K)
	"TVFL", // FLame shield
	"TVBB", // BuBble shield
	"TVZP", // Thunder shield (ZaP)

	// Projectiles
	"MISL",
	"LASR", // GFZ3 laser
	"LASF", // GFZ3 laser flames
	"TORP", // Torpedo
	"ENRG", // Energy ball
	"MINE", // Skim mine
	"JBUL", // Jetty-Syn Bullet
	"TRLS",
	"CBLL", // Cannonball
	"AROW", // Arrow
	"CFIR", // Colored fire of various sorts

	// The letter
	"LETR",

	// Tutorial Scenery
	"TUPL",
	"TUPF",

	// Greenflower Scenery
	"FWR1",
	"FWR2", // GFZ Sunflower
	"FWR3", // GFZ budding flower
	"FWR4",
	"BUS1", // GFZ Bush w/ berries
	"BUS2", // GFZ Bush w/o berries
	"BUS3", // GFZ Bush w/ BLUE berries
	// Trees (both GFZ and misc)
	"TRE1", // GFZ
	"TRE2", // Checker
	"TRE3", // Frozen Hillside
	"TRE4", // Polygon
	"TRE5", // Bush tree
	"TRE6", // Spring tree

	// Techno Hill Scenery
	"THZP", // THZ1 Steam Flower
	"FWR5", // THZ1 Spin flower (red)
	"FWR6", // THZ1 Spin flower (yellow)
	"THZT", // Steam Whistle tree/bush
	"ALRM", // THZ2 Alarm

	// Deep Sea Scenery
	"GARG", // Deep Sea Gargoyle
	"SEWE", // Deep Sea Seaweed
	"DRIP", // Dripping water
	"CORL", // Coral
	"BCRY", // Blue Crystal
	"KELP", // Kelp
	"ALGA", // Animated algae top
	"ALGB", // Animated algae segment
	"DSTG", // DSZ Stalagmites
	"LIBE", // DSZ Light beam

	// Castle Eggman Scenery
	"CHAN", // CEZ Chain
	"FLAM", // Flame
	"ESTA", // Eggman esta una estatua!
	"SMCH", // Small Mace Chain
	"BMCH", // Big Mace Chain
	"SMCE", // Small Mace
	"BMCE", // Big Mace
	"BSPB", // Blue spring on a ball
	"YSPB", // Yellow spring on a ball
	"RSPB", // Red spring on a ball
	"SFBR", // Small Firebar
	"BFBR", // Big Firebar
	"BANR", // Banner
	"PINE", // Pine Tree
	"CEZB", // Bush
	"CNDL", // Candle/pricket
	"FLMH", // Flame holder
	"CTRC", // Fire torch
	"CFLG", // Waving flag/segment
	"CSTA", // Crawla statue
	"CBBS", // Facestabber statue
	"CABR", // Brambles

	// Arid Canyon Scenery
	"BTBL", // Big tumbleweed
	"STBL", // Small tumbleweed
	"CACT", // Cacti
	"WWSG", // Caution Sign
	"WWS2", // Cacti Sign
	"WWS3", // Sharp Turn Sign
	"OILL", // Oil lamp
	"OILF", // Oil lamp flare
	"BARR", // TNT barrel
	"REMT", // TNT proximity shell
	"TAZD", // Dust devil
	"ADST", // Arid dust
	"MCRT", // Minecart
	"MCSP", // Minecart spark
	"SALD", // Saloon door
	"TRAE", // Train cameo locomotive
	"TRAI", // Train cameo wagon
	"STEA", // Train steam

	// Red Volcano Scenery
	"FLME", // Flame jet
	"DFLM", // Blade's flame
	"LFAL", // Lavafall
	"JPLA", // Jungle palm
	"TFLO", // Torch flower
	"WVIN", // Wall vines

	// Dark City Scenery

	// Egg Rock Scenery

	// Christmas Scenery
	"XMS1", // Christmas Pole
	"XMS2", // Candy Cane
	"XMS3", // Snowman
	"XMS4", // Lamppost
	"XMS5", // Hanging Star
	"XMS6", // Mistletoe
	"SNTT", // Silver Shiver tree
	"SSTT", // Silver Shiver tree with snow
	"FHZI", // FHZ ice
	"ROSY",

	// Halloween Scenery
	"PUMK", // Pumpkins
	"HHPL", // Dr Seuss Trees
	"SHRM", // Mushroom
	"HHZM", // Misc

	// Azure Temple Scenery
	"BGAR", // ATZ Gargoyles
	"RCRY", // ATZ Red Crystal (Target)
	"CFLM", // Green torch flame

	// Botanic Serenity Scenery
	"BSZ1", // Tall flowers
	"BSZ2", // Medium flowers
	"BSZ3", // Small flowers
	//"BSZ4", -- Tulips
	"BST1", // Red tulip
	"BST2", // Purple tulip
	"BST3", // Blue tulip
	"BST4", // Cyan tulip
	"BST5", // Yellow tulip
	"BST6", // Orange tulip
	"BSZ5", // Cluster of Tulips
	"BSZ6", // Bush
	"BSZ7", // Vine
	"BSZ8", // Misc things

	// Misc Scenery
	"STLG", // Stalagmites
	"DBAL", // Disco
	"GINE", // Crystalline Heights tree
	"PPAL", // Pristine Shores palm trees

	// Powerup Indicators
	"ARMA", // Armageddon Shield Orb
	"ARMF", // Armageddon Shield Ring, Front
	"ARMB", // Armageddon Shield Ring, Back
	"WIND", // Whirlwind Shield Orb
	"MAGN", // Attract Shield Orb
	"ELEM", // Elemental Shield Orb and Fire
	"FORC", // Force Shield Orb
	"PITY", // Pity Shield Orb
	"FIRS", // Flame Shield Orb
	"BUBS", // Bubble Shield Orb
	"ZAPS", // Thunder Shield Orb
	"IVSP", // invincibility sparkles
	"SSPK", // Super Sonic Spark

	"GOAL", // Special Stage goal (here because lol NiGHTS)

	// Flickies
	"FBUB", // Flicky-sized bubble
	"FL01", // Bluebird
	"FL02", // Rabbit
	"FL03", // Chicken
	"FL04", // Seal
	"FL05", // Pig
	"FL06", // Chipmunk
	"FL07", // Penguin
	"FL08", // Fish
	"FL09", // Ram
	"FL10", // Puffin
	"FL11", // Cow
	"FL12", // Rat
	"FL13", // Bear
	"FL14", // Dove
	"FL15", // Cat
	"FL16", // Canary
	"FS01", // Spider
	"FS02", // Bat

	// Springs
	"FANS", // Fan
	"STEM", // Steam riser
	"BUMP", // Bumpers
	"BLON", // Balloons
	"SPRY", // Yellow spring
	"SPRR", // Red spring
	"SPRB", // Blue spring
	"YSPR", // Yellow Diagonal Spring
	"RSPR", // Red Diagonal Spring
	"BSPR", // Blue Diagonal Spring
	"SSWY", // Yellow Side Spring
	"SSWR", // Red Side Spring
	"SSWB", // Blue Side Spring
	"BSTY", // Yellow Booster
	"BSTR", // Red Booster

	// Environmental Effects
	"RAIN", // Rain
	"SNO1", // Snowflake
	"SPLH", // Water Splish
	"LSPL", // Lava Splish
	"SPLA", // Water Splash
	"SMOK",
	"BUBL", // Bubble
	"WZAP",
	"DUST", // Spindash dust
	"FPRT", // Spindash dust (flame)
	"TFOG", // Teleport Fog
	"SEED", // Sonic CD flower seed
	"PRTL", // Particle (for fans, etc.)

	// Game Indicators
	"SCOR", // Score logo
	"DRWN", // Drowning Timer
	"FLII", // Flight indicator
	"LCKN", // Target
	"TTAG", // Tag Sign
	"GFLG", // Got Flag sign
	"FNSF", // Finish flag

	"CORK",
	"LHRT",

	// Ring Weapons
	"RRNG", // Red Ring
	"RNGB", // Bounce Ring
	"RNGR", // Rail Ring
	"RNGI", // Infinity Ring
	"RNGA", // Automatic Ring
	"RNGE", // Explosion Ring
	"RNGS", // Scatter Ring
	"RNGG", // Grenade Ring

	"PIKB", // Bounce Ring Pickup
	"PIKR", // Rail Ring Pickup
	"PIKA", // Automatic Ring Pickup
	"PIKE", // Explosion Ring Pickup
	"PIKS", // Scatter Ring Pickup
	"PIKG", // Grenade Ring Pickup

	"TAUT", // Thrown Automatic Ring
	"TGRE", // Thrown Grenade Ring
	"TSCR", // Thrown Scatter Ring

	// Mario-specific stuff
	"COIN",
	"CPRK",
	"GOOM",
	"BGOM",
	"FFWR",
	"FBLL",
	"SHLL",
	"PUMA",
	"HAMM",
	"KOOP",
	"BFLM",
	"MAXE",
	"MUS1",
	"MUS2",
	"TOAD",

	// NiGHTS Stuff
	"NDRN", // NiGHTS drone
	"NSPK", // NiGHTS sparkle
	"NBMP", // NiGHTS Bumper
	"HOOP", // NiGHTS hoop sprite
	"NSCR", // NiGHTS score sprite
	"NPRU", // Nights Powerups
	"CAPS", // Capsule thingy for NiGHTS
	"IDYA", // Ideya
	"NTPN", // Nightopian
	"SHLP", // Shleep

	// Secret badniks and hazards, shhhh
	"PENG",
	"POPH",
	"HIVE",
	"BUMB",
	"BBUZ",
	"FMCE",
	"HMCE",
	"CACO",
	"BAL2",
	"SBOB",
	"SBFL",
	"SBSK",
	"HBAT",

	// Debris
	"SPRK", // Sparkle
	"BOM1", // Robot Explosion
	"BOM2", // Boss Explosion 1
	"BOM3", // Boss Explosion 2
	"BOM4", // Underwater Explosion
	"BMNB", // Mine Explosion

	// Crumbly rocks
	"ROIA",
	"ROIB",
	"ROIC",
	"ROID",
	"ROIE",
	"ROIF",
	"ROIG",
	"ROIH",
	"ROII",
	"ROIJ",
	"ROIK",
	"ROIL",
	"ROIM",
	"ROIN",
	"ROIO",
	"ROIP",

	// Level debris
	"GFZD", // GFZ debris
	"BRIC", // Bricks
	"WDDB", // Wood Debris
	"BRIR", // CEZ3 colored bricks
	"BRIB", // CEZ3 colored bricks
	"BRIY", // CEZ3 colored bricks

	// Gravity Well Objects
	"GWLG",
	"GWLR",

	// LJ Knuckles
	"OLDK",
};

char spr2names[NUMPLAYERSPRITES][MAXSPRITENAME + 1] =
{
	"STND",
	"WAIT",
	"WALK",
	"SKID",
	"RUN_",
	"DASH",
	"PAIN",
	"STUN",
	"DEAD",
	"DRWN",
	"ROLL",
	"GASP",
	"JUMP",
	"SPNG",
	"FALL",
	"EDGE",
	"RIDE",

	"SPIN",

	"FLY_",
	"SWIM",
	"TIRE",

	"GLID",
	"LAND",
	"CLNG",
	"CLMB",

	"FLT_",
	"FRUN",

	"BNCE",

	"FIRE",

	"TWIN",

	"MLEE",
	"MLEL",

	"TRNS",

	"NSTD",
	"NFLT",
	"NFLY",
	"NDRL",
	"NSTN",
	"NPUL",
	"NATK",

	"TAL0",
	"TAL1",
	"TAL2",
	"TAL3",
	"TAL4",
	"TAL5",
	"TAL6",
	"TAL7",
	"TAL8",
	"TAL9",
	"TALA",
	"TALB",
	"TALC",

	"MSC0",
	"MSC1",
	"MSC2",
	"MSC3",
	"MSC4",
	"MSC5",
	"MSC6",
	"MSC7",
	"MSC8",
	"MSC9",

	"CNT1",
	"CNT2",
	"CNT3",
	"CNT4",

	"SIGN",
	"LIFE",

	"XTRA",
};
playersprite_t free_spr2 = SPR2_FIRSTFREESLOT;

playersprite_t spr2defaults[NUMPLAYERSPRITES] = {
	0, // SPR2_STND,
	0, // SPR2_WAIT,
	0, // SPR2_WALK,
	SPR2_WALK, // SPR2_SKID,
	SPR2_WALK, // SPR2_RUN ,
	SPR2_FRUN, // SPR2_DASH,
	0, // SPR2_PAIN,
	SPR2_PAIN, // SPR2_STUN,
	SPR2_PAIN, // SPR2_DEAD,
	SPR2_DEAD, // SPR2_DRWN,
	0, // SPR2_ROLL,
	SPR2_SPNG, // SPR2_GASP,
	0, // SPR2_JUMP, (conditional, will never be referenced)
	SPR2_FALL, // SPR2_SPNG,
	SPR2_WALK, // SPR2_FALL,
	0, // SPR2_EDGE,
	SPR2_FALL, // SPR2_RIDE,

	SPR2_ROLL, // SPR2_SPIN,

	SPR2_SPNG, // SPR2_FLY ,
	SPR2_FLY , // SPR2_SWIM,
	0, // SPR2_TIRE, (conditional, will never be referenced)

	SPR2_FLY , // SPR2_GLID,
	SPR2_ROLL, // SPR2_LAND,
	SPR2_CLMB, // SPR2_CLNG,
	SPR2_ROLL, // SPR2_CLMB,

	SPR2_WALK, // SPR2_FLT ,
	SPR2_RUN , // SPR2_FRUN,

	SPR2_FALL, // SPR2_BNCE,

	0, // SPR2_FIRE,

	SPR2_ROLL, // SPR2_TWIN,

	SPR2_TWIN, // SPR2_MLEE,
	0, // SPR2_MLEL,

	0, // SPR2_TRNS,

	SPR2_STND, // SPR2_NSTD,
	SPR2_FALL, // SPR2_NFLT,
	0, // SPR2_NFLY, (will never be referenced unless skin 0 lacks this)
	SPR2_NFLY, // SPR2_NDRL,
	SPR2_STUN, // SPR2_NSTN,
	SPR2_NSTN, // SPR2_NPUL,
	SPR2_ROLL, // SPR2_NATK,

	0, // SPR2_TAL0, (this will look mighty stupid but oh well)
	SPR2_TAL0, // SPR2_TAL1,
	SPR2_TAL1, // SPR2_TAL2,
	SPR2_TAL2, // SPR2_TAL3,
	SPR2_TAL1, // SPR2_TAL4,
	SPR2_TAL4, // SPR2_TAL5,
	SPR2_TAL0, // SPR2_TAL6,
	SPR2_TAL3, // SPR2_TAL7,
	SPR2_TAL7, // SPR2_TAL8,
	SPR2_TAL0, // SPR2_TAL9,
	SPR2_TAL9, // SPR2_TALA,
	SPR2_TAL0, // SPR2_TALB,
	SPR2_TAL6, // SPR2_TALC,

	0, // SPR2_MSC0,
	0, // SPR2_MSC1,
	0, // SPR2_MSC2,
	0, // SPR2_MSC3,
	0, // SPR2_MSC4,
	0, // SPR2_MSC5,
	0, // SPR2_MSC6,
	0, // SPR2_MSC7,
	0, // SPR2_MSC8,
	0, // SPR2_MSC9,

	SPR2_WAIT, // SPR2_CNT1,
	SPR2_FALL, // SPR2_CNT2,
	SPR2_SPNG, // SPR2_CNT3,
	SPR2_CNT1, // SPR2_CNT4,

	0, // SPR2_SIGN,
	0, // SPR2_LIFE,

	0, // SPR2_XTRA (should never be referenced)
};

// Doesn't work with g++, needs actionf_p1 (don't modify this comment)
static const state_t startstates[] =
{
	// frame is masked through FF_FRAMEMASK
	// FF_ANIMATE makes simple state animations (var1 #frames, var2 tic delay)
	// FF_FULLBRIGHT activates the fullbright colormap
	// use FF_TRANS10 - FF_TRANS90 for easy translucency
	// (or tr_trans10<<FF_TRANSSHIFT if you want to make it hard on yourself)

	// Keep this comment directly above S_NULL.
	{"NULL", 0, SPR_NULL, 0,  1, NULL, 0, 0, S_NULL, 0},
	{"UNKNOWN", 0, SPR_UNKN, FF_FULLBRIGHT, -1, NULL, 0, 0, S_NULL, 0},
	{"INVISIBLE", 0, SPR_NULL, 0, -1, NULL, 0, 0, S_NULL, 0},

	{"SPAWNSTATE", 0, SPR_UNKN, FF_FULLBRIGHT, -1, A_InfoState, 0, 0, S_NULL, 0},
	{"SEESTATE", 0, SPR_UNKN, FF_FULLBRIGHT, -1, A_InfoState, 1, 0, S_NULL, 0},
	{"MELEESTATE", 0, SPR_UNKN, FF_FULLBRIGHT, -1, A_InfoState, 2, 0, S_NULL, 0},
	{"MISSILESTATE", 0, SPR_UNKN, FF_FULLBRIGHT, -1, A_InfoState, 3, 0, S_NULL, 0},
	{"DEATHSTATE", 0, SPR_UNKN, FF_FULLBRIGHT, -1, A_InfoState, 4, 0, S_NULL, 0},
	{"XDEATHSTATE", 0, SPR_UNKN, FF_FULLBRIGHT, -1, A_InfoState, 5, 0, S_NULL, 0},
	{"RAISESTATE", 0, SPR_UNKN, FF_FULLBRIGHT, -1, A_InfoState, 6, 0, S_NULL, 0},

	// Thok
	{"THOK", 0, SPR_THOK, FF_TRANS50, 8, NULL, 0, 0, S_NULL, 0},

	// Player
	{"PLAY_STND", 0, SPR_PLAY, SPR2_STND|FF_ANIMATE,    105, NULL, 0,  7, S_PLAY_WAIT, 0},
	{"PLAY_WAIT", 0, SPR_PLAY, SPR2_WAIT,                16, NULL, 0,  0, S_PLAY_WAIT, 0},
	{"PLAY_WALK", 0, SPR_PLAY, SPR2_WALK,                 4, NULL, 0,  0, S_PLAY_WALK, 0},
	{"PLAY_SKID", 0, SPR_PLAY, SPR2_SKID,                 1, NULL, 0,  0, S_PLAY_WALK, 0},
	{"PLAY_RUN", 0, SPR_PLAY, SPR2_RUN ,                 2, NULL, 0,  0, S_PLAY_RUN, 0},
	{"PLAY_DASH", 0, SPR_PLAY, SPR2_DASH,                 2, NULL, 0,  0, S_PLAY_DASH, 0},
	{"PLAY_PAIN", 0, SPR_PLAY, SPR2_PAIN|FF_ANIMATE,    350, NULL, 0,  4, S_PLAY_FALL, 0},
	{"PLAY_STUN", 0, SPR_PLAY, SPR2_STUN|FF_ANIMATE,    350, NULL, 0,  4, S_PLAY_FALL, 0},
	{"PLAY_DEAD", 0, SPR_PLAY, SPR2_DEAD|FF_ANIMATE,     -1, NULL, 0,  4, S_NULL, 0},
	{"PLAY_DRWN", 0, SPR_PLAY, SPR2_DRWN|FF_ANIMATE,     -1, NULL, 0,  4, S_NULL, 0},
	{"PLAY_ROLL", 0, SPR_PLAY, SPR2_ROLL,                 1, NULL, 0,  0, S_PLAY_ROLL, 0},
	{"PLAY_GASP", 0, SPR_PLAY, SPR2_GASP|FF_ANIMATE,     14, NULL, 0,  4, S_PLAY_WALK, 0},
	{"PLAY_JUMP", 0, SPR_PLAY, SPR2_JUMP,                 1, NULL, 0,  0, S_PLAY_JUMP, 0},
	{"PLAY_SPRING", 0, SPR_PLAY, SPR2_SPNG,                 2, NULL, 0,  0, S_PLAY_SPRING, 0},
	{"PLAY_FALL", 0, SPR_PLAY, SPR2_FALL,                 2, NULL, 0,  0, S_PLAY_FALL, 0},
	{"PLAY_EDGE", 0, SPR_PLAY, SPR2_EDGE,                12, NULL, 0,  0, S_PLAY_EDGE, 0},
	{"PLAY_RIDE", 0, SPR_PLAY, SPR2_RIDE,                 4, NULL, 0,  0, S_PLAY_RIDE, 0},

	// CA2_SPINDASH
	{"PLAY_SPINDASH", 0, SPR_PLAY, SPR2_SPIN,                 2, NULL, 0,  0, S_PLAY_SPINDASH, 0},

	// CA_FLY/CA_SWIM
	{"PLAY_FLY", 0, SPR_PLAY, SPR2_FLY ,                 2, NULL, 0,  0, S_PLAY_FLY, 0},
	{"PLAY_SWIM", 0, SPR_PLAY, SPR2_SWIM,                 4, NULL, 0,  0, S_PLAY_SWIM, 0},
	{"PLAY_FLY_TIRED", 0, SPR_PLAY, SPR2_TIRE,                12, NULL, 0,  0, S_PLAY_FLY_TIRED, 0},

	// CA_GLIDEANDCLIMB
	{"PLAY_GLIDE", 0, SPR_PLAY, SPR2_GLID,                 2, NULL, 0,  0, S_PLAY_GLIDE, 0},
	{"PLAY_GLIDE_LANDING", 0, SPR_PLAY, SPR2_LAND,                 7, NULL, 0,  0, S_PLAY_STND, 0},
	{"PLAY_CLING", 0, SPR_PLAY, SPR2_CLNG|FF_ANIMATE,     -1, NULL, 0,  4, S_NULL, 0},
	{"PLAY_CLIMB", 0, SPR_PLAY, SPR2_CLMB,                 5, NULL, 0,  0, S_PLAY_CLIMB, 0},

	// CA_FLOAT/CA_SLOWFALL
	{"PLAY_FLOAT", 0, SPR_PLAY, SPR2_FLT ,                 7, NULL, 0,  0, S_PLAY_FLOAT, 0},
	{"PLAY_FLOAT_RUN", 0, SPR_PLAY, SPR2_FRUN,                 7, NULL, 0,  0, S_PLAY_FLOAT_RUN, 0},

	// CA_BOUNCE
	{"PLAY_BOUNCE", 0, SPR_PLAY, SPR2_BNCE|FF_ANIMATE,     -1, NULL,             0,  0, S_NULL, 0},
	{"PLAY_BOUNCE_LANDING", 0, SPR_PLAY, SPR2_LAND|FF_SPR2ENDSTATE, 2, NULL, S_PLAY_BOUNCE,  0, S_PLAY_BOUNCE_LANDING, 0},

	// CA2_GUNSLINGER
	{"PLAY_FIRE", 0, SPR_PLAY, SPR2_FIRE|FF_SPR2ENDSTATE,  2, NULL, S_PLAY_FIRE_FINISH, 0, S_PLAY_FIRE, 0},
	{"PLAY_FIRE_FINISH", 0, SPR_PLAY, SPR2_FIRE,                 15, NULL,        S_PLAY_STND, 0, S_PLAY_STND, 0},

	// CA_TWINSPIN
	{"PLAY_TWINSPIN", 0, SPR_PLAY, SPR2_TWIN|FF_SPR2ENDSTATE, 2, NULL, S_PLAY_JUMP, 0, S_PLAY_TWINSPIN, 0},

	// CA2_MELEE
	{"PLAY_MELEE", 0, SPR_PLAY, SPR2_MLEE|FF_SPR2ENDSTATE, 2, NULL, S_PLAY_MELEE_FINISH, 0, S_PLAY_MELEE, 0},
	{"PLAY_MELEE_FINISH", 0, SPR_PLAY, SPR2_MLEE,                70, NULL,                   0, 0, S_PLAY_FALL, 0},
	{"PLAY_MELEE_LANDING", 0, SPR_PLAY, SPR2_MLEL,                35, NULL,                   0, 0, S_PLAY_WALK, 0},

	// SF_SUPER
	{"PLAY_SUPER_TRANS1", 0, SPR_PLAY, SPR2_TRNS|SPR2F_SUPER|FF_ANIMATE,     7, NULL,          0, 4, S_PLAY_SUPER_TRANS2, 0},
	{"PLAY_SUPER_TRANS2", 0, SPR_PLAY, SPR2_TRNS|SPR2F_SUPER,                3, NULL,          0, 0, S_PLAY_SUPER_TRANS3, 0},
	{"PLAY_SUPER_TRANS3", 0, SPR_PLAY, SPR2_TRNS|SPR2F_SUPER|FF_FULLBRIGHT,  2, NULL,          0, 0, S_PLAY_SUPER_TRANS4, 0},
	{"PLAY_SUPER_TRANS4", 0, SPR_PLAY, SPR2_TRNS|SPR2F_SUPER|FF_FULLBRIGHT,  2, NULL,          0, 0, S_PLAY_SUPER_TRANS5, 0},
	{"PLAY_SUPER_TRANS5", 0, SPR_PLAY, SPR2_TRNS|SPR2F_SUPER|FF_FULLBRIGHT,  2, NULL,          0, 0, S_PLAY_SUPER_TRANS6, 0},
	{"PLAY_SUPER_TRANS6", 0, SPR_PLAY, SPR2_TRNS|SPR2F_SUPER|FF_FULLBRIGHT, 19, A_FadeOverlay, 0, 0, S_PLAY_FALL, 0},

	{"OBJPLACE_DUMMY", 0, SPR_NULL, 0, -1, NULL, 0, 0, S_OBJPLACE_DUMMY, 0},

	// 1-Up box sprites (uses player sprite)
	{"PLAY_BOX1", 0, SPR_PLAY, SPR2_LIFE,  2, NULL, 0, 18, S_PLAY_BOX2, 0},
	{"PLAY_BOX2", 0, SPR_NULL,         0,  1, NULL, 0, 18, S_PLAY_BOX1, 0},
	{"PLAY_ICON1", 0, SPR_PLAY, SPR2_LIFE,  4, NULL, 0,  4, S_PLAY_ICON2, 0},
	{"PLAY_ICON2", 0, SPR_NULL,         0, 12, NULL, 0,  4, S_PLAY_ICON3, 0},
	{"PLAY_ICON3", 0, SPR_PLAY, SPR2_LIFE, 20, NULL, 0,  4, S_NULL, 0},

	// Level end sign (uses player sprite)
	{"PLAY_SIGN", 0, SPR_PLAY, SPR2_SIGN|FF_PAPERSPRITE, 2, NULL, 0, 29, S_PLAY_SIGN, 0},

	// NiGHTS Player, transforming
	{"PLAY_NIGHTS_TRANS1", 0, SPR_PLAY, SPR2_TRNS|FF_ANIMATE,     7, NULL,          0, 4, S_PLAY_NIGHTS_TRANS2, 0},
	{"PLAY_NIGHTS_TRANS2", 0, SPR_PLAY, SPR2_TRNS,                3, NULL,          0, 0, S_PLAY_NIGHTS_TRANS3, 0},
	{"PLAY_NIGHTS_TRANS3", 0, SPR_PLAY, SPR2_TRNS|FF_FULLBRIGHT,  2, NULL,          0, 0, S_PLAY_NIGHTS_TRANS4, 0},
	{"PLAY_NIGHTS_TRANS4", 0, SPR_PLAY, SPR2_TRNS|FF_FULLBRIGHT,  2, NULL,          0, 0, S_PLAY_NIGHTS_TRANS5, 0},
	{"PLAY_NIGHTS_TRANS5", 0, SPR_PLAY, SPR2_TRNS|FF_FULLBRIGHT,  2, NULL,          0, 0, S_PLAY_NIGHTS_TRANS6, 0},
	{"PLAY_NIGHTS_TRANS5", 0, SPR_PLAY, SPR2_TRNS|FF_FULLBRIGHT, 21, A_FadeOverlay, 2, 0, S_PLAY_NIGHTS_FLOAT, 0},

	// NiGHTS Player
	{"PLAY_NIGHTS_STAND", 0, SPR_PLAY, SPR2_NSTD, 7, NULL, 0, 0, S_PLAY_NIGHTS_STAND, 0},
	{"PLAY_NIGHTS_FLOAT", 0, SPR_PLAY, SPR2_NFLT, 7, NULL, 0, 0, S_PLAY_NIGHTS_FLOAT, 0},
	{"PLAY_NIGHTS_FLY", 0, SPR_PLAY, SPR2_NFLY, 2, NULL, 0, 0, S_PLAY_NIGHTS_FLY, 0},
	{"PLAY_NIGHTS_DRILL", 0, SPR_PLAY, SPR2_NDRL, 2, NULL, 0, 0, S_PLAY_NIGHTS_DRILL, 0},
	{"PLAY_NIGHTS_STUN", 0, SPR_PLAY, SPR2_NSTN, 2, NULL, 0, 0, S_PLAY_NIGHTS_STUN, 0},
	{"PLAY_NIGHTS_PULL", 0, SPR_PLAY, SPR2_NPUL, 1, NULL, 0, 0, S_PLAY_NIGHTS_PULL, 0},
	{"PLAY_NIGHTS_ATTACK", 0, SPR_PLAY, SPR2_NATK, 1, NULL, 0, 0, S_PLAY_NIGHTS_ATTACK, 0},

	// c:
	{"TAILSOVERLAY_STAND", 0, SPR_PLAY, SPR2_TAL0|FF_SPR2MIDSTART,  5, NULL, 0, 0, S_TAILSOVERLAY_STAND, 0},
	{"TAILSOVERLAY_0DEGREES", 0, SPR_PLAY, SPR2_TAL1|FF_SPR2MIDSTART, 35, NULL, 0, 0, S_TAILSOVERLAY_0DEGREES, 0},
	{"TAILSOVERLAY_PLUS30DEGREES", 0, SPR_PLAY, SPR2_TAL2|FF_SPR2MIDSTART, 35, NULL, 0, 0, S_TAILSOVERLAY_PLUS30DEGREES, 0},
	{"TAILSOVERLAY_PLUS60DEGREES", 0, SPR_PLAY, SPR2_TAL3|FF_SPR2MIDSTART, 35, NULL, 0, 0, S_TAILSOVERLAY_PLUS60DEGREES, 0},
	{"TAILSOVERLAY_MINUS30DEGREES", 0, SPR_PLAY, SPR2_TAL4|FF_SPR2MIDSTART, 35, NULL, 0, 0, S_TAILSOVERLAY_MINUS30DEGREES, 0},
	{"TAILSOVERLAY_MINUS60DEGREES", 0, SPR_PLAY, SPR2_TAL5|FF_SPR2MIDSTART, 35, NULL, 0, 0, S_TAILSOVERLAY_MINUS60DEGREES, 0},
	{"TAILSOVERLAY_RUN", 0, SPR_PLAY, SPR2_TAL6|FF_SPR2MIDSTART, 35, NULL, 0, 0, S_TAILSOVERLAY_RUN, 0},
	{"TAILSOVERLAY_FLY", 0, SPR_PLAY, SPR2_TAL7|FF_SPR2MIDSTART,  4, NULL, 0, 0, S_TAILSOVERLAY_FLY, 0},
	{"TAILSOVERLAY_TIRE", 0, SPR_PLAY, SPR2_TAL8|FF_SPR2MIDSTART,  4, NULL, 0, 0, S_TAILSOVERLAY_TIRE, 0},
	{"TAILSOVERLAY_PAIN", 0, SPR_PLAY, SPR2_TAL9|FF_SPR2MIDSTART, 35, NULL, 0, 0, S_TAILSOVERLAY_PAIN, 0},
	{"TAILSOVERLAY_GASP", 0, SPR_PLAY, SPR2_TALA|FF_SPR2MIDSTART, 35, NULL, 0, 0, S_TAILSOVERLAY_GASP, 0},
	{"TAILSOVERLAY_EDGE", 0, SPR_PLAY, SPR2_TALB                , 35, NULL, 0, 0, S_TAILSOVERLAY_EDGE, 0},
	{"TAILSOVERLAY_DASH", 0, SPR_PLAY, SPR2_TALC|FF_SPR2MIDSTART, 35, NULL, 0, 0, S_TAILSOVERLAY_DASH, 0},

	// [:
	{"JETFUMEFLASH", 0, SPR_JETF, 3|FF_ANIMATE|FF_FULLBRIGHT, 2, NULL, 1, 1, S_JETFUME1, 0},

	// Blue Crawla
	{"POSS_STND", 0, SPR_POSS, 0, 5, A_Look, 0, 0, S_POSS_STND, 0},
	{"POSS_RUN1", 0, SPR_POSS, 0, 3, A_Chase, 0, 0, S_POSS_RUN2, 0},
	{"POSS_RUN2", 0, SPR_POSS, 1, 3, A_Chase, 0, 0, S_POSS_RUN3, 0},
	{"POSS_RUN3", 0, SPR_POSS, 2, 3, A_Chase, 0, 0, S_POSS_RUN4, 0},
	{"POSS_RUN4", 0, SPR_POSS, 3, 3, A_Chase, 0, 0, S_POSS_RUN5, 0},
	{"POSS_RUN5", 0, SPR_POSS, 4, 3, A_Chase, 0, 0, S_POSS_RUN6, 0},
	{"POSS_RUN6", 0, SPR_POSS, 5, 3, A_Chase, 0, 0, S_POSS_RUN1, 0},

	// Red Crawla
	{"SPOS_STND", 0, SPR_SPOS, 0, 5, A_Look, 0, 0, S_SPOS_STND, 0},
	{"SPOS_RUN1", 0, SPR_SPOS, 0, 1, A_Chase, 0, 0, S_SPOS_RUN2, 0},
	{"SPOS_RUN2", 0, SPR_SPOS, 1, 1, A_Chase, 0, 0, S_SPOS_RUN3, 0},
	{"SPOS_RUN3", 0, SPR_SPOS, 2, 1, A_Chase, 0, 0, S_SPOS_RUN4, 0},
	{"SPOS_RUN4", 0, SPR_SPOS, 3, 1, A_Chase, 0, 0, S_SPOS_RUN5, 0},
	{"SPOS_RUN5", 0, SPR_SPOS, 4, 1, A_Chase, 0, 0, S_SPOS_RUN6, 0},
	{"SPOS_RUN6", 0, SPR_SPOS, 5, 1, A_Chase, 0, 0, S_SPOS_RUN1, 0},

	// Greenflower Fish
	{"FISH1", 0, SPR_FISH, 1, 1, NULL, 0, 0, S_FISH2, 0},
	{"FISH2", 0, SPR_FISH, 1, 1, A_FishJump, 0, 0, S_FISH1, 0},
	{"FISH3", 0, SPR_FISH, 0, 1, NULL, 0, 0, S_FISH4, 0},
	{"FISH4", 0, SPR_FISH, 0, 1, A_FishJump, 0, 0, S_FISH3, 0},

	// Gold Buzz
	{"BUZZLOOK1", 0, SPR_BUZZ, 0, 2, A_Look, 0, 0, S_BUZZLOOK2, 0},
	{"BUZZLOOK2", 0, SPR_BUZZ, 1, 2, A_Look, 0, 0, S_BUZZLOOK1, 0},
	{"BUZZFLY1", 0, SPR_BUZZ, 0, 2, A_BuzzFly, sfx_buzz4, 0, S_BUZZFLY2, 0},
	{"BUZZFLY2", 0, SPR_BUZZ, 1, 2, A_BuzzFly, 0, 0, S_BUZZFLY1, 0},

	// Red Buzz
	{"RBUZZLOOK1", 0, SPR_RBUZ, 0, 2, A_Look, 0, 0, S_RBUZZLOOK2, 0},
	{"RBUZZLOOK2", 0, SPR_RBUZ, 1, 2, A_Look, 0, 0, S_RBUZZLOOK1, 0},
	{"RBUZZFLY1", 0, SPR_RBUZ, 0, 2, A_BuzzFly, sfx_buzz4, 0, S_RBUZZFLY2, 0},
	{"RBUZZFLY2", 0, SPR_RBUZ, 1, 2, A_BuzzFly, 0, 0, S_RBUZZFLY1, 0},

	// Jetty-Syn Bomber
	{"JETBLOOK1", 0, SPR_JETB, 0, 4, A_Look, 0, 0, S_JETBLOOK2, 0},
	{"JETBLOOK2", 0, SPR_JETB, 1, 4, A_Look, 0, 0, S_JETBLOOK1, 0},
	{"JETBZOOM1", 0, SPR_JETB, 0, 1, A_JetbThink, 0, 0, S_JETBZOOM2, 0},
	{"JETBZOOM2", 0, SPR_JETB, 1, 1, A_JetbThink, 0, 0, S_JETBZOOM1, 0},

	// Jetty-Syn Gunner
	{"JETGLOOK1", 0, SPR_JETG, 0, 4, A_Look, 0, 0, S_JETGLOOK2, 0},
	{"JETGLOOK2", 0, SPR_JETG, 1, 4, A_Look, 0, 0, S_JETGLOOK1, 0},
	{"JETGZOOM1", 0, SPR_JETG, 0, 1, A_JetgThink, 0, 0, S_JETGZOOM2, 0},
	{"JETGZOOM2", 0, SPR_JETG, 1, 1, A_JetgThink, 0, 0, S_JETGZOOM1, 0},
	{"JETGSHOOT1", 0, SPR_JETG, 2, 1, A_JetgShoot, 0, 0, S_JETGSHOOT2, 0},
	{"JETGSHOOT2", 0, SPR_JETG, 3, 1, NULL, 0, 0, S_JETGZOOM1, 0},

	// Crawla Commander
	{"CCOMMAND1", 0, SPR_CCOM, 0, 1, A_CrawlaCommanderThink, 0, 15*FRACUNIT, S_CCOMMAND2, 0},
	{"CCOMMAND2", 0, SPR_CCOM, 1, 1, A_CrawlaCommanderThink, 0, 15*FRACUNIT, S_CCOMMAND1, 0},
	{"CCOMMAND3", 0, SPR_CCOM, 2, 1, A_CrawlaCommanderThink, 0, 15*FRACUNIT, S_CCOMMAND4, 0},
	{"CCOMMAND4", 0, SPR_CCOM, 3, 1, A_CrawlaCommanderThink, 0, 15*FRACUNIT, S_CCOMMAND3, 0},

	// Deton
	{"DETON1", 0, SPR_DETN, 0, 35, A_Look, 0, 0, S_DETON1, 0},
	{"DETON2", 0, SPR_DETN, 0,  1, A_DetonChase, 0, 0, S_DETON3, 0},
	{"DETON3", 0, SPR_DETN, 1,  1, A_DetonChase, 0, 0, S_DETON4, 0},
	{"DETON4", 0, SPR_DETN, 2,  1, A_DetonChase, 0, 0, S_DETON5, 0},
	{"DETON5", 0, SPR_DETN, 3,  1, A_DetonChase, 0, 0, S_DETON6, 0},
	{"DETON6", 0, SPR_DETN, 4,  1, A_DetonChase, 0, 0, S_DETON7, 0},
	{"DETON7", 0, SPR_DETN, 5,  1, A_DetonChase, 0, 0, S_DETON8, 0},
	{"DETON8", 0, SPR_DETN, 6,  1, A_DetonChase, 0, 0, S_DETON9, 0},
	{"DETON9", 0, SPR_DETN, 7,  1, A_DetonChase, 0, 0, S_DETON10, 0},
	{"DETON10", 0, SPR_DETN, 6,  1, A_DetonChase, 0, 0, S_DETON11, 0},
	{"DETON11", 0, SPR_DETN, 5,  1, A_DetonChase, 0, 0, S_DETON12, 0},
	{"DETON12", 0, SPR_DETN, 4,  1, A_DetonChase, 0, 0, S_DETON13, 0},
	{"DETON13", 0, SPR_DETN, 3,  1, A_DetonChase, 0, 0, S_DETON14, 0},
	{"DETON14", 0, SPR_DETN, 2,  1, A_DetonChase, 0, 0, S_DETON15, 0},
	{"DETON15", 0, SPR_DETN, 1,  1, A_DetonChase, 0, 0, S_DETON2, 0},

	// Skim Mine Dropper
	{"SKIM1", 0, SPR_SKIM, 0,  1, A_SkimChase, 0, 0, S_SKIM2, 0},
	{"SKIM2", 0, SPR_SKIM, 0,  1, A_SkimChase, 0, 0, S_SKIM1, 0},
	{"SKIM3", 0, SPR_SKIM, 0, 14,        NULL, 0, 0, S_SKIM4, 0},
	{"SKIM4", 0, SPR_SKIM, 0, 14,  A_DropMine, 0, 0, S_SKIM1, 0},

	// THZ Turret
	{"TURRET", 0, SPR_TRET, FF_FULLBRIGHT, 105, A_TurretStop, 0, 0, S_TURRETFIRE, 0},
	{"TURRETFIRE", 0, SPR_TRET, FF_FULLBRIGHT, 105, A_TurretFire, 0, 0, S_TURRET, 0},
	{"TURRETSHOCK1", 0, SPR_TRET, FF_FULLBRIGHT|1, 7, A_Pain, 0, 0, S_TURRETSHOCK2, 0},
	{"TURRETSHOCK2", 0, SPR_TRET, FF_FULLBRIGHT|2, 7, NULL, 0, 0, S_TURRETSHOCK3, 0},
	{"TURRETSHOCK3", 0, SPR_TRET, FF_FULLBRIGHT|3, 7, NULL, 0, 0, S_TURRETSHOCK4, 0},
	{"TURRETSHOCK4", 0, SPR_TRET, FF_FULLBRIGHT|4, 7, NULL, 0, 0, S_TURRETSHOCK5, 0},
	{"TURRETSHOCK5", 0, SPR_TRET, FF_FULLBRIGHT|1, 7, NULL, 0, 0, S_TURRETSHOCK6, 0},
	{"TURRETSHOCK6", 0, SPR_TRET, FF_FULLBRIGHT|2, 7, A_Pain, 0, 0, S_TURRETSHOCK7, 0},
	{"TURRETSHOCK7", 0, SPR_TRET, FF_FULLBRIGHT|3, 7, NULL, 0, 0, S_TURRETSHOCK8, 0},
	{"TURRETSHOCK8", 0, SPR_TRET, FF_FULLBRIGHT|4, 7, NULL, 0, 0, S_TURRETSHOCK9, 0},
	{"TURRETSHOCK9", 0, SPR_TRET, FF_FULLBRIGHT|4, 7, A_LinedefExecuteFromArg, 0, 0, S_XPLD1, 0},

	{"TURRETLOOK", 0, SPR_TURR, 0, 1, A_Look, 1, 0, S_TURRETPOPDOWN8, 0},
	{"TURRETSEE", 0, SPR_TURR, 0, 0, A_FaceTarget, 0, 0, S_TURRETPOPUP1, 0},
	{"TURRETPOPUP1", 0, SPR_TURR, 1, 2, A_Pain, 0, 0, S_TURRETPOPUP2, 0},
	{"TURRETPOPUP2", 0, SPR_TURR, 2, 2, NULL, 0, 0, S_TURRETPOPUP3, 0},
	{"TURRETPOPUP3", 0, SPR_TURR, 3, 2, NULL, 0, 0, S_TURRETPOPUP4, 0},
	{"TURRETPOPUP4", 0, SPR_TURR, 4, 2, NULL, 0, 0, S_TURRETPOPUP5, 0},
	{"TURRETPOPUP5", 0, SPR_TURR, 5, 2, NULL, 0, 0, S_TURRETPOPUP6, 0},
	{"TURRETPOPUP6", 0, SPR_TURR, 6, 2, NULL, 0, 0, S_TURRETPOPUP7, 0},
	{"TURRETPOPUP7", 0, SPR_TURR, 7, 2, NULL, 0, 0, S_TURRETPOPUP8, 0},
	{"TURRETPOPUP8", 0, SPR_TURR, 8, 14,NULL, 0, 0, S_TURRETSHOOT, 0},
	{"TURRETSHOOT", 0, SPR_TURR, 8, 14,A_JetgShoot, 0, 0, S_TURRETPOPDOWN1, 0},
	{"TURRETPOPDOWN1", 0, SPR_TURR, 7, 2, A_Pain, 0, 0, S_TURRETPOPDOWN2, 0},
	{"TURRETPOPDOWN2", 0, SPR_TURR, 6, 2, NULL, 0, 0, S_TURRETPOPDOWN3, 0},
	{"TURRETPOPDOWN3", 0, SPR_TURR, 5, 2, NULL, 0, 0, S_TURRETPOPDOWN4, 0},
	{"TURRETPOPDOWN4", 0, SPR_TURR, 4, 2, NULL, 0, 0, S_TURRETPOPDOWN5, 0},
	{"TURRETPOPDOWN5", 0, SPR_TURR, 3, 2, NULL, 0, 0, S_TURRETPOPDOWN6, 0},
	{"TURRETPOPDOWN6", 0, SPR_TURR, 2, 2, NULL, 0, 0, S_TURRETPOPDOWN7, 0},
	{"TURRETPOPDOWN7", 0, SPR_TURR, 1, 2, NULL, 0, 0, S_TURRETPOPDOWN8, 0},
	{"TURRETPOPDOWN8", 0, SPR_TURR, 0, 69,A_SetTics, 0, 1, S_TURRETLOOK, 0},

	// Spincushion
	{"SPINCUSHION_LOOK", 0, SPR_SHRP, 0,  2, A_Look,                 0, 0, S_SPINCUSHION_LOOK, 0},
	{"SPINCUSHION_CHASE1", 0, SPR_SHRP, 1,  2, A_SharpChase,           0, 0, S_SPINCUSHION_CHASE2, 0},
	{"SPINCUSHION_CHASE2", 0, SPR_SHRP, 2,  2, A_SharpChase,           0, 0, S_SPINCUSHION_CHASE3, 0},
	{"SPINCUSHION_CHASE3", 0, SPR_SHRP, 3,  2, A_SharpChase,           0, 0, S_SPINCUSHION_CHASE4, 0},
	{"SPINCUSHION_CHASE4", 0, SPR_SHRP, 0,  2, A_SharpChase,           0, 0, S_SPINCUSHION_CHASE1, 0},
	{"SPINCUSHION_AIM1", 0, SPR_SHRP, 0,  2, NULL,                   0, 0, S_SPINCUSHION_AIM2, 0},
	{"SPINCUSHION_AIM2", 0, SPR_SHRP, 4,  2, NULL,                   0, 0, S_SPINCUSHION_AIM3, 0},
	{"SPINCUSHION_AIM3", 0, SPR_SHRP, 5,  2, A_SetObjectFlags, MF_PAIN, 2, S_SPINCUSHION_AIM4, 0},
	{"SPINCUSHION_AIM4", 0, SPR_SHRP, 6, 16, A_MultiShotDist, (MT_DUST<<16)|6, -32, S_SPINCUSHION_AIM5, 0},
	{"SPINCUSHION_AIM5", 0, SPR_SHRP, 6,  0, A_PlaySound,   sfx_shrpgo, 1, S_SPINCUSHION_SPIN1, 0},
	{"SPINCUSHION_SPIN1", 0, SPR_SHRP, 6,  1, A_SharpSpin,            0, 0, S_SPINCUSHION_SPIN2, 0},
	{"SPINCUSHION_SPIN2", 0, SPR_SHRP, 8,  1, A_SharpSpin,            0, 0, S_SPINCUSHION_SPIN3, 0},
	{"SPINCUSHION_SPIN3", 0, SPR_SHRP, 7,  1, A_SharpSpin,            0, 0, S_SPINCUSHION_SPIN4, 0},
	{"SPINCUSHION_SPIN4", 0, SPR_SHRP, 8,  1, A_SharpSpin,  MT_SPINDUST, 0, S_SPINCUSHION_SPIN1, 0},
	{"SPINCUSHION_STOP1", 0, SPR_SHRP, 6,  1, A_PlaySound,    sfx_s3k69, 1, S_SPINCUSHION_STOP2, 0},
	{"SPINCUSHION_STOP2", 0, SPR_SHRP, 6,  4, A_SharpDecel,           0, 0, S_SPINCUSHION_STOP2, 0},
	{"SPINCUSHION_STOP3", 0, SPR_SHRP, 5,  4, A_FaceTarget,           0, 0, S_SPINCUSHION_STOP4, 0},
	{"SPINCUSHION_STOP4", 0, SPR_SHRP, 4,  4, A_SetObjectFlags, MF_PAIN, 1, S_SPINCUSHION_LOOK, 0},

	// Crushstacean
	{"CRUSHSTACEAN_ROAM1", 0, SPR_CRAB, 0,  3, A_CrushstaceanWalk,  0, S_CRUSHSTACEAN_ROAMPAUSE, S_CRUSHSTACEAN_ROAM2, 0},
	{"CRUSHSTACEAN_ROAM2", 0, SPR_CRAB, 1,  3, A_CrushstaceanWalk,  0, S_CRUSHSTACEAN_ROAMPAUSE, S_CRUSHSTACEAN_ROAM3, 0},
	{"CRUSHSTACEAN_ROAM3", 0, SPR_CRAB, 0,  3, A_CrushstaceanWalk,  0, S_CRUSHSTACEAN_ROAMPAUSE, S_CRUSHSTACEAN_ROAM4, 0},
	{"CRUSHSTACEAN_ROAM4", 0, SPR_CRAB, 2,  3, A_CrushstaceanWalk,  0, S_CRUSHSTACEAN_ROAMPAUSE, S_CRUSHSTACEAN_ROAM1, 0},
	{"CRUSHSTACEAN_ROAMPAUSE", 0, SPR_CRAB, 0, 40, NULL,                0,                        0, S_CRUSHSTACEAN_ROAM1, 0},
	{"CRUSHSTACEAN_PUNCH1", 0, SPR_CRAB, 0, 10, NULL,                0,                        0, S_CRUSHSTACEAN_PUNCH2, 0},
	{"CRUSHSTACEAN_PUNCH2", 0, SPR_CRAB, 0, -1, A_CrushstaceanPunch, 0,                        0, S_CRUSHSTACEAN_ROAMPAUSE, 0},
	{"CRUSHCLAW_AIM", 0, SPR_CRAB, 3,  1, A_CrushclawAim,   40,               20, S_CRUSHCLAW_AIM, 0},
	{"CRUSHCLAW_OUT", 0, SPR_CRAB, 3,  1, A_CrushclawLaunch, 0, S_CRUSHCLAW_STAY, S_CRUSHCLAW_OUT, 0},
	{"CRUSHCLAW_STAY", 0, SPR_CRAB, 3, 10, NULL,              0,                0, S_CRUSHCLAW_IN, 0},
	{"CRUSHCLAW_IN", 0, SPR_CRAB, 3,  1, A_CrushclawLaunch, 1, S_CRUSHCLAW_WAIT, S_CRUSHCLAW_IN, 0},
	{"CRUSHCLAW_WAIT", 0, SPR_CRAB, 3, 37, NULL,              0,                0, S_CRUSHCLAW_AIM, 0},
	{"CRUSHCHAIN", 0, SPR_CRAB, 4, -1, NULL, 0, 0, S_NULL, 0},

	// Banpyura
	{"BANPYURA_ROAM1", 0, SPR_CR2B, 0,  3, A_CrushstaceanWalk,  0, S_BANPYURA_ROAMPAUSE, S_BANPYURA_ROAM2, 0},
	{"BANPYURA_ROAM2", 0, SPR_CR2B, 1,  3, A_CrushstaceanWalk,  0, S_BANPYURA_ROAMPAUSE, S_BANPYURA_ROAM3, 0},
	{"BANPYURA_ROAM3", 0, SPR_CR2B, 0,  3, A_CrushstaceanWalk,  0, S_BANPYURA_ROAMPAUSE, S_BANPYURA_ROAM4, 0},
	{"BANPYURA_ROAM4", 0, SPR_CR2B, 2,  3, A_CrushstaceanWalk,  0, S_BANPYURA_ROAMPAUSE, S_BANPYURA_ROAM1, 0},
	{"BANPYURA_ROAMPAUSE", 0, SPR_CR2B, 0, 40, NULL,                0,                    0, S_BANPYURA_ROAM1, 0},

	{"CDIAG1", 0, SPR_CSPR, 0, 1, A_CrushclawAim, 50, 20, S_CDIAG1, 0},
	{"CDIAG2", 0, SPR_CSPR, 1, 1, A_Pain,          0,  0, S_CDIAG3, 0},
	{"CDIAG3", 0, SPR_CSPR, 2, 1, A_CrushclawAim, 50, 20, S_CDIAG4, 0},
	{"CDIAG4", 0, SPR_CSPR, 3, 1, A_CrushclawAim, 50, 20, S_CDIAG5, 0},
	{"CDIAG5", 0, SPR_CSPR, 4, 1, A_CrushclawAim, 50, 20, S_CDIAG6, 0},
	{"CDIAG6", 0, SPR_CSPR, 3, 1, A_CrushclawAim, 50, 20, S_CDIAG7, 0},
	{"CDIAG7", 0, SPR_CSPR, 2, 1, A_CrushclawAim, 50, 20, S_CDIAG8, 0},
	{"CDIAG8", 0, SPR_CSPR, 1, 1, A_CrushclawAim, 50, 20, S_CDIAG1, 0},

	// Jet Jaw
	{"JETJAW_ROAM1", 0, SPR_JJAW, 0, 1, A_JetJawRoam,               0,               0,   S_JETJAW_ROAM2, 0},
	{"JETJAW_ROAM2", 0, SPR_JJAW, 0, 1, A_JetJawRoam,               0,               0,   S_JETJAW_ROAM3, 0},
	{"JETJAW_ROAM3", 0, SPR_JJAW, 0, 1, A_JetJawRoam,               0,               0,   S_JETJAW_ROAM4, 0},
	{"JETJAW_ROAM4", 0, SPR_JJAW, 0, 1, A_JetJawRoam,               0,               0,   S_JETJAW_ROAM5, 0},
	{"JETJAW_ROAM5", 0, SPR_JJAW, 1, 1, A_JetJawRoam,               0,               0,   S_JETJAW_ROAM6, 0},
	{"JETJAW_ROAM6", 0, SPR_JJAW, 1, 1, A_JetJawRoam,               0,               0,   S_JETJAW_ROAM7, 0},
	{"JETJAW_ROAM7", 0, SPR_JJAW, 1, 1, A_JetJawRoam,               0,               0,   S_JETJAW_ROAM8, 0},
	{"JETJAW_ROAM8", 0, SPR_JJAW, 1, 1, A_JetJawRoam,               0,               0,   S_JETJAW_ROAM1, 0},
	{"JETJAW_CHOMP1", 0, SPR_JJAW, 0, 1, A_DualAction, S_JETJAW_CHOMP16, S_JETJAW_SOUND,  S_JETJAW_CHOMP2, 0},
	{"JETJAW_CHOMP2", 0, SPR_JJAW, 0, 1, A_JetJawChomp,              0,               0,  S_JETJAW_CHOMP3, 0},
	{"JETJAW_CHOMP3", 0, SPR_JJAW, 0, 1, A_JetJawChomp,              0,               0,  S_JETJAW_CHOMP4, 0},
	{"JETJAW_CHOMP4", 0, SPR_JJAW, 0, 1, A_JetJawChomp,              0,               0,  S_JETJAW_CHOMP5, 0},
	{"JETJAW_CHOMP5", 0, SPR_JJAW, 1, 1, A_JetJawChomp,              0,               0,  S_JETJAW_CHOMP6, 0},
	{"JETJAW_CHOMP6", 0, SPR_JJAW, 1, 1, A_JetJawChomp,              0,               0,  S_JETJAW_CHOMP7, 0},
	{"JETJAW_CHOMP7", 0, SPR_JJAW, 1, 1, A_JetJawChomp,              0,               0,  S_JETJAW_CHOMP8, 0},
	{"JETJAW_CHOMP8", 0, SPR_JJAW, 1, 1, A_JetJawChomp,              0,               0,  S_JETJAW_CHOMP9, 0},
	{"JETJAW_CHOMP9", 0, SPR_JJAW, 2, 1, A_JetJawChomp,              0,               0, S_JETJAW_CHOMP10, 0},
	{"JETJAW_CHOMP10", 0, SPR_JJAW, 2, 1, A_JetJawChomp,              0,               0, S_JETJAW_CHOMP11, 0},
	{"JETJAW_CHOMP11", 0, SPR_JJAW, 2, 1, A_JetJawChomp,              0,               0, S_JETJAW_CHOMP12, 0},
	{"JETJAW_CHOMP12", 0, SPR_JJAW, 2, 1, A_JetJawChomp,              0,               0, S_JETJAW_CHOMP13, 0},
	{"JETJAW_CHOMP13", 0, SPR_JJAW, 3, 1, A_JetJawChomp,              0,               0, S_JETJAW_CHOMP14, 0},
	{"JETJAW_CHOMP14", 0, SPR_JJAW, 3, 1, A_JetJawChomp,              0,               0, S_JETJAW_CHOMP15, 0},
	{"JETJAW_CHOMP15", 0, SPR_JJAW, 3, 1, A_JetJawChomp,              0,               0, S_JETJAW_CHOMP16, 0},
	{"JETJAW_CHOMP16", 0, SPR_JJAW, 3, 1, A_JetJawChomp,              0,               0,  S_JETJAW_CHOMP1, 0},
	{"JETJAW_SOUND", 0, SPR_JJAW, 0, 1, A_PlayAttackSound,          0,               0,   S_JETJAW_SOUND, 0},

	// Snailer
	{"SNAILER1", 0, SPR_SNLR, 0, 1, A_SnailerThink, 0, 0, S_SNAILER1, 0},
	{"SNAILER_FLICKY", 0, SPR_BOM1, 0, 0, A_FlickySpawn, 1<<17, 0, S_XPLD1, 0},

	// Vulture
	{"VULTURE_STND", 0, SPR_VLTR, 4, 35,        A_Look,         1, 0, S_VULTURE_STND, 0},
	{"VULTURE_DRIFT", 0, SPR_VLTR, 4, 3,         A_VultureHover, 0, 0, S_VULTURE_DRIFT, 0},
	{"VULTURE_ZOOM1", 0, SPR_VLTR, 0, 6,         A_VultureBlast, 0, 0, S_VULTURE_ZOOM2, 0},
	{"VULTURE_ZOOM2", 0, SPR_VLTR, 0, 3,         A_VultureFly,   0, 0, S_VULTURE_ZOOM2, 0},
	{"VULTURE_STUNNED", 0, SPR_VLTR, 0, 3*TICRATE, NULL,           0, 0, S_VULTURE_DRIFT, 0},

	// Pointy
	{"POINTY1", 0, SPR_PNTY, 0,  1, A_PointyThink, 0, 0, S_POINTY1, 0},

	// Pointy Ball
	{"POINTYBALL1", 0, SPR_PNTY, 1,  1, A_CheckBuddy, 0, 0, S_POINTYBALL1, 0},

	// Robo-Hood
	{"ROBOHOOD_LOOK", 0, SPR_ARCH, 0,       4,            A_Look, 2048<<FRACBITS,   0, S_ROBOHOOD_LOOK, 0},
	{"ROBOHOOD_STAND", 0, SPR_ARCH, 0,       1,       A_HoodThink,              0,   0, S_ROBOHOOD_STAND, 0},
	{"ROBOHOOD_FIRE1", 0, SPR_ARCH, 2, TICRATE, A_PlayActiveSound,              0,   0, S_ROBOHOOD_FIRE2, 0},
	{"ROBOHOOD_FIRE2", 0, SPR_ARCH, 2,      20,        A_HoodFire,       MT_ARROW,   0, S_ROBOHOOD_STAND, 0},
	{"ROBOHOOD_JUMP1", 0, SPR_ARCH, 1,       1,      A_FaceTarget,              0,   0, S_ROBOHOOD_JUMP2, 0},
	{"ROBOHOOD_JUMP2", 0, SPR_ARCH, 1,       1,        A_BunnyHop,              4, -10, S_ROBOHOOD_JUMP3, 0},
	{"ROBOHOOD_JUMP3", 0, SPR_ARCH, 1,       1,        A_HoodFall,              0,   0, S_ROBOHOOD_JUMP3, 0},

	// Castlebot Facestabber
	{"FACESTABBER_STND1", 0, SPR_CBFS, 0,  1,        A_Chase,  0, 0, S_FACESTABBER_STND2, 0},
	{"FACESTABBER_STND2", 0, SPR_CBFS, 1,  1,        A_Chase,  0, 0, S_FACESTABBER_STND3, 0},
	{"FACESTABBER_STND3", 0, SPR_CBFS, 2,  1,        A_Chase,  0, 0, S_FACESTABBER_STND4, 0},
	{"FACESTABBER_STND4", 0, SPR_CBFS, 3,  1,        A_Chase,  0, 0, S_FACESTABBER_STND5, 0},
	{"FACESTABBER_STND5", 0, SPR_CBFS, 4,  1,        A_Chase,  0, 0, S_FACESTABBER_STND6, 0},
	{"FACESTABBER_STND6", 0, SPR_CBFS, 5,  1,        A_Chase,  0, 0, S_FACESTABBER_STND1, 0},
	{"FACESTABBER_CHARGE1", 0, SPR_CBFS, 0,  1,  A_FaceStabRev,                  20, S_FACESTABBER_CHARGE2, S_FACESTABBER_CHARGE1, 0},
	{"FACESTABBER_CHARGE2", 0, SPR_CBFS, 0,  0,   A_FaceTarget,                   0,                     0, S_FACESTABBER_CHARGE3, 0},
	{"FACESTABBER_CHARGE3", 0, SPR_CBFS, 7,  1, A_FaceStabHurl,                   6, S_FACESTABBER_CHARGE4, S_FACESTABBER_CHARGE3, 0},
	{"FACESTABBER_CHARGE4", 0, SPR_CBFS, 7,  1, A_FaceStabMiss, 0,   S_FACESTABBER_STND1, S_FACESTABBER_CHARGE4, 0},
	{"FACESTABBER_PAIN", 0, SPR_CBFS, 0, 35,         A_Pain, 0,                     0, S_FACESTABBER_STND1, 0},
	{"FACESTABBER_DIE1", 0, SPR_CBFS, 0,  2,   A_BossScream, 1, 0, S_FACESTABBER_DIE2, 0},
	{"FACESTABBER_DIE2", 0, SPR_NULL, 0,  2,   A_BossScream, 1, 0, S_FACESTABBER_DIE3, 0},
	{"FACESTABBER_DIE3", 0, SPR_NULL, 0,  0,       A_Repeat, 7, S_FACESTABBER_DIE1,    S_XPLD_FLICKY, 0},

	{"FACESTABBERSPEAR", 0, SPR_STAB, FF_PAPERSPRITE|FF_TRANS50|FF_FULLBRIGHT, -1, NULL, 0, 0, S_NULL, 0},

	// Egg Guard
	{"EGGGUARD_STND", 0, SPR_SPSH,  0,  1,       A_Look, 0, 0, S_EGGGUARD_STND, 0},
	{"EGGGUARD_WALK1", 0, SPR_SPSH,  1,  3, A_GuardChase, 0, 0, S_EGGGUARD_WALK2, 0},
	{"EGGGUARD_WALK2", 0, SPR_SPSH,  2,  3, A_GuardChase, 0, 0, S_EGGGUARD_WALK3, 0},
	{"EGGGUARD_WALK3", 0, SPR_SPSH,  3,  3, A_GuardChase, 0, 0, S_EGGGUARD_WALK4, 0},
	{"EGGGUARD_WALK4", 0, SPR_SPSH,  4,  3, A_GuardChase, 0, 0, S_EGGGUARD_WALK1, 0},
	{"EGGGUARD_MAD1", 0, SPR_SPSH,  5,  5,         NULL, 0, 0, S_EGGGUARD_MAD2, 0},
	{"EGGGUARD_MAD2", 0, SPR_SPSH,  6,  5,         NULL, 0, 0, S_EGGGUARD_MAD3, 0},
	{"EGGGUARD_MAD3", 0, SPR_SPSH,  7, 15,         NULL, 0, 0, S_EGGGUARD_RUN1, 0},
	{"EGGGUARD_RUN1", 0, SPR_SPSH,  8,  1, A_GuardChase, 0, 0, S_EGGGUARD_RUN2, 0},
	{"EGGGUARD_RUN2", 0, SPR_SPSH,  9,  1, A_GuardChase, 0, 0, S_EGGGUARD_RUN3, 0},
	{"EGGGUARD_RUN3", 0, SPR_SPSH, 10,  1, A_GuardChase, 0, 0, S_EGGGUARD_RUN4, 0},
	{"EGGGUARD_RUN4", 0, SPR_SPSH, 11,  1, A_GuardChase, 0, 0, S_EGGGUARD_RUN1, 0},

	{"EGGSHIELD", 0, SPR_ESHI, 0, 8, A_EggShield, 0, 0, S_EGGSHIELD, 0},
	{"EGGSHIELDBREAK", 0, SPR_ESHI, 0, TICRATE/2, NULL, 0, 0, S_NULL, 0},

	// Green Snapper
	{"SNAPPER_SPAWN", 0, SPR_GSNP, 0, TICRATE, NULL,             0,              0,               S_SNAPPER_SPAWN2, 0},
	{"SNAPPER_SPAWN2", 0, SPR_GSNP, 0, 2,       A_SnapperSpawn,   MT_SNAPPER_LEG, MT_SNAPPER_HEAD, S_GSNAPPER_STND, 0},
	{"GSNAPPER_STND", 0, SPR_GSNP, 0, 1,       A_SnapperThinker, 0,              0,               S_GSNAPPER_STND, 0},
	{"GSNAPPER1", 0, SPR_GSNP, 0, 2,       A_Chase,          0,              0,               S_GSNAPPER2, 0},
	{"GSNAPPER2", 0, SPR_GSNP, 1, 2,       A_Chase,          0,              0,               S_GSNAPPER3, 0},
	{"GSNAPPER3", 0, SPR_GSNP, 2, 2,       A_Chase,          0,              0,               S_GSNAPPER4, 0},
	{"GSNAPPER4", 0, SPR_GSNP, 3, 2,       A_Chase,          0,              0,               S_GSNAPPER1, 0},
	{"SNAPPER_XPLD", 0, SPR_GSNP, 0, 0,       A_KillSegments,   0,              0,               S_XPLD_FLICKY, 0},
	{"SNAPPER_LEG", 0, SPR_GSNL, 0, -1,      NULL,             0,              0,               S_NULL, 0},
	{"SNAPPER_LEGRAISE", 0, SPR_GSNL, 1, -1,      NULL,             0,              0,               S_NULL, 0},
	{"SNAPPER_HEAD", 0, SPR_GSNH, 0, -1,      NULL,             0,              0,               S_NULL, 0},

	// Minus
	{"MINUS_INIT", 0, SPR_MNUD, 0,            1,  NULL,           0, 0, S_MINUS_STND, 0}, // (required for objectplace to work)
	{"MINUS_STND", 0, SPR_NULL, 0,            10, A_Look,         0, 0, S_MINUS_STND, 0},
	{"MINUS_DIGGING1", 0, SPR_NULL, 0,            1,  A_MinusDigging, 1, 0, S_MINUS_DIGGING2, 0},
	{"MINUS_DIGGING2", 0, SPR_NULL, 0,            1,  A_MinusDigging, 0, 0, S_MINUS_DIGGING3, 0},
	{"MINUS_DIGGING3", 0, SPR_NULL, 0,            1,  A_MinusDigging, 0, 0, S_MINUS_DIGGING4, 0},
	{"MINUS_DIGGING4", 0, SPR_NULL, 0,            1,  A_MinusDigging, 0, 0, S_MINUS_DIGGING1, 0},
	{"MINUS_BURST0", 0, SPR_NULL, 0,            25, NULL,           0, 0, S_MINUS_POPUP, 0},
	{"MINUS_BURST1", 0, SPR_MNUD, FF_ANIMATE,   5,  NULL,           1, 2, S_MINUS_BURST2, 0},
	{"MINUS_BURST2", 0, SPR_MNUD, 1|FF_ANIMATE, 5,  NULL,           1, 2, S_MINUS_BURST3, 0},
	{"MINUS_BURST3", 0, SPR_MNUD, 2|FF_ANIMATE, 5,  NULL,           1, 2, S_MINUS_BURST4, 0},
	{"MINUS_BURST4", 0, SPR_MNUD, 3|FF_ANIMATE, 5,  NULL,           1, 2, S_MINUS_BURST5, 0},
	{"MINUS_BURST5", 0, SPR_MNUD, 4|FF_ANIMATE, 5,  NULL,           1, 2, S_MINUSDIRT2, 0},
	{"MINUS_POPUP", 0, SPR_MNUS, 3, 1, A_MinusPopup, 0, 0, S_MINUS_AERIAL1, 0},
	{"MINUS_AERIAL1", 0, SPR_MNUS, 0, 1, A_MinusCheck, 0, 1, S_MINUS_AERIAL2, 0},
	{"MINUS_AERIAL2", 0, SPR_MNUS, 1, 1, A_MinusCheck, 0, 1, S_MINUS_AERIAL3, 0},
	{"MINUS_AERIAL3", 0, SPR_MNUS, 2, 1, A_MinusCheck, 0, 1, S_MINUS_AERIAL4, 0},
	{"MINUS_AERIAL4", 0, SPR_MNUS, 3, 1, A_MinusCheck, 0, 1, S_MINUS_AERIAL1, 0},

	{"MINUSDIRT1", 0, SPR_MNUD, FF_ANIMATE, 6, NULL, 1, 5, S_MINUSDIRT2, 0},
	{"MINUSDIRT2", 0, SPR_MNUD, 5,          8, NULL, 3, 5, S_MINUSDIRT3, 0},
	{"MINUSDIRT3", 0, SPR_MNUD, 4,          8, NULL, 3, 5, S_MINUSDIRT4, 0},
	{"MINUSDIRT4", 0, SPR_MNUD, 3,          8, NULL, 3, 5, S_MINUSDIRT5, 0},
	{"MINUSDIRT5", 0, SPR_MNUD, 2,          8, NULL, 3, 5, S_MINUSDIRT6, 0},
	{"MINUSDIRT6", 0, SPR_MNUD, 1,          8, NULL, 3, 5, S_MINUSDIRT7, 0},
	{"MINUSDIRT7", 0, SPR_MNUD, 0,          8, NULL, 3, 5, S_NULL, 0},

	// Spring Shell
	{"SSHELL_STND", 0, SPR_SSHL,  0,  4, A_Look,  0, 0, S_SSHELL_STND, 0},
	{"SSHELL_RUN1", 0, SPR_SSHL,  0,  4, A_Chase, 0, 0, S_SSHELL_RUN2, 0},
	{"SSHELL_RUN2", 0, SPR_SSHL,  1,  4, A_Chase, 0, 0, S_SSHELL_RUN3, 0},
	{"SSHELL_RUN3", 0, SPR_SSHL,  2,  4, A_Chase, 0, 0, S_SSHELL_RUN4, 0},
	{"SSHELL_RUN4", 0, SPR_SSHL,  3,  4, A_Chase, 0, 0, S_SSHELL_RUN1, 0},
	{"SSHELL_SPRING1", 0, SPR_SSHL,  7,  4, A_Pain,  0, 0, S_SSHELL_SPRING2, 0},
	{"SSHELL_SPRING2", 0, SPR_SSHL,  6,  1, NULL,    0, 0, S_SSHELL_SPRING3, 0},
	{"SSHELL_SPRING3", 0, SPR_SSHL,  5,  1, NULL,    0, 0, S_SSHELL_SPRING4, 0},
	{"SSHELL_SPRING4", 0, SPR_SSHL,  4,  1, NULL,    0, 0, S_SSHELL_RUN1, 0},

	// Spring Shell (yellow)
	{"YSHELL_STND", 0, SPR_SSHL,  8,  4, A_Look,  0, 0, S_YSHELL_STND, 0},
	{"YSHELL_RUN1", 0, SPR_SSHL,  8,  4, A_Chase, 0, 0, S_YSHELL_RUN2, 0},
	{"YSHELL_RUN2", 0, SPR_SSHL,  9,  4, A_Chase, 0, 0, S_YSHELL_RUN3, 0},
	{"YSHELL_RUN3", 0, SPR_SSHL, 10,  4, A_Chase, 0, 0, S_YSHELL_RUN4, 0},
	{"YSHELL_RUN4", 0, SPR_SSHL, 11,  4, A_Chase, 0, 0, S_YSHELL_RUN1, 0},
	{"YSHELL_SPRING1", 0, SPR_SSHL, 15,  4, A_Pain,  0, 0, S_YSHELL_SPRING2, 0},
	{"YSHELL_SPRING2", 0, SPR_SSHL, 14,  1, NULL,    0, 0, S_YSHELL_SPRING3, 0},
	{"YSHELL_SPRING3", 0, SPR_SSHL, 13,  1, NULL,    0, 0, S_YSHELL_SPRING4, 0},
	{"YSHELL_SPRING4", 0, SPR_SSHL, 12,  1, NULL,    0, 0, S_YSHELL_RUN1, 0},

	// Unidus
	{"UNIDUS_STND", 0, SPR_UNID, 0, 4, A_Look,       0, 0, S_UNIDUS_STND, 0},
	{"UNIDUS_RUN", 0, SPR_UNID, 0, 1, A_Chase,      0, 0, S_UNIDUS_RUN , 0},
	{"UNIDUS_BALL", 0, SPR_UNID, 1, 1, A_UnidusBall, 1, 0, S_UNIDUS_BALL, 0},

	// Canarivore
	{"CANARIVORE_LOOK", 0, SPR_CANA, 0, 5,  A_Look,          1200*FRACUNIT+1,   1,                 S_CANARIVORE_LOOK, 0},
	{"CANARIVORE_AWAKEN1", 0, SPR_CANA, 0, 3,  A_PlaySound,     sfx_s3k76,         1,                 S_CANARIVORE_AWAKEN2, 0},
	{"CANARIVORE_AWAKEN2", 0, SPR_CANA, 1, 5,  NULL,            0,                 0,                 S_CANARIVORE_AWAKEN3, 0},
	{"CANARIVORE_AWAKEN3", 0, SPR_CANA, 2, 8,  NULL,            0,                 0,                 S_CANARIVORE_GAS1, 0},
	{"CANARIVORE_GAS1", 0, SPR_CANA, 2, 15, A_PlaySound,     sfx_s3k93,         1,                 S_CANARIVORE_GAS2, 0},
	{"CANARIVORE_GAS2", 0, SPR_CANA, 1, 4,  NULL,            0,                 0,                 S_CANARIVORE_GAS3, 0},
	{"CANARIVORE_GAS3", 0, SPR_CANA, 2, 0,  A_PlaySound,     sfx_s3k97,         1,                 S_CANARIVORE_GAS4, 0},
	{"CANARIVORE_GAS4", 0, SPR_CANA, 2, 5,  A_CanarivoreGas, MT_CANARIVORE_GAS, 0,                 S_CANARIVORE_GAS5, 0},
	{"CANARIVORE_GAS5", 0, SPR_CANA, 1, 5,  NULL,            0,                 0,                 S_CANARIVORE_GASREPEAT, 0},
	{"CANARIVORE_GASREPEAT", 0, SPR_CANA, 2, 0,  A_Repeat,        6,                 S_CANARIVORE_GAS4, S_CANARIVORE_CLOSE1, 0},
	{"CANARIVORE_CLOSE1", 0, SPR_CANA, 1, 8,  NULL,            0,                 0,                 S_CANARIVORE_CLOSE2, 0},
	{"CANARIVORE_CLOSE2", 0, SPR_CANA, 0, 90, NULL,            sfx_s3k5d,         1,                 S_CANARIVORE_LOOK, 0},

	{"CANARIVOREGAS_1", 0, SPR_CANG, 0|FF_TRANS90, 2,         NULL,            0, 0,       S_CANARIVOREGAS_2, 0},
	{"CANARIVOREGAS_2", 0, SPR_CANG, 0|FF_TRANS30, 2*TICRATE, A_SetRandomTics, 2, TICRATE, S_CANARIVOREGAS_3, 0},
	{"CANARIVOREGAS_3", 0, SPR_CANG, 0|FF_TRANS40, 10,        NULL,            0, 0,       S_CANARIVOREGAS_4, 0},
	{"CANARIVOREGAS_4", 0, SPR_CANG, 0|FF_TRANS50, 10,        NULL,            0, 0,       S_CANARIVOREGAS_5, 0},
	{"CANARIVOREGAS_5", 0, SPR_CANG, 0|FF_TRANS60, 10,        NULL,            0, 0,       S_CANARIVOREGAS_6, 0},
	{"CANARIVOREGAS_6", 0, SPR_CANG, 0|FF_TRANS70, 10,        NULL,            0, 0,       S_CANARIVOREGAS_7, 0},
	{"CANARIVOREGAS_7", 0, SPR_CANG, 0|FF_TRANS80, 10,        NULL,            0, 0,       S_CANARIVOREGAS_8, 0},
	{"CANARIVOREGAS_8", 0, SPR_CANG, 0|FF_TRANS90, 10,        NULL,            0, 0,       S_NULL, 0},

	// Pyre Fly
	{"PYREFLY_FLY", 0, SPR_PYRE, FF_ANIMATE, -1, NULL, 3, 2, S_NULL, 0},
	{"PYREFLY_BURN", 0, SPR_PYRE, 4|FF_ANIMATE|FF_FULLBRIGHT, -1, NULL, 3, 2, S_NULL, 0},
	{"PYREFIRE1", 0, SPR_FLAM, FF_FULLBRIGHT, 10, NULL, 0, 0, S_PYREFIRE2, 0},
	{"PYREFIRE2", 0, SPR_FLAM, 1|FF_FULLBRIGHT, 10, A_FireShrink, 0, 16, S_NULL, 0},

	// Pterabyte
	{"PTERABYTESPAWNER", 0, SPR_NULL, 0, -1, A_SpawnPterabytes, 0, 0, S_PTERABYTESPAWNER, 0},
	{"PTERABYTEWAYPOINT", 0, SPR_NULL, 0,  1, A_PterabyteHover,  0, 0, S_PTERABYTEWAYPOINT, 0},
	{"PTERABYTE_FLY1", 0, SPR_PTER, 0,  6, NULL,              0, 0, S_PTERABYTE_FLY2, 0},
	{"PTERABYTE_FLY2", 0, SPR_PTER, 1,  2, NULL,              0, 0, S_PTERABYTE_FLY3, 0},
	{"PTERABYTE_FLY3", 0, SPR_PTER, 2,  6, NULL,              0, 0, S_PTERABYTE_FLY4, 0},
	{"PTERABYTE_FLY4", 0, SPR_PTER, 3,  2, NULL,              0, 0, S_PTERABYTE_FLY1, 0},
	{"PTERABYTE_SWOOPDOWN", 0, SPR_PTER, 4,  1, NULL,              0, 0, S_PTERABYTE_SWOOPDOWN, 0},
	{"PTERABYTE_SWOOPUP", 0, SPR_PTER, 0,  1, NULL,              0, 0, S_PTERABYTE_SWOOPUP, 0},

	// Dragonbomber
	{"DRAGONBOMBER", 0, SPR_DRAB,                0, -1, A_DragonbomberSpawn, 6, 0, S_NULL, 0},
	{"DRAGONWING1", 0, SPR_DRAB, FF_PAPERSPRITE|7,  1,        A_DragonWing, 0, 0, S_DRAGONWING2, 0},
	{"DRAGONWING2", 0, SPR_DRAB, FF_PAPERSPRITE|8,  1,        A_DragonWing, 0, 0, S_DRAGONWING3, 0},
	{"DRAGONWING3", 0, SPR_DRAB, FF_PAPERSPRITE|9,  1,        A_DragonWing, 0, 0, S_DRAGONWING4, 0},
	{"DRAGONWING4", 0, SPR_DRAB, FF_PAPERSPRITE|10, 1,        A_DragonWing, 0, 0, S_DRAGONWING1, 0},
	{"DRAGONTAIL_LOADED", 0, SPR_DRAB,                1,  1,     A_DragonSegment, 0, 0, S_DRAGONTAIL_LOADED, 0},
	{"DRAGONTAIL_EMPTY", 0, SPR_DRAB,                2,  1,     A_DragonSegment, 0, 0, S_DRAGONTAIL_EMPTYLOOP, 0},
	{"DRAGONTAIL_EMPTYLOOP", 0, SPR_DRAB,                2,  0,            A_Repeat, 3*TICRATE, S_DRAGONTAIL_EMPTY, S_DRAGONTAIL_RELOAD, 0},
	{"DRAGONTAIL_RELOAD", 0, SPR_DRAB,                1,  0,   A_PlayActiveSound, 0, 0, S_DRAGONTAIL_LOADED, 0},
	{"DRAGONMINE", 0, SPR_DRAB,                3,  1,        A_MinusCheck, S_DRAGONMINE_LAND1, 0, S_DRAGONMINE, 0},
	{"DRAGONMINE_LAND1", 0, SPR_DRAB,                4,  0,   A_PlayActiveSound, 0, 0, S_DRAGONMINE_LAND2, 0},
	{"DRAGONMINE_LAND2", 0, SPR_DRAB,                4,  2,            A_Thrust, 0, 1, S_DRAGONMINE_SLOWFLASH1, 0},
	{"DRAGONMINE_SLOWFLASH1", 0, SPR_DRAB,                5, 11,                NULL, 0, 0, S_DRAGONMINE_SLOWFLASH2, 0},
	{"DRAGONMINE_SLOWFLASH2", 0, SPR_DRAB,  FF_FULLBRIGHT|6,  1,   A_PlayAttackSound, 0, 0, S_DRAGONMINE_SLOWLOOP, 0},
	{"DRAGONMINE_SLOWLOOP", 0, SPR_DRAB,                5,  0,            A_Repeat, 4, S_DRAGONMINE_SLOWFLASH1, S_DRAGONMINE_FASTFLASH1, 0},
	{"DRAGONMINE_FASTFLASH1", 0, SPR_DRAB,                5,  3,                NULL, 0, 0, S_DRAGONMINE_FASTFLASH2, 0},
	{"DRAGONMINE_FASTFLASH2", 0, SPR_DRAB,  FF_FULLBRIGHT|6,  1,   A_PlayAttackSound, 0, 0, S_DRAGONMINE_FASTLOOP, 0},
	{"DRAGONMINE_FASTLOOP", 0, SPR_DRAB,                5,  0,            A_Repeat, 5, S_DRAGONMINE_FASTFLASH1, S_DEATHSTATE, 0},

	// Boss Explosion
	{"BOSSEXPLODE", 0, SPR_BOM2, FF_FULLBRIGHT|FF_ANIMATE, (5*7), NULL, 6, 5, S_NULL, 0},

	// S3&K Boss Explosion
	{"SONIC3KBOSSEXPLOSION1", 0, SPR_BOM3, FF_FULLBRIGHT,   1, NULL, 0, 0, S_SONIC3KBOSSEXPLOSION2, 0},
	{"SONIC3KBOSSEXPLOSION2", 0, SPR_BOM3, FF_FULLBRIGHT|1, 1, NULL, 0, 0, S_SONIC3KBOSSEXPLOSION3, 0},
	{"SONIC3KBOSSEXPLOSION3", 0, SPR_BOM3, FF_FULLBRIGHT|2, 2, NULL, 0, 0, S_SONIC3KBOSSEXPLOSION4, 0},
	{"SONIC3KBOSSEXPLOSION4", 0, SPR_BOM3, FF_FULLBRIGHT|3, 2, NULL, 0, 0, S_SONIC3KBOSSEXPLOSION5, 0},
	{"SONIC3KBOSSEXPLOSION5", 0, SPR_BOM3, FF_FULLBRIGHT|4, 3, NULL, 0, 0, S_SONIC3KBOSSEXPLOSION6, 0},
	{"SONIC3KBOSSEXPLOSION6", 0, SPR_BOM3, FF_FULLBRIGHT|5, 4, NULL, 0, 0, S_NULL, 0},

	{"JETFUME1", 0, SPR_JETF, FF_ANIMATE|FF_FULLBRIGHT, -1, NULL, 2, 1, S_NULL, 0},

	// Boss 1
	{"EGGMOBILE_STND", 0, SPR_EGGM,  0,   1, A_Boss1Chase,            0, 0, S_EGGMOBILE_STND, 0},
	{"EGGMOBILE_ROFL", 0, SPR_EGGM, FF_ANIMATE|17, 35, A_FaceTarget,  1, 2, S_EGGMOBILE_STND, 0},
	{"EGGMOBILE_LATK1", 0, SPR_EGGM,  1,   3, A_FaceTarget,            0, 0, S_EGGMOBILE_LATK2, 0},
	{"EGGMOBILE_LATK2", 0, SPR_EGGM,  2,  15, NULL,                    0, 0, S_EGGMOBILE_LATK3, 0},
	{"EGGMOBILE_LATK3", 0, SPR_EGGM,  3,   2, NULL,                    0, 0, S_EGGMOBILE_LATK4, 0},
	{"EGGMOBILE_LATK4", 0, SPR_EGGM,  4,   2, A_FaceTarget,            0, 0, S_EGGMOBILE_LATK5, 0},
	{"EGGMOBILE_LATK5", 0, SPR_EGGM,  6,   0, A_PrepareRepeat,        45, 0, S_EGGMOBILE_LATK6, 0},
	{"EGGMOBILE_LATK6", 0, SPR_EGGM,  5,   1, A_Boss1Laser,     MT_LASER, 0, S_EGGMOBILE_LATK7, 0},
	{"EGGMOBILE_LATK7", 0, SPR_EGGM,  6,   1, A_Boss1Laser,     MT_LASER, (1<<16), S_EGGMOBILE_LATK8, 0},
	{"EGGMOBILE_LATK8", 0, SPR_EGGM,  5,   0, A_Repeat, 45, S_EGGMOBILE_LATK6, S_EGGMOBILE_LATK9, 0},
	{"EGGMOBILE_LATK9", 0, SPR_EGGM,  8,  2, NULL,                     0, 0, S_EGGMOBILE_ROFL, 0},
	{"EGGMOBILE_RATK1", 0, SPR_EGGM,  9,   3, A_FaceTarget,            0, 0, S_EGGMOBILE_RATK2, 0},
	{"EGGMOBILE_RATK2", 0, SPR_EGGM, 10,  15, NULL,                    0, 0, S_EGGMOBILE_RATK3, 0},
	{"EGGMOBILE_RATK3", 0, SPR_EGGM, 11,   2, NULL,                    0, 0, S_EGGMOBILE_RATK4, 0},
	{"EGGMOBILE_RATK4", 0, SPR_EGGM, 12,   2, A_FaceTarget,            0, 0, S_EGGMOBILE_RATK5, 0},
	{"EGGMOBILE_RATK5", 0, SPR_EGGM, 14,   0, A_PrepareRepeat,        45, 0, S_EGGMOBILE_RATK6, 0},
	{"EGGMOBILE_RATK6", 0, SPR_EGGM, 13,   1, A_Boss1Laser,     MT_LASER, 1, S_EGGMOBILE_RATK7, 0},
	{"EGGMOBILE_RATK7", 0, SPR_EGGM, 14,   1, A_Boss1Laser,     MT_LASER, 1|(1<<16), S_EGGMOBILE_RATK8, 0},
	{"EGGMOBILE_RATK8", 0, SPR_EGGM, 13,   0, A_Repeat, 45, S_EGGMOBILE_RATK6, S_EGGMOBILE_RATK9, 0},
	{"EGGMOBILE_RATK9", 0, SPR_EGGM, 16,  2, NULL,                     0, 0, S_EGGMOBILE_ROFL, 0},
	{"EGGMOBILE_PANIC1", 0, SPR_EGGM,  0,  0, A_PrepareRepeat,            45, 0, S_EGGMOBILE_PANIC2, 0},
	{"EGGMOBILE_PANIC2", 0, SPR_EGGM, FF_ANIMATE|1, 16, A_FaceTarget,      3, 4, S_EGGMOBILE_PANIC3, 0},
	{"EGGMOBILE_PANIC3", 0, SPR_EGGM,  7,  1, A_Boss1Laser,         MT_LASER, 2, S_EGGMOBILE_PANIC4, 0},
	{"EGGMOBILE_PANIC4", 0, SPR_EGGM,  6,  1, A_Boss1Laser,         MT_LASER, 2|(1<<16), S_EGGMOBILE_PANIC5, 0},
	{"EGGMOBILE_PANIC5", 0, SPR_EGGM,  6,  0, A_Repeat, 45,  S_EGGMOBILE_PANIC3, S_EGGMOBILE_PANIC6, 0},
	{"EGGMOBILE_PANIC6", 0, SPR_EGGM,  0,  0, A_PrepareRepeat,            45, 0, S_EGGMOBILE_PANIC7, 0},
	{"EGGMOBILE_PANIC7", 0, SPR_EGGM, FF_ANIMATE|9, 16, A_FaceTarget,      3, 4, S_EGGMOBILE_PANIC8, 0},
	{"EGGMOBILE_PANIC8", 0, SPR_EGGM, 15,  1, A_Boss1Laser,         MT_LASER, 2, S_EGGMOBILE_PANIC9, 0},
	{"EGGMOBILE_PANIC9", 0, SPR_EGGM, 14,  1, A_Boss1Laser,         MT_LASER, 2|(1<<16), S_EGGMOBILE_PANIC10, 0},
	{"EGGMOBILE_PANIC10", 0, SPR_EGGM, 14,  0, A_Repeat, 45,  S_EGGMOBILE_PANIC8, S_EGGMOBILE_PANIC11, 0},
	{"EGGMOBILE_PANIC11", 0, SPR_EGGM,  0,  0, A_PrepareRepeat,            45, 0, S_EGGMOBILE_PANIC12, 0},
	{"EGGMOBILE_PANIC12", 0, SPR_EGGM, FF_ANIMATE|1, 16, A_FaceTarget,      3, 4, S_EGGMOBILE_PANIC13, 0},
	{"EGGMOBILE_PANIC13", 0, SPR_EGGM,  7,  1, A_Boss1Laser,         MT_LASER, 2, S_EGGMOBILE_PANIC14, 0},
	{"EGGMOBILE_PANIC14", 0, SPR_EGGM,  6,  1, A_Boss1Laser,         MT_LASER, 2|(1<<16), S_EGGMOBILE_PANIC15, 0},
	{"EGGMOBILE_PANIC15", 0, SPR_EGGM,  6,  0, A_Repeat, 45,    S_EGGMOBILE_PANIC13, S_EGGMOBILE_ROFL, 0},
	{"EGGMOBILE_PAIN", 0, SPR_EGGM, 19,  24, A_Pain,                  0, 0, S_EGGMOBILE_PAIN2, 0},
	{"EGGMOBILE_PAIN2", 0, SPR_EGGM, 19,  16, A_SkullAttack,           3, 1, S_EGGMOBILE_STND, 0},
	{"EGGMOBILE_DIE1", 0, SPR_EGGM, 20,  2, A_Fall,                  17, 0, S_EGGMOBILE_DIE2, 0},
	{"EGGMOBILE_DIE2", 0, SPR_EGGM, 20,  2, A_BossScream,             0, 0, S_EGGMOBILE_DIE3, 0},
	{"EGGMOBILE_DIE3", 0, SPR_EGGM, 20,  0, A_Repeat, 17, S_EGGMOBILE_DIE2, S_EGGMOBILE_DIE4, 0},
	{"EGGMOBILE_DIE4", 0, SPR_EGGM, 20,  -1, A_BossDeath,             0, 0, S_NULL, 0},
	{"EGGMOBILE_FLEE1", 0, SPR_EGGM, 21,  2, A_BossScream,             0, 0, S_EGGMOBILE_FLEE2, 0},
	{"EGGMOBILE_FLEE2", 0, SPR_EGGM, 22,  2, A_BossScream,             0, 0, S_EGGMOBILE_FLEE1, 0},
	{"EGGMOBILE_BALL", 0, SPR_UNID,  1,  1, A_UnidusBall,             2, 0, S_EGGMOBILE_BALL, 0},
	{"EGGMOBILE_TARGET", 0, SPR_NULL,  0,  1, A_FocusTarget,            0, 0, S_EGGMOBILE_TARGET, 0},

	{"BOSSEGLZ1", 0, SPR_EGLZ, 0, 35, NULL, 0, 0, S_NULL, 0},
	{"BOSSEGLZ2", 0, SPR_EGLZ, 1, 35, NULL, 0, 0, S_NULL, 0},

	// Boss 2
	{"EGGMOBILE2_STND", 0, SPR_EGGN, 0, -1,              NULL,           0,          0, S_NULL, 0},
	{"EGGMOBILE2_POGO1", 0, SPR_EGGN, 1, 4,               NULL,           0,          0, S_EGGMOBILE2_POGO2, 0},
	{"EGGMOBILE2_POGO2", 0, SPR_EGGN, 0, 2,  A_Boss2PogoTarget,  9*FRACUNIT, 8*FRACUNIT, S_EGGMOBILE2_POGO3, 0},
	{"EGGMOBILE2_POGO3", 0, SPR_EGGN, 1, 2,               NULL,           0,          0, S_EGGMOBILE2_POGO4, 0},
	{"EGGMOBILE2_POGO4", 0, SPR_EGGN, 2, -1,              NULL,           0,          0, S_NULL, 0},
	{"EGGMOBILE2_POGO5", 0, SPR_EGGN, 1, 4,               NULL,           0,          0, S_EGGMOBILE2_POGO6, 0},
	{"EGGMOBILE2_POGO6", 0, SPR_EGGN, 0, 2,  A_Boss2PogoTarget,  7*FRACUNIT, 8*FRACUNIT, S_EGGMOBILE2_POGO7, 0},
	{"EGGMOBILE2_POGO7", 0, SPR_EGGN, 1, 2,               NULL,           0,          0, S_EGGMOBILE2_POGO4, 0},
	{"EGGMOBILE2_PAIN", 0, SPR_EGGN, 3, 24, A_Boss2TakeDamage,  24+TICRATE,          0, S_EGGMOBILE2_STND, 0},
	{"EGGMOBILE2_PAIN2", 0, SPR_EGGN, 4, 24, A_Boss2TakeDamage,  24+TICRATE,          0, S_EGGMOBILE2_POGO4, 0},
	{"EGGMOBILE2_DIE1", 0, SPR_EGGN, 5, 2,             A_Fall,           0,          0, S_EGGMOBILE2_DIE2, 0},
	{"EGGMOBILE2_DIE2", 0, SPR_EGGN, 5, 2,       A_BossScream,           0,          0, S_EGGMOBILE2_DIE3, 0},
	{"EGGMOBILE2_DIE3", 0, SPR_EGGN, 5, 0,       A_Repeat, 17, S_EGGMOBILE2_DIE2, S_EGGMOBILE2_DIE4, 0},
	{"EGGMOBILE2_DIE4", 0, SPR_EGGN, 5, -1,       A_BossDeath,           0,          0, S_NULL, 0},
	{"EGGMOBILE2_FLEE1", 0, SPR_EGGN, 6, 2,       A_BossScream,           0,          0, S_EGGMOBILE2_FLEE2, 0},
	{"EGGMOBILE2_FLEE2", 0, SPR_EGGN, 7, 2,       A_BossScream,           0,          0, S_EGGMOBILE2_FLEE1, 0},

	{"BOSSTANK1", 0, SPR_TANK, 0, 35, NULL, 0, 0, S_NULL, 0},
	{"BOSSTANK2", 0, SPR_TANK, 1, 35, NULL, 0, 0, S_NULL, 0},
	{"BOSSSPIGOT", 0, SPR_TANK, 2, 35, NULL, 0, 0, S_NULL, 0},

	// Boss 2 Goop
	{"GOOP1", 0, SPR_GOOP,            0,  2, A_SpawnObjectRelative, 0, MT_GOOPTRAIL, S_GOOP2, 0},
	{"GOOP2", 0, SPR_GOOP,            1,  2, A_SpawnObjectRelative, 0, MT_GOOPTRAIL, S_GOOP1, 0},
	{"GOOP3", 0, SPR_GOOP,            2, -1,                  NULL, 0,            0, S_NULL, 0},
	{"GOOPTRAIL", 0, SPR_GOOP, FF_ANIMATE|3, 11,                  NULL, 2,            6, S_NULL, 0},

	// Boss 3
	{"EGGMOBILE3_STND", 0, SPR_EGGO,  0,   1, NULL,                    0, 0, S_EGGMOBILE3_STND, 0},
	{"EGGMOBILE3_SHOCK", 0, SPR_EGGO,   FF_ANIMATE, 24, NULL, 1, 2, S_EGGMOBILE3_ATK2, 0},
	{"EGGMOBILE3_ATK1", 0, SPR_EGGO, 6|FF_ANIMATE, 24, NULL, 1, 2, S_EGGMOBILE3_ATK2, 0},
	{"EGGMOBILE3_ATK2", 0, SPR_EGGO,  2,   2, NULL,                    0, 0, S_EGGMOBILE3_ATK3A, 0},
	{"EGGMOBILE3_ATK3A", 0, SPR_EGGO,  3,   2, A_BossFireShot, MT_TORPEDO, 2, S_EGGMOBILE3_ATK3B, 0},
	{"EGGMOBILE3_ATK3B", 0, SPR_EGGO,  3,   2, A_BossFireShot, MT_TORPEDO, 4, S_EGGMOBILE3_ATK3C, 0},
	{"EGGMOBILE3_ATK3C", 0, SPR_EGGO,  3,   2, A_BossFireShot, MT_TORPEDO, 3, S_EGGMOBILE3_ATK3D, 0},
	{"EGGMOBILE3_ATK3D", 0, SPR_EGGO,  3,   2, A_BossFireShot, MT_TORPEDO, 5, S_EGGMOBILE3_ATK4, 0},
	{"EGGMOBILE3_ATK4", 0, SPR_EGGO,  4,   2, NULL,                    0, 0, S_EGGMOBILE3_ATK5, 0},
	{"EGGMOBILE3_ATK5", 0, SPR_EGGO,  5,   2, NULL,                    0, 0, S_EGGMOBILE3_ROFL, 0},
	{"EGGMOBILE3_ROFL", 0, SPR_EGGO,  6|FF_ANIMATE, 60, NULL, 1, 2, S_EGGMOBILE3_STND, 0},
	{"EGGMOBILE3_PAIN", 0, SPR_EGGO,  8,   1, A_Boss3TakeDamage,       0, 0, S_EGGMOBILE3_PAIN2, 0},
	{"EGGMOBILE3_PAIN2", 0, SPR_EGGO,  8,  23, A_Pain,                  0, 0, S_EGGMOBILE3_STND, 0},
	{"EGGMOBILE3_DIE1", 0, SPR_EGGO,  9,   2, A_Fall,                  0, 0, S_EGGMOBILE3_DIE2, 0},
	{"EGGMOBILE3_DIE2", 0, SPR_EGGO,  9,   2, A_BossScream,            0, 0, S_EGGMOBILE3_DIE3, 0},
	{"EGGMOBILE3_DIE3", 0, SPR_EGGO,  9,   0, A_Repeat, 17, S_EGGMOBILE3_DIE2, S_EGGMOBILE3_DIE4, 0},
	{"EGGMOBILE3_DIE4", 0, SPR_EGGO,  9,  -1, A_BossDeath,             0, 0, S_NULL, 0},
	{"EGGMOBILE3_FLEE1", 0, SPR_EGGO, 10,   2, A_BossScream,            0, 0, S_EGGMOBILE3_FLEE2, 0},
	{"EGGMOBILE3_FLEE2", 0, SPR_EGGO, 11,   2, A_BossScream,            0, 0, S_EGGMOBILE3_FLEE1, 0},

	// Boss 3 Pinch
	{"FAKEMOBILE_INIT", 0, SPR_FAKE, 0,  1, NULL,                     0, 0, S_FAKEMOBILE, 0},
	{"FAKEMOBILE", 0, SPR_FAKE, 0,  1, A_Boss3Path,              0, 0, S_FAKEMOBILE, 0},
	{"FAKEMOBILE_ATK1", 0, SPR_FAKE, 0, 22, NULL,                     0, 0, S_FAKEMOBILE_ATK2, 0},
	{"FAKEMOBILE_ATK2", 0, SPR_FAKE, 0,  2, NULL,                     0, 0, S_FAKEMOBILE_ATK3A, 0},
	{"FAKEMOBILE_ATK3A", 0, SPR_FAKE, 0,  2, A_BossFireShot, MT_TORPEDO2, 2, S_FAKEMOBILE_ATK3B, 0},
	{"FAKEMOBILE_ATK3B", 0, SPR_FAKE, 0,  2, A_BossFireShot, MT_TORPEDO2, 4, S_FAKEMOBILE_ATK3C, 0},
	{"FAKEMOBILE_ATK3C", 0, SPR_FAKE, 0,  2, A_BossFireShot, MT_TORPEDO2, 3, S_FAKEMOBILE_ATK3D, 0},
	{"FAKEMOBILE_ATK3D", 0, SPR_FAKE, 0,  2, A_BossFireShot, MT_TORPEDO2, 5, S_FAKEMOBILE, 0},
	{"FAKEMOBILE_DIE1", 0, SPR_FAKE, 1,  1, NULL,                     0, 0, S_FAKEMOBILE_DIE2, 0},
	{"FAKEMOBILE_DIE2", 0, SPR_NULL, 0,  1, NULL,                     0, 0, S_FAKEMOBILE_DIE1, 0},

	{"BOSSSEBH1", 0, SPR_SEBH, 0, 35, NULL, 0, 0, S_NULL, 0},
	{"BOSSSEBH2", 0, SPR_SEBH, 1, 35, NULL, 0, 0, S_NULL, 0},

	// Boss 3 Shockwave

	{"SHOCKWAVE1", 0, SPR_SHCK,   FF_FULLBRIGHT|FF_PAPERSPRITE|FF_ANIMATE, 8, A_Boss3ShockThink, 4, 2, S_SHOCKWAVE2, 0},
	{"SHOCKWAVE2", 0, SPR_SHCK, 3|FF_FULLBRIGHT|FF_PAPERSPRITE|FF_ANIMATE, 8, A_Boss3ShockThink, 4, 2, S_SHOCKWAVE1, 0},

	// Boss 4
	{"EGGMOBILE4_STND", 0, SPR_EGGP, 0, -1, NULL,           0,          0, S_NULL, 0},
	{"EGGMOBILE4_LATK1", 0, SPR_EGGP, 1,  3, NULL,           0,          0, S_EGGMOBILE4_LATK2, 0},
	{"EGGMOBILE4_LATK2", 0, SPR_EGGP, 2, 15, NULL,           0,          0, S_EGGMOBILE4_LATK3, 0},
	{"EGGMOBILE4_LATK3", 0, SPR_EGGP, 3,  2, NULL,           0,          0, S_EGGMOBILE4_LATK4, 0},
	{"EGGMOBILE4_LATK4", 0, SPR_EGGP, 4,  2, NULL,           0,          0, S_EGGMOBILE4_LATK5, 0},
	{"EGGMOBILE4_LATK5", 0, SPR_EGGP, 5, 50, A_Boss4Reverse, sfx_mswing, 0, S_EGGMOBILE4_LATK6, 0},
	{"EGGMOBILE4_LATK6", 0, SPR_EGGP, 6,  2, NULL,           0,          0, S_EGGMOBILE4_STND, 0},
	{"EGGMOBILE4_RATK1", 0, SPR_EGGP, 7,  3, NULL,           0,          0, S_EGGMOBILE4_RATK2, 0},
	{"EGGMOBILE4_RATK2", 0, SPR_EGGP, 8, 15, NULL,           0,          0, S_EGGMOBILE4_RATK3, 0},
	{"EGGMOBILE4_RATK3", 0, SPR_EGGP, 9,  2, NULL,           0,          0, S_EGGMOBILE4_RATK4, 0},
	{"EGGMOBILE4_RATK4", 0, SPR_EGGP,10,  2, NULL,           0,          0, S_EGGMOBILE4_RATK5, 0},
	{"EGGMOBILE4_RATK5", 0, SPR_EGGP,11,150, A_Boss4SpeedUp, sfx_mswing, 0, S_EGGMOBILE4_RATK6, 0},
	{"EGGMOBILE4_RATK6", 0, SPR_EGGP,12,  2, NULL,           0,          0, S_EGGMOBILE4_STND, 0},
	{"EGGMOBILE4_RAISE1", 0, SPR_EGGP,13, 20, A_Boss4Raise,   sfx_doord1, 0, S_EGGMOBILE4_RAISE2, 0},
	{"EGGMOBILE4_RAISE2", 0, SPR_EGGP,15|FF_ANIMATE, -1, NULL,        1,        10, S_NULL, 0},
	{"EGGMOBILE4_PAIN1", 0, SPR_EGGP,13,  0, A_Boss4Reverse, sfx_alarm, sfx_s3k60, S_EGGMOBILE4_PAIN2, 0},
	{"EGGMOBILE4_PAIN2", 0, SPR_EGGP,13, 24, A_Pain,                 0,         0, S_EGGMOBILE4_STND, 0},
	{"EGGMOBILE4_DIE1", 0, SPR_EGGP,14,  2, A_Fall,         0,          0, S_EGGMOBILE4_DIE2, 0},
	{"EGGMOBILE4_DIE2", 0, SPR_EGGP,14,  2, A_BossScream,   0,          0, S_EGGMOBILE4_DIE3, 0},
	{"EGGMOBILE4_DIE3", 0, SPR_EGGP,14,  0, A_Repeat,   17, S_EGGMOBILE4_DIE2, S_EGGMOBILE4_DIE4, 0},
	{"EGGMOBILE4_DIE4", 0, SPR_EGGP,14, -1, A_BossDeath,    0,          0, S_NULL, 0},
	{"EGGMOBILE4_FLEE1", 0, SPR_EGGP,15,  2, A_BossScream,   0,          0, S_EGGMOBILE4_FLEE2, 0},
	{"EGGMOBILE4_FLEE2", 0, SPR_EGGP,16,  2, A_BossScream,   0,          0, S_EGGMOBILE4_FLEE1, 0},
	{"EGGMOBILE4_MACE", 0, SPR_BMCE, 0, -1, NULL,           0,          0, S_NULL, 0},
	{"EGGMOBILE4_MACE_DIE1", 0, SPR_BMCE, 0,  2, A_BossScream,   1, 0, S_EGGMOBILE4_MACE_DIE2, 0},
	{"EGGMOBILE4_MACE_DIE2", 0, SPR_NULL, 0,  2, A_BossScream,   1, 0, S_EGGMOBILE4_MACE_DIE3, 0},
	{"EGGMOBILE4_MACE_DIE3", 0, SPR_NULL, 0,  0, A_Repeat,       7, S_EGGMOBILE4_MACE_DIE1, S_SONIC3KBOSSEXPLOSION1, 0},

	// Boss 4 jet flame
	{"JETFLAME", 0, SPR_EFIR, FF_FULLBRIGHT|FF_ANIMATE, -1, NULL, 1, 1, S_NULL, 0},

	// Boss 4 Spectator Eggrobo
	{"EGGROBO1_STND", 0, SPR_EGR1,            0, -1, NULL, 0, 0, S_NULL, 0},
	{"EGGROBO1_BSLAP1", 0, SPR_EGR1,            5,  2, NULL, 0, 0, S_EGGROBO1_BSLAP2, 0},
	{"EGGROBO1_BSLAP2", 0, SPR_EGR1, FF_ANIMATE|6, 35, NULL, 1, 2, S_EGGROBO1_STND, 0},
	{"EGGROBO1_PISSED", 0, SPR_EGR1, FF_ANIMATE|3, -1, NULL, 1, 2, S_NULL, 0},

	// Boss 4 Spectator Eggrobo jet flame
	{"EGGROBOJET", 0, SPR_EFIR, FF_FULLBRIGHT|2,          -1, NULL, 0, 0, S_NULL, 0},

	// Boss 5
	{"FANG_SETUP", 0, SPR_NULL, 0, 2, A_CheckFlags2, MF2_AMBUSH, S_FANG_IDLE0, S_FANG_INTRO0, 0},

	{"FANG_INTRO0", 0, SPR_NULL,         0, 2, NULL, 0, 0, S_FANG_INTRO1, 0},
	{"FANG_INTRO1", 0, SPR_NULL,         0, 2, A_Boss5MakeJunk, -S_FANG_CLONE1, 0, S_FANG_INTRO2, 0},
	{"FANG_INTRO2", 0, SPR_NULL,         0, 0, A_Repeat, 25, S_FANG_INTRO1, S_FANG_INTRO3, 0},
	{"FANG_INTRO3", 0, SPR_NULL,         0, 0, A_Boss5MakeJunk, 0, 1, S_FANG_INTRO4, 0},
	{"FANG_INTRO4", 0, SPR_PLAY, SPR2_ROLL, 1, A_ZThrust, 9, (1<<16)|1, S_FANG_INTRO5, 0},
	{"FANG_INTRO5", 0, SPR_PLAY, SPR2_ROLL, 1, A_Boss5CheckOnGround, S_FANG_INTRO9, 0, S_FANG_INTRO6, 0},
	{"FANG_INTRO6", 0, SPR_PLAY, SPR2_ROLL, 1, A_Boss5CheckOnGround, S_FANG_INTRO9, 0, S_FANG_INTRO7, 0},
	{"FANG_INTRO7", 0, SPR_PLAY, SPR2_ROLL, 1, A_Boss5CheckOnGround, S_FANG_INTRO9, 0, S_FANG_INTRO8, 0},
	{"FANG_INTRO8", 0, SPR_PLAY, SPR2_ROLL, 1, A_Boss5CheckOnGround, S_FANG_INTRO9, 0, S_FANG_INTRO5, 0},
	{"FANG_INTRO9", 0, SPR_PLAY, SPR2_MSC0|FF_ANIMATE, 50, NULL, 0, 4, S_FANG_INTRO10, 0},
	{"FANG_INTRO10", 0, SPR_PLAY, SPR2_MSC1, 5, NULL, 0, 0, S_FANG_INTRO11, 0},
	{"FANG_INTRO11", 0, SPR_PLAY, SPR2_MSC2, 2, A_Boss5MakeJunk, S_BROKENROBOTD, 2, S_FANG_INTRO12, 0},
	{"FANG_INTRO12", 0, SPR_PLAY, SPR2_CNT1|FF_ANIMATE, 50, NULL, 0, 4, S_FANG_IDLE1, 0},

	{"FANG_CLONE1", 0, SPR_PLAY, SPR2_SPNG, 2, A_Boss5MakeJunk, 0, -1, S_FANG_CLONE2, 0},
	{"FANG_CLONE2", 0, SPR_PLAY, SPR2_SPNG, 0, A_Repeat, 49, S_FANG_CLONE1, S_FANG_CLONE3, 0},
	{"FANG_CLONE3", 0, SPR_PLAY, SPR2_FALL, 0, A_SetObjectFlags, MF_NOGRAVITY, 1, S_FANG_CLONE4, 0},
	{"FANG_CLONE4", 0, SPR_PLAY, SPR2_FALL, 1, A_Boss5CheckOnGround, S_FANG_IDLE0, 0, S_FANG_CLONE4, 0},

	{"FANG_IDLE0", 0, SPR_PLAY,         0,  0, A_SetObjectFlags, MF_NOCLIPTHING, 1, S_FANG_IDLE1, 0},
	{"FANG_IDLE1", 0, SPR_PLAY, SPR2_WAIT, 16, A_Look, 1, 0, S_FANG_IDLE2, 0},
	{"FANG_IDLE2", 0, SPR_PLAY, SPR2_WAIT, 16, A_Look, 1, 0, S_FANG_IDLE3, 0},
	{"FANG_IDLE3", 0, SPR_PLAY, SPR2_WAIT, 16, A_Look, 1, 0, S_FANG_IDLE4, 0},
	{"FANG_IDLE4", 0, SPR_PLAY, SPR2_WAIT, 16, A_Look, 1, 0, S_FANG_IDLE5, 0},
	{"FANG_IDLE5", 0, SPR_PLAY, SPR2_WAIT, 16, A_Look, 1, 0, S_FANG_IDLE6, 0},
	{"FANG_IDLE6", 0, SPR_PLAY, SPR2_WAIT, 16, A_Look, 1, 0, S_FANG_IDLE7, 0},
	{"FANG_IDLE7", 0, SPR_PLAY, SPR2_WAIT, 16, A_Look, 1, 0, S_FANG_IDLE8, 0},
	{"FANG_IDLE8", 0, SPR_PLAY, SPR2_WAIT, 16, A_Look, 1, 0, S_FANG_IDLE1, 0},

	{"FANG_PAIN1", 0, SPR_PLAY,         0, 0, A_DoNPCPain, FRACUNIT, 0, S_FANG_PAIN2, 0},
	{"FANG_PAIN2", 0, SPR_PLAY, SPR2_PAIN, 1, A_Boss5CheckOnGround, S_FANG_PATHINGSTART1, S_FANG_PINCHPATHINGSTART1, S_FANG_PAIN2, 0},

	{"FANG_PATHINGSTART1", 0, SPR_PLAY,         0, 0, A_Boss5ExtraRepeat, 5, 4, S_FANG_PATHINGSTART2, 0},
	{"FANG_PATHINGSTART2", 0, SPR_PLAY,         0, 0, A_PlayActiveSound, 0, 0, S_FANG_PATHING, 0},
	{"FANG_PATHING", 0, SPR_PLAY,         0, 0, A_Boss5FindWaypoint, 0, 0, S_FANG_BOUNCE1, 0},

	{"FANG_BOUNCE1", 0, SPR_PLAY, SPR2_LAND, 2, A_Thrust, 0, 1, S_FANG_BOUNCE2, 0},
	{"FANG_BOUNCE2", 0, SPR_PLAY, SPR2_LAND, 2, NULL, 0, 0, S_FANG_BOUNCE3, 0},
	{"FANG_BOUNCE3", 0, SPR_PLAY, SPR2_LAND, 1, A_Boss5Jump, 0, 0, S_FANG_BOUNCE4, 0},
	{"FANG_BOUNCE4", 0, SPR_PLAY, SPR2_BNCE, 1, A_Boss5CheckFalling, S_FANG_CHECKPATH1, S_FANG_FALL1, S_FANG_BOUNCE4, 0},

	{"FANG_FALL1", 0, SPR_PLAY, SPR2_FALL, 1, A_Boss5CheckOnGround, S_FANG_CHECKPATH1, 0, S_FANG_FALL2, 0},
	{"FANG_FALL2", 0, SPR_PLAY, SPR2_FALL, 1, A_Boss5CheckOnGround, S_FANG_CHECKPATH1, 0, S_FANG_FALL1, 0},

	{"FANG_CHECKPATH1", 0, SPR_PLAY,         0, 0, A_Boss5Calm, 0, 0, S_FANG_CHECKPATH2, 0},
	{"FANG_CHECKPATH2", 0, SPR_PLAY,         0, 0, A_Repeat, 0, S_FANG_PATHINGCONT1, S_FANG_SKID1, 0},

	{"FANG_PATHINGCONT1", 0, SPR_PLAY,         0, 0, A_Boss5PinchShot, MT_FBOMB, -16, S_FANG_PATHINGCONT2, 0},
	{"FANG_PATHINGCONT2", 0, SPR_PLAY,         0, 0, A_PlayActiveSound, 0, 0, S_FANG_PATHINGCONT3, 0},
	{"FANG_PATHINGCONT3", 0, SPR_PLAY, SPR2_LAND, 2, A_Thrust, 0, 1, S_FANG_PATHING, 0},

	{"FANG_SKID1", 0, SPR_PLAY,         0,  0, A_PlayAttackSound, 0, 0, S_FANG_SKID2, 0},
	{"FANG_SKID2", 0, SPR_PLAY, SPR2_SKID,  1, A_DoNPCSkid, S_FANG_SKID3, 0, S_FANG_SKID2, 0},
	{"FANG_SKID3", 0, SPR_PLAY, SPR2_SKID, 10, NULL, 0, 0, S_FANG_CHOOSEATTACK, 0},

	{"FANG_CHOOSEATTACK", 0, SPR_PLAY,         0, 0, A_RandomState, S_FANG_LOBSHOT0, S_FANG_FIRESTART1, S_NULL, 0},

	{"FANG_FIRESTART1", 0, SPR_PLAY,         0,  0, A_PrepareRepeat, 3, 0, S_FANG_FIRESTART2, 0},
	{"FANG_FIRESTART2", 0, SPR_PLAY, SPR2_FIRE, 18, A_LookForBetter, 1, 0, S_FANG_FIRE1, 0},
	{"FANG_FIRE1", 0, SPR_PLAY, SPR2_FIRE,  2, A_FireShot, MT_CORK, -16, S_FANG_FIRE2, 0},
	{"FANG_FIRE2", 0, SPR_PLAY, SPR2_FIRE,  2, NULL, 0, 0, S_FANG_FIRE3, 0},
	{"FANG_FIRE3", 0, SPR_PLAY, SPR2_FIRE, 16, NULL, 0, 0, S_FANG_FIREREPEAT, 0},
	{"FANG_FIREREPEAT", 0, SPR_PLAY,         0,  0, A_Repeat, 3, S_FANG_FIRE1, S_FANG_WAIT1, 0},

	{"FANG_LOBSHOT0", 0, SPR_PLAY, SPR2_MSC3, 14, A_LookForBetter, 1, 0, S_FANG_LOBSHOT1, 0},
	{"FANG_LOBSHOT1", 0, SPR_PLAY, SPR2_MSC3,  2, A_LookForBetter, 1, 0, S_FANG_LOBSHOT2, 0},
	{"FANG_LOBSHOT2", 0, SPR_PLAY, SPR2_MSC3,  2, A_LookForBetter, 1, 0, S_FANG_LOBSHOT3, 0},
	{"FANG_LOBSHOT3", 0, SPR_PLAY, SPR2_MSC3, 18, A_BrakLobShot, MT_FBOMB, 32+(1<<16), S_FANG_WAIT1, 0},

	{"FANG_WAIT1", 0, SPR_PLAY, SPR2_MLEL|FF_ANIMATE, 70, NULL, 0, 5, S_FANG_WAIT2, 0},
	{"FANG_WAIT2", 0, SPR_PLAY,            SPR2_STND, 35, A_Look, 1, 0, S_FANG_IDLE1, 0},

	{"FANG_WALLHIT", 0, SPR_PLAY, SPR2_FALL, 1, A_Boss5CheckOnGround, S_FANG_PATHINGSTART2, S_FANG_PINCHPATHINGSTART1, S_FANG_WALLHIT, 0},

	{"FANG_PINCHPATHINGSTART1", 0, SPR_PLAY,         0,  0, A_PrepareRepeat, 1, 0, S_FANG_PINCHPATHINGSTART2, 0},
	{"FANG_PINCHPATHINGSTART2", 0, SPR_PLAY,         0,  0, A_PlayActiveSound, 0, 0, S_FANG_PINCHPATHING, 0},
	{"FANG_PINCHPATHING", 0, SPR_PLAY,         0,  0, A_Boss5FindWaypoint, 1, 0, S_FANG_PINCHBOUNCE0, 0},
	{"FANG_PINCHBOUNCE0", 0, SPR_PLAY,         0,  0, A_SetObjectFlags, MF_NOCLIP|MF_NOCLIPHEIGHT, 2, S_FANG_PINCHBOUNCE1, 0},
	{"FANG_PINCHBOUNCE1", 0, SPR_PLAY, SPR2_LAND,  2, A_Thrust, 0, 1, S_FANG_PINCHBOUNCE2, 0},
	{"FANG_PINCHBOUNCE2", 0, SPR_PLAY, SPR2_LAND,  2, NULL, 0, 0, S_FANG_PINCHBOUNCE3, 0},
	{"FANG_PINCHBOUNCE3", 0, SPR_PLAY, SPR2_LAND,  2, A_Boss5Jump, 0, 0, S_FANG_PINCHBOUNCE4, 0},
	{"FANG_PINCHBOUNCE4", 0, SPR_PLAY, SPR2_BNCE,  1, A_Boss5CheckFalling, S_FANG_PINCHSKID1, S_FANG_PINCHFALL0, S_FANG_PINCHBOUNCE4, 0},
	{"FANG_PINCHFALL0", 0, SPR_PLAY,         0,  0, A_SetObjectFlags, MF_NOCLIP|MF_NOCLIPHEIGHT, 1, S_FANG_PINCHFALL1, 0},
	{"FANG_PINCHFALL1", 0, SPR_PLAY, SPR2_FALL,  1, A_Boss5CheckOnGround, S_FANG_PINCHSKID1, 0, S_FANG_PINCHFALL2, 0},
	{"FANG_PINCHFALL2", 0, SPR_PLAY, SPR2_FALL,  1, A_Boss5CheckOnGround, S_FANG_PINCHSKID1, 0, S_FANG_PINCHFALL1, 0},
	{"FANG_PINCHSKID1", 0, SPR_PLAY,         0,  0, A_PlayAttackSound, 0, 0, S_FANG_PINCHSKID2, 0},
	{"FANG_PINCHSKID2", 0, SPR_PLAY, SPR2_SKID,  1, A_DoNPCSkid, S_FANG_PINCHLOBSHOT0, 0, S_FANG_PINCHSKID2, 0},
	{"FANG_PINCHLOBSHOT0", 0, SPR_PLAY, SPR2_MSC3, 16, A_FaceTarget, 1, 5, S_FANG_PINCHLOBSHOT1, 0},
	{"FANG_PINCHLOBSHOT1", 0, SPR_PLAY, SPR2_MSC3,  2, A_FaceTarget, 3, 0, S_FANG_PINCHLOBSHOT2, 0},
	{"FANG_PINCHLOBSHOT2", 0, SPR_PLAY, SPR2_MSC3,  2, A_FaceTarget, 3, 0, S_FANG_PINCHLOBSHOT3, 0},
	{"FANG_PINCHLOBSHOT3", 0, SPR_PLAY, SPR2_MSC3, 30, A_Boss5MakeItRain, MT_FBOMB, -16, S_FANG_PINCHLOBSHOT4, 0},
	{"FANG_PINCHLOBSHOT4", 0, SPR_PLAY, SPR2_STND, 18, A_LinedefExecuteFromArg, 4, 0, S_FANG_PINCHLOBSHOT5, 0},
	{"FANG_PINCHLOBSHOT5", 0, SPR_PLAY,         0,  0, A_Boss5Calm, 0, 0, S_FANG_PATHINGSTART1, 0},

	{"FANG_DIE1", 0, SPR_PLAY,         0, 0, A_DoNPCPain,                    0, 0, S_FANG_DIE2, 0},
	{"FANG_DIE2", 0, SPR_PLAY, SPR2_MSC4, 1, A_Boss5CheckOnGround, S_FANG_DIE3, 0, S_FANG_DIE2, 0},

	{"FANG_DIE3", 0, SPR_PLAY,         0,  0, A_Scream, 0, 0, S_FANG_DIE4, 0},
	{"FANG_DIE4", 0, SPR_PLAY, SPR2_MSC5, -1, A_SetFuse, 70, 0, S_FANG_DIE5, 0},

	{"FANG_DIE5", 0, SPR_PLAY,         0, 0, A_PlaySound, sfx_jump, 0, S_FANG_DIE6, 0},
	{"FANG_DIE6", 0, SPR_PLAY, SPR2_JUMP, 1, A_ZThrust, 6, (1<<16)|1, S_FANG_DIE7, 0},
	{"FANG_DIE7", 0, SPR_PLAY, SPR2_JUMP, 1, A_Boss5CheckFalling, S_FANG_FLEEPATHING1, S_FANG_DIE8, S_FANG_DIE7, 0},
	{"FANG_DIE8", 0, SPR_PLAY, SPR2_FALL, 1, A_Boss5CheckOnGround, S_FANG_FLEEPATHING1, 0, S_FANG_DIE8, 0},

	{"FANG_FLEEPATHING1", 0, SPR_PLAY,         0,  0, A_PlayActiveSound, 0, 0, S_FANG_FLEEPATHING2, 0},
	{"FANG_FLEEPATHING2", 0, SPR_PLAY, SPR2_LAND,  2, A_Boss5FindWaypoint, 2, 0, S_FANG_FLEEBOUNCE1, 0},
	{"FANG_FLEEBOUNCE1", 0, SPR_PLAY, SPR2_LAND,  2, NULL, 0, 0, S_FANG_FLEEBOUNCE2, 0},
	{"FANG_FLEEBOUNCE2", 0, SPR_PLAY, SPR2_LAND, -1, A_BossDeath, 0, 0, S_NULL, 0},

	{"FANG_KO", 0, SPR_PLAY, SPR2_DEAD, 7*TICRATE, NULL, 0, 0, S_NULL, 0},

	{"BROKENROBOTRANDOM", 0, SPR_NULL, 0, -1, A_RandomStateRange, S_BROKENROBOTA, S_BROKENROBOTF, S_NULL, 0},
	{"BROKENROBOTA", 0, SPR_BRKN,    FF_ANIMATE|FF_RANDOMANIM, -1, NULL, 3, 4, S_NULL, 0},
	{"BROKENROBOTB", 0, SPR_BRKN,  4|FF_ANIMATE|FF_RANDOMANIM, -1, NULL, 3, 4, S_NULL, 0},
	{"BROKENROBOTC", 0, SPR_BRKN,  8|FF_ANIMATE|FF_RANDOMANIM, -1, NULL, 3, 4, S_NULL, 0},
	{"BROKENROBOTD", 0, SPR_BRKN, 12|FF_ANIMATE|FF_RANDOMANIM, -1, NULL, 3, 4, S_NULL, 0},
	{"BROKENROBOTE", 0, SPR_BRKN, 16|FF_ANIMATE|FF_RANDOMANIM, -1, NULL, 3, 4, S_NULL, 0},
	{"BROKENROBOTF", 0, SPR_BRKN, 20|FF_ANIMATE|FF_RANDOMANIM, -1, NULL, 3, 4, S_NULL, 0},

	{"ALART1", 0, SPR_WHAT,   FF_ANIMATE|FF_FULLBRIGHT,  4, NULL, 1, 2, S_ALART2, 0},
	{"ALART2", 0, SPR_WHAT, 2|FF_ANIMATE|FF_FULLBRIGHT, -1, NULL, 1, 2, S_NULL, 0},

	{"VWREF", 0, SPR_VWRE,   FF_FULLBRIGHT, -1, NULL, 0, 0, S_NULL, 0},
	{"VWREB", 0, SPR_VWRE, 1|FF_FULLBRIGHT, -1, NULL, 0, 0, S_NULL, 0},

	{"PROJECTORLIGHT1", 0, SPR_PROJ,   FF_TRANS20|FF_FULLBRIGHT,  4, NULL, 0, 0, S_PROJECTORLIGHT2, 0},
	{"PROJECTORLIGHT2", 0, SPR_PROJ, 1|FF_TRANS40|FF_FULLBRIGHT,  1, NULL, 0, 0, S_PROJECTORLIGHT3, 0},
	{"PROJECTORLIGHT3", 0, SPR_PROJ, 2|FF_TRANS20|FF_FULLBRIGHT,  1, NULL, 0, 0, S_PROJECTORLIGHT4, 0},
	{"PROJECTORLIGHT4", 0, SPR_PROJ, 3|FF_TRANS40|FF_FULLBRIGHT,  2, A_Repeat, 39, S_PROJECTORLIGHT2, S_PROJECTORLIGHT5, 0},
	{"PROJECTORLIGHT5", 0, SPR_PROJ, 4|FF_TRANS60|FF_FULLBRIGHT,  2, NULL, 0, 0, S_NULL, 0},

	{"FBOMB1", 0, SPR_FBOM, 0, 1, A_GhostMe, 0, 0, S_FBOMB2, 0},
	{"FBOMB2", 0, SPR_FBOM, 1, 1, A_GhostMe, 0, 0, S_FBOMB1, 0},
	{"FBOMB_EXPL1", 0, SPR_BARX, 0|FF_FULLBRIGHT, 3, A_SetObjectFlags, MF_NOCLIP|MF_NOGRAVITY|MF_NOBLOCKMAP, 0, S_FBOMB_EXPL2, 0},
	{"FBOMB_EXPL2", 0, SPR_BARX, 1|FF_FULLBRIGHT, 2, A_Boss5BombExplode, MT_TNTDUST, 0, S_FBOMB_EXPL3, 0},
	{"FBOMB_EXPL3", 0, SPR_BARX, 1|FF_FULLBRIGHT, 1, NULL, 0, 0, S_FBOMB_EXPL4, 0},
	{"FBOMB_EXPL4", 0, SPR_BARX, 2|FF_FULLBRIGHT, 3, NULL, 0, 0, S_FBOMB_EXPL5, 0},
	{"FBOMB_EXPL5", 0, SPR_BARX, 3|FF_FULLBRIGHT, 3, NULL, 0, 0, S_FBOMB_EXPL6, 0},
	{"FBOMB_EXPL6", 0, SPR_NULL, 0, 2*TICRATE, NULL, 0, 0, S_NULL, 0},
	{"TNTDUST_1", 0, SPR_BARD, 0|FF_TRANS90, 2, NULL, 0, 0, S_TNTDUST_2, 0},
	{"TNTDUST_2", 0, SPR_BARD, 0|FF_TRANS30, 2*TICRATE, A_SetRandomTics, 2, TICRATE, S_TNTDUST_3, 0},
	{"TNTDUST_3", 0, SPR_BARD, 0|FF_TRANS40, 10, NULL, 0, 0, S_TNTDUST_4, 0},
	{"TNTDUST_4", 0, SPR_BARD, 0|FF_TRANS50, 10, NULL, 0, 0, S_TNTDUST_5, 0},
	{"TNTDUST_5", 0, SPR_BARD, 0|FF_TRANS60, 10, NULL, 0, 0, S_TNTDUST_6, 0},
	{"TNTDUST_6", 0, SPR_BARD, 0|FF_TRANS70, 10, NULL, 0, 0, S_TNTDUST_7, 0},
	{"TNTDUST_7", 0, SPR_BARD, 0|FF_TRANS80, 10, NULL, 0, 0, S_TNTDUST_8, 0},
	{"TNTDUST_8", 0, SPR_BARD, 0|FF_TRANS90, 10, NULL, 0, 0, S_NULL, 0},
	{"FSGNA", 0, SPR_FSGN, 0|FF_PAPERSPRITE, -1, NULL, 0, 0, S_NULL, 0},
	{"FSGNB", 0, SPR_FSGN, 1|FF_PAPERSPRITE, -1, NULL, 0, 0, S_NULL, 0},
	{"FSGNC", 0, SPR_FSGN, 2|FF_PAPERSPRITE, -1, NULL, 0, 0, S_NULL, 0},
	{"FSGND", 0, SPR_FSGN, 3|FF_PAPERSPRITE, -1, NULL, 0, 0, S_NULL, 0},

	// Black Eggman (Boss 7)
	{"BLACKEGG_STND", 0, SPR_BRAK, 0, 1, A_SetReactionTime, 0, 0, S_BLACKEGG_STND2, 0},
	{"BLACKEGG_STND2", 0, SPR_BRAK, 0, 7, A_Look, 1, 0, S_BLACKEGG_STND2, 0},
	{"BLACKEGG_WALK1", 0, SPR_BRAK, 1, 7, NULL, 0, 0, S_BLACKEGG_WALK2, 0},
	{"BLACKEGG_WALK2", 0, SPR_BRAK, 2, 7, NULL, 0, 0, S_BLACKEGG_WALK3, 0},
	{"BLACKEGG_WALK3", 0, SPR_BRAK, 3, 7, A_PlaySound, sfx_bestep, 0, S_BLACKEGG_WALK4, 0},
	{"BLACKEGG_WALK4", 0, SPR_BRAK, 4, 7, NULL, 0, 0, S_BLACKEGG_WALK5, 0},
	{"BLACKEGG_WALK5", 0, SPR_BRAK, 5, 7, NULL, 0, 0, S_BLACKEGG_WALK6, 0},
	{"BLACKEGG_WALK6", 0, SPR_BRAK, 6, 7, A_PlaySound, sfx_bestp2, 0, S_BLACKEGG_WALK1, 0},
	{"BLACKEGG_SHOOT1", 0, SPR_BRAK, 7, 3, NULL, 0, 0, S_BLACKEGG_SHOOT2, 0},
	{"BLACKEGG_SHOOT2", 0, SPR_BRAK, 24, 1, A_PlaySound, sfx_befire, 0, S_BLACKEGG_SHOOT1, 0},

	{"BLACKEGG_PAIN1", 0, SPR_BRAK, 8, 1, NULL, 0, 0, S_BLACKEGG_PAIN2, 0},
	{"BLACKEGG_PAIN2", 0, SPR_BRAK, 25, 1, NULL, 0, 0, S_BLACKEGG_PAIN3, 0},
	{"BLACKEGG_PAIN3", 0, SPR_BRAK, 8, 1, NULL, 0, 0, S_BLACKEGG_PAIN4, 0},
	{"BLACKEGG_PAIN4", 0, SPR_BRAK, 25, 1, NULL, 0, 0, S_BLACKEGG_PAIN5, 0},
	{"BLACKEGG_PAIN5", 0, SPR_BRAK, 8, 1, NULL, 0, 0, S_BLACKEGG_PAIN6, 0},
	{"BLACKEGG_PAIN6", 0, SPR_BRAK, 25, 1, NULL, 0, 0, S_BLACKEGG_PAIN7, 0},
	{"BLACKEGG_PAIN7", 0, SPR_BRAK, 8, 1, NULL, 0, 0, S_BLACKEGG_PAIN8, 0},
	{"BLACKEGG_PAIN8", 0, SPR_BRAK, 25, 1, NULL, 0, 0, S_BLACKEGG_PAIN9, 0},
	{"BLACKEGG_PAIN9", 0, SPR_BRAK, 8, 1, NULL, 0, 0, S_BLACKEGG_PAIN10, 0},
	{"BLACKEGG_PAIN10", 0, SPR_BRAK, 25, 1, NULL, 0, 0, S_BLACKEGG_PAIN11, 0},
	{"BLACKEGG_PAIN11", 0, SPR_BRAK, 8, 1, NULL, 0, 0, S_BLACKEGG_PAIN12, 0},
	{"BLACKEGG_PAIN12", 0, SPR_BRAK, 25, 1, NULL, 0, 0, S_BLACKEGG_PAIN13, 0},
	{"BLACKEGG_PAIN13", 0, SPR_BRAK, 8, 1, NULL, 0, 0, S_BLACKEGG_PAIN14, 0},
	{"BLACKEGG_PAIN14", 0, SPR_BRAK, 25, 1, NULL, 0, 0, S_BLACKEGG_PAIN15, 0},
	{"BLACKEGG_PAIN15", 0, SPR_BRAK, 8, 1, NULL, 0, 0, S_BLACKEGG_PAIN16, 0},
	{"BLACKEGG_PAIN16", 0, SPR_BRAK, 25, 1, NULL, 0, 0, S_BLACKEGG_PAIN17, 0},
	{"BLACKEGG_PAIN17", 0, SPR_BRAK, 8, 1, NULL, 0, 0, S_BLACKEGG_PAIN18, 0},
	{"BLACKEGG_PAIN18", 0, SPR_BRAK, 25, 1, NULL, 0, 0, S_BLACKEGG_PAIN19, 0},
	{"BLACKEGG_PAIN19", 0, SPR_BRAK, 8, 1, NULL, 0, 0, S_BLACKEGG_PAIN20, 0},
	{"BLACKEGG_PAIN20", 0, SPR_BRAK, 25, 1, NULL, 0, 0, S_BLACKEGG_PAIN21, 0},
	{"BLACKEGG_PAIN21", 0, SPR_BRAK, 8, 1, NULL, 0, 0, S_BLACKEGG_PAIN22, 0},
	{"BLACKEGG_PAIN22", 0, SPR_BRAK, 25, 1, NULL, 0, 0, S_BLACKEGG_PAIN23, 0},
	{"BLACKEGG_PAIN23", 0, SPR_BRAK, 8, 1, NULL, 0, 0, S_BLACKEGG_PAIN24, 0},
	{"BLACKEGG_PAIN24", 0, SPR_BRAK, 25, 1, NULL, 0, 0, S_BLACKEGG_PAIN25, 0},
	{"BLACKEGG_PAIN25", 0, SPR_BRAK, 8, 1, NULL, 0, 0, S_BLACKEGG_PAIN26, 0},
	{"BLACKEGG_PAIN26", 0, SPR_BRAK, 25, 1, NULL, 0, 0, S_BLACKEGG_PAIN27, 0},
	{"BLACKEGG_PAIN27", 0, SPR_BRAK, 8, 1, NULL, 0, 0, S_BLACKEGG_PAIN28, 0},
	{"BLACKEGG_PAIN28", 0, SPR_BRAK, 25, 1, NULL, 0, 0, S_BLACKEGG_PAIN29, 0},
	{"BLACKEGG_PAIN29", 0, SPR_BRAK, 8, 1, NULL, 0, 0, S_BLACKEGG_PAIN30, 0},
	{"BLACKEGG_PAIN30", 0, SPR_BRAK, 25, 1, NULL, 0, 0, S_BLACKEGG_PAIN31, 0},
	{"BLACKEGG_PAIN31", 0, SPR_BRAK, 8, 1, NULL, 0, 0, S_BLACKEGG_PAIN32, 0},
	{"BLACKEGG_PAIN32", 0, SPR_BRAK, 25, 1, NULL, 0, 0, S_BLACKEGG_PAIN33, 0},
	{"BLACKEGG_PAIN33", 0, SPR_BRAK, 8, 1, NULL, 0, 0, S_BLACKEGG_PAIN34, 0},
	{"BLACKEGG_PAIN34", 0, SPR_BRAK, 25, 1, NULL, 0, 0, S_BLACKEGG_PAIN35, 0},
	{"BLACKEGG_PAIN35", 0, SPR_BRAK, 8, 1, NULL, 0, 0, S_BLACKEGG_WALK1, 0},

	{"BLACKEGG_HITFACE1", 0, SPR_BRAK, 9, 20, NULL, 0, 0, S_BLACKEGG_HITFACE2, 0},
	{"BLACKEGG_HITFACE2", 0, SPR_BRAK, 10, 2, NULL, 0, 0, S_BLACKEGG_HITFACE3, 0},
	{"BLACKEGG_HITFACE3", 0, SPR_BRAK, 11, 2, NULL, 0, 0, S_BLACKEGG_HITFACE4, 0},
	{"BLACKEGG_HITFACE4", 0, SPR_BRAK, 12,14, NULL, 0, 0, S_BLACKEGG_PAIN1, 0},

	{"BLACKEGG_DIE1", 0, SPR_BRAK, 13, 14, NULL, 0, 0, S_BLACKEGG_DIE2, 0},
	{"BLACKEGG_DIE2", 0, SPR_BRAK, 14, 7, NULL, 0, 0, S_BLACKEGG_DIE3, 0},
	{"BLACKEGG_DIE3", 0, SPR_BRAK, 15, 5, NULL, 0, 0, S_BLACKEGG_DIE4, 0},
	{"BLACKEGG_DIE4", 0, SPR_BRAK, 16, 3, A_PlaySound, sfx_bgxpld, 0, S_BLACKEGG_DIE5, 0},
	{"BLACKEGG_DIE5", 0, SPR_BRAK, 17, -1, NULL, 0, 0, S_BLACKEGG_DIE5, 0},

	{"BLACKEGG_MISSILE1", 0, SPR_BRAK, 18, 14, NULL, 0, 0, S_BLACKEGG_MISSILE2, 0},
	{"BLACKEGG_MISSILE2", 0, SPR_BRAK, 19, 5, NULL, 0, 0, S_BLACKEGG_MISSILE3, 0},
	{"BLACKEGG_MISSILE3", 0, SPR_BRAK, 20, 35, A_Boss7FireMissiles, MT_BLACKEGGMAN_MISSILE, sfx_beshot, S_BLACKEGG_JUMP1, 0},

	{"BLACKEGG_GOOP", 0, SPR_BRAK, 21, -1, NULL, 0, 0, S_BLACKEGG_STND, 0},

	{"BLACKEGG_JUMP1", 0, SPR_BRAK, 22, 14, A_PlaySound, sfx_belnch, 0, S_BLACKEGG_JUMP2, 0},
	{"BLACKEGG_JUMP2", 0, SPR_BRAK, 23, -1, NULL, 0, 0, S_BLACKEGG_WALK1, 0},

	{"BLACKEGG_DESTROYPLAT1", 0, SPR_BRAK, 21, 3*TICRATE, NULL, 0, 0, S_BLACKEGG_DESTROYPLAT2, 0},
	{"BLACKEGG_DESTROYPLAT2", 0, SPR_BRAK, 21, 1, A_PlaySound, sfx_s3k54, 0, S_BLACKEGG_DESTROYPLAT3, 0},
	{"BLACKEGG_DESTROYPLAT3", 0, SPR_BRAK, 21, 14, A_LinedefExecuteFromArg, 5, 0, S_BLACKEGG_STND, 0},

	{"BLACKEGG_HELPER", 0, SPR_NULL, 0, 1, A_CapeChase, (160 - 20) << 16, 0, S_BLACKEGG_HELPER, 0},

	{"BLACKEGG_GOOP1", 0, SPR_BGOO, FF_TRANS50  , 2, NULL, 0, 0, S_BLACKEGG_GOOP2, 0},
	{"BLACKEGG_GOOP2", 0, SPR_BGOO, FF_TRANS50|1, 2, NULL, 0, 0, S_BLACKEGG_GOOP1, 0},
	{"BLACKEGG_GOOP3", 0, SPR_BGOO, FF_TRANS50|2, 6*TICRATE, A_GoopSplat, 0, 0, S_BLACKEGG_GOOP4, 0},
	{"BLACKEGG_GOOP4", 0, SPR_BGOO, FF_TRANS60|2, 4, NULL, 0, 0, S_BLACKEGG_GOOP5, 0},
	{"BLACKEGG_GOOP5", 0, SPR_BGOO, FF_TRANS70|2, 4, NULL, 0, 0, S_BLACKEGG_GOOP6, 0},
	{"BLACKEGG_GOOP6", 0, SPR_BGOO, FF_TRANS80|2, 4, NULL, 0, 0, S_BLACKEGG_GOOP7, 0},
	{"BLACKEGG_GOOP7", 0, SPR_BGOO, FF_TRANS90|2, 4, NULL, 0, 0, S_NULL, 0},

	{"BLACKEGG_MISSILE", 0, SPR_BMSL, 0, 1, NULL, 0, 0, S_BLACKEGG_MISSILE, 0},

	// New Very-Last-Minute 2.1 Brak Eggman (Cy-Brak-demon)
	{"CYBRAKDEMON_IDLE", 0, SPR_BRAK, 0, 10, A_Look, 0, 0, S_CYBRAKDEMON_IDLE, 0},
	{"CYBRAKDEMON_WALK1", 0, SPR_BRAK, 1, 8, A_BrakChase, 3, 0, S_CYBRAKDEMON_WALK2, 0},
	{"CYBRAKDEMON_WALK2", 0, SPR_BRAK, 2, 8, A_BrakChase, 3, 0, S_CYBRAKDEMON_WALK3, 0},
	{"CYBRAKDEMON_WALK3", 0, SPR_BRAK, 3, 8, A_BrakChase, 3, sfx_bestep, S_CYBRAKDEMON_WALK4, 0},
	{"CYBRAKDEMON_WALK4", 0, SPR_BRAK, 4, 8, A_BrakChase, 3, 0, S_CYBRAKDEMON_WALK5, 0},
	{"CYBRAKDEMON_WALK5", 0, SPR_BRAK, 5, 8, A_BrakChase, 3, 0, S_CYBRAKDEMON_WALK6, 0},
	{"CYBRAKDEMON_WALK6", 0, SPR_BRAK, 6, 8, A_BrakChase, 3, sfx_bestp2, S_CYBRAKDEMON_WALK1, 0},
	{"CYBRAKDEMON_CHOOSE_ATTACK1", 0, SPR_BRAK, 7, 6, A_RandomState, S_CYBRAKDEMON_MISSILE_ATTACK1, S_CYBRAKDEMON_FLAME_ATTACK1, S_CYBRAKDEMON_MISSILE_ATTACK1, 0},
	{"CYBRAKDEMON_MISSILE_ATTACK1", 0, SPR_BRAK, 7, 6, A_FaceTarget, 0, 0, S_CYBRAKDEMON_MISSILE_ATTACK2, 0},  // Aim
	{"CYBRAKDEMON_MISSILE_ATTACK2", 0, SPR_BRAK, 26 + FF_FULLBRIGHT, 12, A_BrakFireShot, MT_CYBRAKDEMON_MISSILE, 128, S_CYBRAKDEMON_MISSILE_ATTACK3, 0},  // Fire
	{"CYBRAKDEMON_MISSILE_ATTACK3", 0, SPR_BRAK, 7, 12, A_FaceTarget, 0, 0, S_CYBRAKDEMON_MISSILE_ATTACK4, 0},  // Aim
	{"CYBRAKDEMON_MISSILE_ATTACK4", 0, SPR_BRAK, 26 + FF_FULLBRIGHT, 12, A_BrakFireShot, MT_CYBRAKDEMON_MISSILE, 128, S_CYBRAKDEMON_MISSILE_ATTACK5, 0},  // Fire
	{"CYBRAKDEMON_MISSILE_ATTACK5", 0, SPR_BRAK, 7, 12, A_FaceTarget, 0, 0, S_CYBRAKDEMON_MISSILE_ATTACK6, 0},  // Aim
	{"CYBRAKDEMON_MISSILE_ATTACK6", 0, SPR_BRAK, 26 + FF_FULLBRIGHT, 12, A_BrakFireShot, MT_CYBRAKDEMON_MISSILE, 128, S_CYBRAKDEMON_FINISH_ATTACK1, 0},  // Fire
	{"CYBRAKDEMON_FLAME_ATTACK1", 0, SPR_BRAK, 7, 1, A_Repeat, 1, S_CYBRAKDEMON_FLAME_ATTACK1, S_CYBRAKDEMON_FLAME_ATTACK2, 0},  // Reset
	{"CYBRAKDEMON_FLAME_ATTACK2", 0, SPR_BRAK, 7, 6, A_FaceTarget, 0, 0, S_CYBRAKDEMON_FLAME_ATTACK3, 0},  // Aim
	{"CYBRAKDEMON_FLAME_ATTACK3", 0, SPR_BRAK, 26 + FF_FULLBRIGHT, 2, A_BrakFireShot, MT_CYBRAKDEMON_FLAMESHOT, 128, S_CYBRAKDEMON_FLAME_ATTACK4, 0},  // Fire
	{"CYBRAKDEMON_FLAME_ATTACK4", 0, SPR_BRAK, 7, 1, A_Repeat, 30, S_CYBRAKDEMON_FLAME_ATTACK3, S_CYBRAKDEMON_FINISH_ATTACK1, 0},  // Loop
	{"CYBRAKDEMON_CHOOSE_ATTACK2", 0, SPR_BRAK, 0, 6, A_RandomState, S_CYBRAKDEMON_VILE_ATTACK1, S_CYBRAKDEMON_NAPALM_ATTACK1, S_CYBRAKDEMON_MISSILE_ATTACK1, 0},
	{"CYBRAKDEMON_VILE_ATTACK1", 0, SPR_BRAK, 20, 0, A_LinedefExecuteFromArg, 5, 0, S_CYBRAKDEMON_VILE_ATTACK2, 0},
	{"CYBRAKDEMON_VILE_ATTACK2", 0, SPR_BRAK, 20, 24, A_VileTarget, MT_CYBRAKDEMON_TARGET_RETICULE, 1, S_CYBRAKDEMON_VILE_ATTACK3, 0},
	{"CYBRAKDEMON_VILE_ATTACK3", 0, SPR_BRAK, 19, 8, A_FaceTarget, 0, 0, S_CYBRAKDEMON_VILE_ATTACK4, 0},
	{"CYBRAKDEMON_VILE_ATTACK4", 0, SPR_BRAK, 18, 8, A_FaceTarget, 0, 0, S_CYBRAKDEMON_VILE_ATTACK5, 0},
	{"CYBRAKDEMON_VILE_ATTACK5", 0, SPR_BRAK, 8, 32, A_FaceTarget, 0, 0, S_CYBRAKDEMON_VILE_ATTACK6, 0},
	{"CYBRAKDEMON_VILE_ATTACK6", 0, SPR_BRAK, 20 + FF_FULLBRIGHT, 28, A_VileAttack, sfx_brakrx, MT_CYBRAKDEMON_VILE_EXPLOSION + (1<<16), S_CYBRAKDEMON_FINISH_ATTACK1, 0},
	{"CYBRAKDEMON_NAPALM_ATTACK1", 0, SPR_BRAK, 0, 6, A_FaceTarget, 0, 0, S_CYBRAKDEMON_NAPALM_ATTACK2, 0},
	{"CYBRAKDEMON_NAPALM_ATTACK2", 0, SPR_BRAK, 21 + FF_FULLBRIGHT, 8, A_BrakLobShot, MT_CYBRAKDEMON_NAPALM_BOMB_LARGE, 96, S_CYBRAKDEMON_NAPALM_ATTACK3, 0},
	{"CYBRAKDEMON_NAPALM_ATTACK3", 0, SPR_BRAK, 0, 8, A_FaceTarget, 0, 0, S_CYBRAKDEMON_FINISH_ATTACK1, 0},
	{"CYBRAKDEMON_FINISH_ATTACK1", 0, SPR_BRAK, 0, 0, A_SetObjectFlags2, MF2_FRET, 1, S_CYBRAKDEMON_FINISH_ATTACK2, 0},  // If just attacked, remove MF2_FRET w/out going back to spawnstate
	{"CYBRAKDEMON_FINISH_ATTACK2", 0, SPR_BRAK, 0, 0, A_SetReactionTime, 0, 0, S_CYBRAKDEMON_WALK1, 0},  // If just attacked, remove MF2_FRET w/out going back to spawnstate
	{"CYBRAKDEMON_PAIN1", 0, SPR_BRAK, 18, 24, A_Pain, 0, 0, S_CYBRAKDEMON_PAIN2, 0},
	{"CYBRAKDEMON_PAIN2", 0, SPR_BRAK, 18, 0, A_CheckHealth, 3, S_CYBRAKDEMON_PAIN3, S_CYBRAKDEMON_CHOOSE_ATTACK1, 0},
	{"CYBRAKDEMON_PAIN3", 0, SPR_BRAK, 18, 0, A_LinedefExecuteFromArg, 4, 0, S_CYBRAKDEMON_CHOOSE_ATTACK1, 0},
	{"CYBRAKDEMON_DIE1", 0, SPR_BRAK, 18, 1, A_Repeat, 1, S_CYBRAKDEMON_DIE1, S_CYBRAKDEMON_DIE2, 0},
	{"CYBRAKDEMON_DIE2", 0, SPR_BRAK, 18, 2, A_BossScream, 2, 0, S_CYBRAKDEMON_DIE3, 0},
	{"CYBRAKDEMON_DIE3", 0, SPR_BRAK, 18, 0, A_Repeat, 52, S_CYBRAKDEMON_DIE2, S_CYBRAKDEMON_DIE4, 0},
	{"CYBRAKDEMON_DIE4", 0, SPR_BRAK, 13, 34, A_BossDeath, 0, 0, S_CYBRAKDEMON_DIE5, 0},
	{"CYBRAKDEMON_DIE5", 0, SPR_BRAK, 14, 34, NULL, 0, 0, S_CYBRAKDEMON_DIE6, 0},
	{"CYBRAKDEMON_DIE6", 0, SPR_BRAK, 15, 34, NULL, 0, 0, S_CYBRAKDEMON_DIE7, 0},
	{"CYBRAKDEMON_DIE7", 0, SPR_BRAK, 16, 34, NULL, 0, 0, S_CYBRAKDEMON_DIE8, 0},
	{"CYBRAKDEMON_DIE8", 0, SPR_BRAK, 17, 34, NULL, sfx_befall, 0, S_CYBRAKDEMON_DIE8, 0},
	{"CYBRAKDEMON_DEINVINCIBLERIZE", 0, SPR_BRAK, 0, 0, A_SetObjectFlags, MF_SPECIAL|MF_SHOOTABLE, 2, S_CYBRAKDEMON_IDLE, 0},
	{"CYBRAKDEMON_INVINCIBLERIZE", 0, SPR_BRAK, 0, 0, A_SetObjectFlags, MF_SPECIAL|MF_SHOOTABLE, 1, S_CYBRAKDEMON_IDLE, 0},

	{"CYBRAKDEMONMISSILE", 0, SPR_RCKT, 0 + FF_FULLBRIGHT, 1, A_SetObjectFlags2, MF2_RAILRING, 2, S_CYBRAKDEMONMISSILE, 0},
	{"CYBRAKDEMONMISSILE_EXPLODE1", 0, SPR_RCKT, 1 + FF_FULLBRIGHT, 8, A_Explode, 0, 0, S_CYBRAKDEMONMISSILE_EXPLODE2, 0},  //TODO: set missile mobj's "damage" to an appropriate radius
	{"CYBRAKDEMONMISSILE_EXPLODE2", 0, SPR_RCKT, 2 + FF_FULLBRIGHT, 6, A_NapalmScatter, MT_CYBRAKDEMON_NAPALM_FLAMES + (6<<16), 32 + (16<<16), S_CYBRAKDEMONMISSILE_EXPLODE3, 0},
	{"CYBRAKDEMONMISSILE_EXPLODE3", 0, SPR_RCKT, 3 + FF_FULLBRIGHT, 4, NULL, 0, 0, S_NULL, 0},

	{"CYBRAKDEMONFLAMESHOT_FLY1", 0, SPR_FLME, FF_FULLBRIGHT  , 15, NULL, 0, 0, S_CYBRAKDEMONFLAMESHOT_FLY2, 0},
	{"CYBRAKDEMONFLAMESHOT_FLY2", 0, SPR_FLME, FF_FULLBRIGHT|1, 15, NULL, 0, 0, S_CYBRAKDEMONFLAMESHOT_FLY3, 0},
	{"CYBRAKDEMONFLAMESHOT_FLY3", 0, SPR_FLME, FF_FULLBRIGHT|2, -1, NULL, 0, 0, S_CYBRAKDEMONFLAMESHOT_FLY3, 0},
	{"CYBRAKDEMONFLAMESHOT_DIE", 0, SPR_FLME, FF_FULLBRIGHT|2, 0, A_SpawnObjectRelative, 0, MT_CYBRAKDEMON_FLAMEREST, S_NULL, 0},

	{"CYBRAKDEMONFLAMEREST", 0, SPR_FLAM, FF_FULLBRIGHT, 1, A_SetFuse, 10*TICRATE, 0, S_FLAMEREST, 0},

	{"CYBRAKDEMONELECTRICBARRIER_INIT1", 0, SPR_ELEC, 0 + FF_FULLBRIGHT, 1, NULL, 0, 0, S_CYBRAKDEMONELECTRICBARRIER_INIT2, 0},
	{"CYBRAKDEMONELECTRICBARRIER_INIT2", 0, SPR_ELEC, 0 + FF_FULLBRIGHT, 0, A_RemoteAction, -1, S_CYBRAKDEMON_INVINCIBLERIZE, S_CYBRAKDEMONELECTRICBARRIER_PLAYSOUND, 0},
	{"CYBRAKDEMONELECTRICBARRIER_PLAYSOUND", 0, SPR_ELEC, 0 + FF_FULLBRIGHT, 0, A_PlayActiveSound, 0, 0, S_CYBRAKDEMONELECTRICBARRIER1, 0},
	{"CYBRAKDEMONELECTRICBARRIER1", 0, SPR_ELEC, 0 + FF_FULLBRIGHT, 1, A_CapeChase, 0, 0, S_CYBRAKDEMONELECTRICBARRIER2, 0},
	{"CYBRAKDEMONELECTRICBARRIER2", 0, SPR_ELEC, 0 + FF_FULLBRIGHT, 1, A_CapeChase, 0, 0, S_CYBRAKDEMONELECTRICBARRIER3, 0},
	{"CYBRAKDEMONELECTRICBARRIER3", 0, SPR_ELEC, 1 + FF_FULLBRIGHT, 1, A_CapeChase, 0, 0, S_CYBRAKDEMONELECTRICBARRIER4, 0},
	{"CYBRAKDEMONELECTRICBARRIER4", 0, SPR_ELEC, 1 + FF_FULLBRIGHT, 1, A_CapeChase, 0, 0, S_CYBRAKDEMONELECTRICBARRIER5, 0},
	{"CYBRAKDEMONELECTRICBARRIER5", 0, SPR_ELEC, 2 + FF_FULLBRIGHT, 1, A_CapeChase, 0, 0, S_CYBRAKDEMONELECTRICBARRIER6, 0},
	{"CYBRAKDEMONELECTRICBARRIER6", 0, SPR_ELEC, 2 + FF_FULLBRIGHT, 1, A_CapeChase, 0, 0, S_CYBRAKDEMONELECTRICBARRIER7, 0},
	{"CYBRAKDEMONELECTRICBARRIER7", 0, SPR_ELEC, 3 + FF_FULLBRIGHT, 1, A_CapeChase, 0, 0, S_CYBRAKDEMONELECTRICBARRIER8, 0},
	{"CYBRAKDEMONELECTRICBARRIER8", 0, SPR_ELEC, 3 + FF_FULLBRIGHT, 1, A_CapeChase, 0, 0, S_CYBRAKDEMONELECTRICBARRIER9, 0},
	{"CYBRAKDEMONELECTRICBARRIER9", 0, SPR_ELEC, 4 + FF_FULLBRIGHT, 1, A_CapeChase, 0, 0, S_CYBRAKDEMONELECTRICBARRIER10, 0},
	{"CYBRAKDEMONELECTRICBARRIER10", 0, SPR_ELEC, 4 + FF_FULLBRIGHT, 1, A_CapeChase, 0, 0, S_CYBRAKDEMONELECTRICBARRIER11, 0},
	{"CYBRAKDEMONELECTRICBARRIER11", 0, SPR_ELEC, 5 + FF_FULLBRIGHT, 1, A_CapeChase, 0, 0, S_CYBRAKDEMONELECTRICBARRIER12, 0},
	{"CYBRAKDEMONELECTRICBARRIER12", 0, SPR_ELEC, 5 + FF_FULLBRIGHT, 1, A_CapeChase, 0, 0, S_CYBRAKDEMONELECTRICBARRIER13, 0},
	{"CYBRAKDEMONELECTRICBARRIER13", 0, SPR_ELEC, 6 + FF_FULLBRIGHT, 1, A_CapeChase, 0, 0, S_CYBRAKDEMONELECTRICBARRIER14, 0},
	{"CYBRAKDEMONELECTRICBARRIER14", 0, SPR_ELEC, 6 + FF_FULLBRIGHT, 1, A_CapeChase, 0, 0, S_CYBRAKDEMONELECTRICBARRIER15, 0},
	{"CYBRAKDEMONELECTRICBARRIER15", 0, SPR_ELEC, 7 + FF_FULLBRIGHT, 1, A_CapeChase, 0, 0, S_CYBRAKDEMONELECTRICBARRIER16, 0},
	{"CYBRAKDEMONELECTRICBARRIER16", 0, SPR_ELEC, 7 + FF_FULLBRIGHT, 1, A_CapeChase, 0, 0, S_CYBRAKDEMONELECTRICBARRIER17, 0},
	{"CYBRAKDEMONELECTRICBARRIER17", 0, SPR_ELEC, 8 + FF_FULLBRIGHT, 1, A_CapeChase, 0, 0, S_CYBRAKDEMONELECTRICBARRIER18, 0},
	{"CYBRAKDEMONELECTRICBARRIER18", 0, SPR_ELEC, 8 + FF_FULLBRIGHT, 1, A_CapeChase, 0, 0, S_CYBRAKDEMONELECTRICBARRIER19, 0},
	{"CYBRAKDEMONELECTRICBARRIER19", 0, SPR_ELEC, 9 + FF_FULLBRIGHT, 1, A_CapeChase, 0, 0, S_CYBRAKDEMONELECTRICBARRIER20, 0},
	{"CYBRAKDEMONELECTRICBARRIER20", 0, SPR_ELEC, 9 + FF_FULLBRIGHT, 1, A_CapeChase, 0, 0, S_CYBRAKDEMONELECTRICBARRIER21, 0},
	{"CYBRAKDEMONELECTRICBARRIER21", 0, SPR_ELEC, 10 + FF_FULLBRIGHT, 1, A_CapeChase, 0, 0, S_CYBRAKDEMONELECTRICBARRIER22, 0},
	{"CYBRAKDEMONELECTRICBARRIER22", 0, SPR_ELEC, 10 + FF_FULLBRIGHT, 1, A_CapeChase, 0, 0, S_CYBRAKDEMONELECTRICBARRIER23, 0},
	{"CYBRAKDEMONELECTRICBARRIER23", 0, SPR_ELEC, 11 + FF_FULLBRIGHT, 1, A_CapeChase, 0, 0, S_CYBRAKDEMONELECTRICBARRIER24, 0},
	{"CYBRAKDEMONELECTRICBARRIER24", 0, SPR_ELEC, 11 + FF_FULLBRIGHT, 1, A_CapeChase, 0, 0, S_CYBRAKDEMONELECTRICBARRIER_PLAYSOUND, 0},
	{"CYBRAKDEMONELECTRICBARRIER_DIE1", 0, SPR_NULL, 0, 0, A_RemoteAction, -1, S_CYBRAKDEMON_DEINVINCIBLERIZE, S_CYBRAKDEMONELECTRICBARRIER_DIE2, 0},
	{"CYBRAKDEMONELECTRICBARRIER_DIE2", 0, SPR_NULL, 0, 0, A_SetObjectFlags, MF_PUSHABLE|MF_FIRE|MF_PAIN, 1, S_CYBRAKDEMONELECTRICBARRIER_DIE3, 0},
	{"CYBRAKDEMONELECTRICBARRIER_DIE3", 0, SPR_NULL, 0, 20*TICRATE, A_Scream, 0, 0, S_CYBRAKDEMONELECTRICBARRIER_SPARK_RANDOMSUCCESS, 0},
	{"CYBRAKDEMONELECTRICBARRIER_SPARK_RANDOMCHECK", 0, SPR_NULL, 0, 0, A_CheckRandom, 10, S_CYBRAKDEMONELECTRICBARRIER_SPARK_RANDOMSUCCESS, S_CYBRAKDEMONELECTRICBARRIER_SPARK_RANDOMFAIL, 0},
	{"CYBRAKDEMONELECTRICBARRIER_SPARK_RANDOMSUCCESS", 0, SPR_NULL, 0, 0, A_CapeChase, 0, 0, S_CYBRAKDEMONELECTRICBARRIER_SPARK_RANDOMCHOOSE, 0},
	{"CYBRAKDEMONELECTRICBARRIER_SPARK_RANDOMCHOOSE", 0, SPR_NULL, 0, 0, A_RandomStateRange, S_CYBRAKDEMONELECTRICBARRIER_SPARK_RANDOM1, S_CYBRAKDEMONELECTRICBARRIER_SPARK_RANDOM12, S_CYBRAKDEMONELECTRICBARRIER_SPARK_RANDOM1, 0},
	{"CYBRAKDEMONELECTRICBARRIER_SPARK_RANDOM1", 0, SPR_ELEC, 0 + FF_FULLBRIGHT, 1, A_PlaySound, sfx_s3k5c, 1, S_CYBRAKDEMONELECTRICBARRIER_SPARK_RANDOMLOOP, 0},
	{"CYBRAKDEMONELECTRICBARRIER_SPARK_RANDOM2", 0, SPR_ELEC, 1 + FF_FULLBRIGHT, 1, A_PlaySound, sfx_s3k5c, 1, S_CYBRAKDEMONELECTRICBARRIER_SPARK_RANDOMLOOP, 0},
	{"CYBRAKDEMONELECTRICBARRIER_SPARK_RANDOM3", 0, SPR_ELEC, 2 + FF_FULLBRIGHT, 1, A_PlaySound, sfx_s3k5c, 1, S_CYBRAKDEMONELECTRICBARRIER_SPARK_RANDOMLOOP, 0},
	{"CYBRAKDEMONELECTRICBARRIER_SPARK_RANDOM4", 0, SPR_ELEC, 3 + FF_FULLBRIGHT, 1, A_PlaySound, sfx_s3k5c, 1, S_CYBRAKDEMONELECTRICBARRIER_SPARK_RANDOMLOOP, 0},
	{"CYBRAKDEMONELECTRICBARRIER_SPARK_RANDOM5", 0, SPR_ELEC, 4 + FF_FULLBRIGHT, 1, A_PlaySound, sfx_s3k5c, 1, S_CYBRAKDEMONELECTRICBARRIER_SPARK_RANDOMLOOP, 0},
	{"CYBRAKDEMONELECTRICBARRIER_SPARK_RANDOM6", 0, SPR_ELEC, 5 + FF_FULLBRIGHT, 1, A_PlaySound, sfx_s3k5c, 1, S_CYBRAKDEMONELECTRICBARRIER_SPARK_RANDOMLOOP, 0},
	{"CYBRAKDEMONELECTRICBARRIER_SPARK_RANDOM7", 0, SPR_ELEC, 6 + FF_FULLBRIGHT, 1, A_PlaySound, sfx_s3k5c, 1, S_CYBRAKDEMONELECTRICBARRIER_SPARK_RANDOMLOOP, 0},
	{"CYBRAKDEMONELECTRICBARRIER_SPARK_RANDOM8", 0, SPR_ELEC, 7 + FF_FULLBRIGHT, 1, A_PlaySound, sfx_s3k5c, 1, S_CYBRAKDEMONELECTRICBARRIER_SPARK_RANDOMLOOP, 0},
	{"CYBRAKDEMONELECTRICBARRIER_SPARK_RANDOM9", 0, SPR_ELEC, 8 + FF_FULLBRIGHT, 1, A_PlaySound, sfx_s3k5c, 1, S_CYBRAKDEMONELECTRICBARRIER_SPARK_RANDOMLOOP, 0},
	{"CYBRAKDEMONELECTRICBARRIER_SPARK_RANDOM10", 0, SPR_ELEC, 9 + FF_FULLBRIGHT, 1, A_PlaySound, sfx_s3k5c, 1, S_CYBRAKDEMONELECTRICBARRIER_SPARK_RANDOMLOOP, 0},
	{"CYBRAKDEMONELECTRICBARRIER_SPARK_RANDOM11", 0, SPR_ELEC, 10 + FF_FULLBRIGHT, 1, A_PlaySound, sfx_s3k5c, 1, S_CYBRAKDEMONELECTRICBARRIER_SPARK_RANDOMLOOP, 0},
	{"CYBRAKDEMONELECTRICBARRIER_SPARK_RANDOM12", 0, SPR_ELEC, 11 + FF_FULLBRIGHT, 1, A_PlaySound, sfx_s3k5c, 1, S_CYBRAKDEMONELECTRICBARRIER_SPARK_RANDOMLOOP, 0},
	{"CYBRAKDEMONELECTRICBARRIER_SPARK_RANDOMFAIL", 0, SPR_NULL, 0, 1, NULL, 0, 0, S_CYBRAKDEMONELECTRICBARRIER_SPARK_RANDOMLOOP, 0},
	{"CYBRAKDEMONELECTRICBARRIER_SPARK_RANDOMLOOP", 0, SPR_NULL, 0, 0, A_Repeat, 5*TICRATE, S_CYBRAKDEMONELECTRICBARRIER_SPARK_RANDOMCHECK, S_CYBRAKDEMONELECTRICBARRIER_REVIVE1, 0},
	{"CYBRAKDEMONELECTRICBARRIER_REVIVE1", 0, SPR_NULL, 0, 0, A_CapeChase, 0, 0, S_CYBRAKDEMONELECTRICBARRIER_REVIVE2, 0},
	{"CYBRAKDEMONELECTRICBARRIER_REVIVE2", 0, SPR_NULL, 0, 0, A_SpawnFreshCopy, 0, 0, S_CYBRAKDEMONELECTRICBARRIER_REVIVE3, 0},
	{"CYBRAKDEMONELECTRICBARRIER_REVIVE3", 0, SPR_NULL, 0, TICRATE, A_PlaySound, sfx_s3k79, 0, S_NULL, 0},

	{"CYBRAKDEMONTARGETRETICULE1", 0, SPR_TARG, FF_TRANS50|FF_FULLBRIGHT  , 1, A_VileFire, sfx_s3k9d, MT_CYBRAKDEMON_TARGET_DOT, S_CYBRAKDEMONTARGETRETICULE2, 0},
	{"CYBRAKDEMONTARGETRETICULE2", 0, SPR_TARG, FF_TRANS50|FF_FULLBRIGHT|6, 1, A_VileFire, 0, MT_CYBRAKDEMON_TARGET_DOT, S_CYBRAKDEMONTARGETRETICULE3, 0},
	{"CYBRAKDEMONTARGETRETICULE3", 0, SPR_TARG, FF_TRANS50|FF_FULLBRIGHT|1, 1, A_VileFire, 0, MT_CYBRAKDEMON_TARGET_DOT, S_CYBRAKDEMONTARGETRETICULE4, 0},
	{"CYBRAKDEMONTARGETRETICULE4", 0, SPR_TARG, FF_TRANS50|FF_FULLBRIGHT|6, 1, A_VileFire, 0, MT_CYBRAKDEMON_TARGET_DOT, S_CYBRAKDEMONTARGETRETICULE5, 0},
	{"CYBRAKDEMONTARGETRETICULE5", 0, SPR_TARG, FF_TRANS50|FF_FULLBRIGHT|2, 1, A_VileFire, 0, MT_CYBRAKDEMON_TARGET_DOT, S_CYBRAKDEMONTARGETRETICULE6, 0},
	{"CYBRAKDEMONTARGETRETICULE6", 0, SPR_TARG, FF_TRANS50|FF_FULLBRIGHT|6, 1, A_VileFire, 0, MT_CYBRAKDEMON_TARGET_DOT, S_CYBRAKDEMONTARGETRETICULE7, 0},
	{"CYBRAKDEMONTARGETRETICULE7", 0, SPR_TARG, FF_TRANS50|FF_FULLBRIGHT|3, 1, A_VileFire, 0, MT_CYBRAKDEMON_TARGET_DOT, S_CYBRAKDEMONTARGETRETICULE8, 0},
	{"CYBRAKDEMONTARGETRETICULE8", 0, SPR_TARG, FF_TRANS50|FF_FULLBRIGHT|6, 1, A_VileFire, 0, MT_CYBRAKDEMON_TARGET_DOT, S_CYBRAKDEMONTARGETRETICULE9, 0},
	{"CYBRAKDEMONTARGETRETICULE9", 0, SPR_TARG, FF_TRANS50|FF_FULLBRIGHT|4, 1, A_VileFire, 0, MT_CYBRAKDEMON_TARGET_DOT, S_CYBRAKDEMONTARGETRETICULE10, 0},
	{"CYBRAKDEMONTARGETRETICULE10", 0, SPR_TARG, FF_TRANS50|FF_FULLBRIGHT|6, 1, A_VileFire, 0, MT_CYBRAKDEMON_TARGET_DOT, S_CYBRAKDEMONTARGETRETICULE11, 0},
	{"CYBRAKDEMONTARGETRETICULE11", 0, SPR_TARG, FF_TRANS50|FF_FULLBRIGHT|5, 1, A_VileFire, 0, MT_CYBRAKDEMON_TARGET_DOT, S_CYBRAKDEMONTARGETRETICULE12, 0},
	{"CYBRAKDEMONTARGETRETICULE12", 0, SPR_TARG, FF_TRANS50|FF_FULLBRIGHT|6, 1, A_VileFire, 0, MT_CYBRAKDEMON_TARGET_DOT, S_CYBRAKDEMONTARGETRETICULE13, 0},
	{"CYBRAKDEMONTARGETRETICULE13", 0, SPR_TARG, FF_TRANS50|FF_FULLBRIGHT  , 1, A_VileFire, 0, MT_CYBRAKDEMON_TARGET_DOT, S_CYBRAKDEMONTARGETRETICULE14, 0},
	{"CYBRAKDEMONTARGETRETICULE14", 0, SPR_TARG, FF_TRANS50|FF_FULLBRIGHT|6, 1, A_Repeat, 6, S_CYBRAKDEMONTARGETRETICULE2, S_NULL, 0},

	{"CYBRAKDEMONTARGETDOT", 0, SPR_HOOP, FF_TRANS50|FF_FULLBRIGHT, 2, NULL, 0, 0, S_NULL, 0},

	{"CYBRAKDEMONNAPALMBOMBLARGE_FLY1", 0, SPR_NPLM, 0, 2, NULL, 0, 0, S_CYBRAKDEMONNAPALMBOMBLARGE_FLY2, 0},
	{"CYBRAKDEMONNAPALMBOMBLARGE_FLY2", 0, SPR_NPLM, 1, 2, NULL, 0, 0, S_CYBRAKDEMONNAPALMBOMBLARGE_FLY3, 0},
	{"CYBRAKDEMONNAPALMBOMBLARGE_FLY3", 0, SPR_NPLM, 2, 2, NULL, 0, 0, S_CYBRAKDEMONNAPALMBOMBLARGE_FLY4, 0},
	{"CYBRAKDEMONNAPALMBOMBLARGE_FLY4", 0, SPR_NPLM, 3, 2, NULL, 0, 0, S_CYBRAKDEMONNAPALMBOMBLARGE_FLY1, 0},
	{"CYBRAKDEMONNAPALMBOMBLARGE_DIE1", 0, SPR_NPLM, 0, 1, A_Explode, 0, 0, S_CYBRAKDEMONNAPALMBOMBLARGE_DIE2, 0}, // Explode
	{"CYBRAKDEMONNAPALMBOMBLARGE_DIE2", 0, SPR_NPLM, 0, 1, A_NapalmScatter, MT_CYBRAKDEMON_NAPALM_BOMB_SMALL + (6<<16), 256 + (48<<16), S_CYBRAKDEMONNAPALMBOMBLARGE_DIE3, 0}, // Outer ring
	{"CYBRAKDEMONNAPALMBOMBLARGE_DIE3", 0, SPR_NPLM, 0, 1, A_NapalmScatter, MT_CYBRAKDEMON_NAPALM_BOMB_SMALL + (1<<16), 32<<16, S_CYBRAKDEMONNAPALMBOMBLARGE_DIE4, 0}, // Center
	{"CYBRAKDEMONNAPALMBOMBLARGE_DIE4", 0, SPR_NULL, 0, 81, A_Scream, 0, 0, S_NULL, 0}, // Sound

	{"CYBRAKDEMONNAPALMBOMBSMALL", 0, SPR_MNPL, 0, 1, NULL, 0, 0, S_CYBRAKDEMONNAPALMBOMBSMALL, 0},
	{"CYBRAKDEMONNAPALMBOMBSMALL_DIE1", 0, SPR_MNPL, 0, 1, A_Explode, 0, 0, S_CYBRAKDEMONNAPALMBOMBSMALL_DIE2, 0}, // Explode
	{"CYBRAKDEMONNAPALMBOMBSMALL_DIE2", 0, SPR_MNPL, 0, 1, A_NapalmScatter, MT_CYBRAKDEMON_NAPALM_FLAMES + (12<<16), 128 + (40<<16), S_CYBRAKDEMONNAPALMBOMBSMALL_DIE3, 0}, // Outer ring
	{"CYBRAKDEMONNAPALMBOMBSMALL_DIE3", 0, SPR_MNPL, 0, 1, A_NapalmScatter, MT_CYBRAKDEMON_NAPALM_FLAMES + (8<<16), 64 + (32<<16), S_CYBRAKDEMONNAPALMBOMBSMALL_DIE4, 0}, // Inner ring
	{"CYBRAKDEMONNAPALMBOMBSMALL_DIE4", 0, SPR_MNPL, 0, 1, A_NapalmScatter, MT_CYBRAKDEMON_NAPALM_FLAMES + (1<<16), 24<<16, S_CYBRAKDEMONNAPALMBOMBSMALL_DIE5, 0}, // Center
	{"CYBRAKDEMONNAPALMBOMBSMALL_DIE5", 0, SPR_NULL, 0, 24, A_Scream, 0, 0, S_NULL, 0}, // Sound

	{"CYBRAKDEMONNAPALMFLAME_FLY1", 0, SPR_SFLM, FF_FULLBRIGHT,   2, NULL, 0, 0, S_CYBRAKDEMONNAPALMFLAME_FLY2, 0},
	{"CYBRAKDEMONNAPALMFLAME_FLY2", 0, SPR_SFLM, FF_FULLBRIGHT|1, 2, NULL, 0, 0, S_CYBRAKDEMONNAPALMFLAME_FLY3, 0},
	{"CYBRAKDEMONNAPALMFLAME_FLY3", 0, SPR_SFLM, FF_FULLBRIGHT|2, 2, NULL, 0, 0, S_CYBRAKDEMONNAPALMFLAME_FLY4, 0},
	{"CYBRAKDEMONNAPALMFLAME_FLY4", 0, SPR_SFLM, FF_FULLBRIGHT|3, 2, NULL, 0, 0, S_CYBRAKDEMONNAPALMFLAME_FLY5, 0},
	{"CYBRAKDEMONNAPALMFLAME_FLY5", 0, SPR_SFLM, FF_FULLBRIGHT|4, 2, NULL, 0, 0, S_CYBRAKDEMONNAPALMFLAME_FLY6, 0},
	{"CYBRAKDEMONNAPALMFLAME_FLY6", 0, SPR_SFLM, FF_FULLBRIGHT|5, 2, NULL, 0, 0, S_CYBRAKDEMONNAPALMFLAME_FLY1, 0},
	{"CYBRAKDEMONNAPALMFLAME_DIE", 0, SPR_SFLM, FF_FULLBRIGHT,   0, A_SpawnObjectRelative, 0, MT_CYBRAKDEMON_FLAMEREST, S_NULL, 0},

	{"CYBRAKDEMONVILEEXPLOSION1", 0, SPR_NULL, 0, 1, A_SetFuse, TICRATE, 0, S_CYBRAKDEMONVILEEXPLOSION2, 0},
	{"CYBRAKDEMONVILEEXPLOSION2", 0, SPR_NULL, 0, 0, A_ScoreRise, 0, 0, S_CYBRAKDEMONVILEEXPLOSION3, 0},
	{"CYBRAKDEMONVILEEXPLOSION3", 0, SPR_NULL, 0, 1, A_BossScream, 0, 0, S_CYBRAKDEMONVILEEXPLOSION1, 0},

	// Metal Sonic
	{"METALSONIC_RACE", 0, SPR_PLAY, SPR2_STND, -1, NULL, 0, 0, S_METALSONIC_RACE, 0},

	{"METALSONIC_FLOAT", 0, SPR_PLAY,               SPR2_WALK, -1, NULL,         0, 0, S_METALSONIC_FLOAT, 0},
	{"METALSONIC_VECTOR", 0, SPR_PLAY, SPR2_MSC1|FF_FULLBRIGHT, -1, NULL, 0, 0, S_METALSONIC_STUN, 0},
	{"METALSONIC_STUN", 0, SPR_PLAY,               SPR2_MSC0, -1, NULL,         0, 0, S_METALSONIC_FLOAT, 0},
	{"METALSONIC_RAISE", 0, SPR_PLAY, SPR2_SPNG, 20, NULL,         0, 0, S_METALSONIC_GATHER, 0},
	{"METALSONIC_GATHER", 0, SPR_PLAY, SPR2_MSC2, -1, NULL,         0, 0, S_METALSONIC_FLOAT, 0},
	{"METALSONIC_DASH", 0, SPR_PLAY, SPR2_DASH|FF_FULLBRIGHT, -1, NULL, 1, 2, S_METALSONIC_BOUNCE, 0},
	{"METALSONIC_BOUNCE", 0, SPR_PLAY, SPR2_MSC2|FF_FULLBRIGHT, -1, NULL, 1, 2, S_METALSONIC_FLOAT, 0},
	{"METALSONIC_BADBOUNCE", 0, SPR_PLAY, SPR2_PAIN, -1, NULL,         0, 0, S_METALSONIC_FLOAT, 0},
	{"METALSONIC_SHOOT", 0, SPR_PLAY, SPR2_SPNG, -1, NULL,         0, 0, S_METALSONIC_GATHER, 0},
	{"METALSONIC_PAIN", 0, SPR_PLAY, SPR2_FLT, 40, A_Pain,       0, 0, S_METALSONIC_FLOAT, 0},
	{"METALSONIC_DEATH1", 0, SPR_PLAY, SPR2_SPNG,  2, A_Fall,       0, 0, S_METALSONIC_DEATH2, 0},
	{"METALSONIC_DEATH2", 0, SPR_PLAY, SPR2_SPNG,  4, A_BossScream, 0, 0, S_METALSONIC_DEATH3, 0},
	{"METALSONIC_DEATH3", 0, SPR_PLAY, SPR2_SPNG,  0, A_Repeat, 17, S_METALSONIC_DEATH2, S_METALSONIC_DEATH4, 0},
	{"METALSONIC_DEATH4", 0, SPR_PLAY, SPR2_SPNG, -1, A_BossDeath,  0, 0, S_NULL, 0},
	{"METALSONIC_FLEE1", 0, SPR_PLAY, SPR2_FLT,  1, A_BossScream,         0, 0, S_METALSONIC_FLEE2, 0},
	{"METALSONIC_FLEE2", 0, SPR_PLAY, SPR2_FLT,  7, NULL,                 0, 0, S_METALSONIC_FLEE1, 0},

	{"MSSHIELD_F1", 0, SPR_MSCF, FF_FULLBRIGHT|FF_TRANS30|FF_ANIMATE, -1, NULL, 11, 1, S_NULL, 0},
	{"MSSHIELD_F2", 0, SPR_MSCF, FF_FULLBRIGHT|FF_ANIMATE|12, -1, NULL, 8, 2, S_NULL, 0},

	// Ring
	{"RING", 0, SPR_RING, FF_ANIMATE|FF_GLOBALANIM, -1, NULL, 23, 1, S_RING, 0},

	// Blue Sphere for special stages
	{"BLUESPHERE", 0, SPR_SPHR, FF_SEMIBRIGHT, -1, NULL, 0, 0, S_NULL, 0},
	{"BLUESPHEREBONUS", 0, SPR_SPHR, FF_SEMIBRIGHT
#ifdef MANIASPHERES
							|FF_ANIMATE|FF_RANDOMANIM
#endif
							, -1, NULL, 1, 4, S_NULL, 0},
	{"BLUESPHERESPARK", 0, SPR_SPHR, 0, 20, NULL, 0, 0, S_NULL, 0},

	// Bomb Sphere
	{"BOMBSPHERE1", 0, SPR_SPHR, FF_FULLBRIGHT|3, 2, NULL, 0, 0, S_BOMBSPHERE2, 0},
	{"BOMBSPHERE2", 0, SPR_SPHR, FF_SEMIBRIGHT|4, 1, NULL, 0, 0, S_BOMBSPHERE3, 0},
	{"BOMBSPHERE3", 0, SPR_SPHR, FF_SEMIBRIGHT|5, 2, NULL, 0, 0, S_BOMBSPHERE4, 0},
	{"BOMBSPHERE4", 0, SPR_SPHR, FF_SEMIBRIGHT|4, 1, NULL, 0, 0, S_BOMBSPHERE1, 0},

	// NiGHTS Chip
	{"NIGHTSCHIP", 0, SPR_NCHP, FF_SEMIBRIGHT|FF_ANIMATE,    -1, NULL, 15, 2, S_NULL, 0},
	{"NIGHTSCHIPBONUS", 0, SPR_NCHP, FF_SEMIBRIGHT|FF_ANIMATE|16, -1, NULL, 15, 2, S_NULL, 0},

	// NiGHTS Star
	{"NIGHTSSTAR", 0, SPR_NSTR, FF_ANIMATE, -1, NULL, 14, 2, S_NULL, 0},
	{"NIGHTSSTARXMAS", 0, SPR_NSTR, 15, -1, NULL, 0, 0, S_NULL, 0},

	// Gravity Well sprites for Egg Rock's Special Stage
	{"GRAVWELLGREEN", 0, SPR_GWLG, FF_ANIMATE, -1, NULL, 2, 1, S_NULL, 0},
	{"GRAVWELLRED", 0, SPR_GWLR, FF_ANIMATE, -1, NULL, 2, 1, S_NULL, 0},

	// Individual Team Rings (now with shield attracting action! =P)
	{"TEAMRING", 0, SPR_TRNG, FF_ANIMATE|FF_GLOBALANIM, -1, NULL, 23, 1, S_TEAMRING, 0},

	// Special Stage Token
	{"TOKEN", 0, SPR_TOKE, FF_ANIMATE|FF_FULLBRIGHT, -1, NULL, 19, 1, S_TOKEN, 0},

	// CTF Flags
	{"REDFLAG", 0, SPR_RFLG, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"BLUEFLAG", 0, SPR_BFLG, 0, -1, NULL, 0, 0, S_NULL, 0},

	// Emblem
	{"EMBLEM1", 0, SPR_EMBM,  0, -1, NULL, 0, 0, S_NULL, 0},
	{"EMBLEM2", 0, SPR_EMBM,  1, -1, NULL, 0, 0, S_NULL, 0},
	{"EMBLEM3", 0, SPR_EMBM,  2, -1, NULL, 0, 0, S_NULL, 0},
	{"EMBLEM4", 0, SPR_EMBM,  3, -1, NULL, 0, 0, S_NULL, 0},
	{"EMBLEM5", 0, SPR_EMBM,  4, -1, NULL, 0, 0, S_NULL, 0},
	{"EMBLEM6", 0, SPR_EMBM,  5, -1, NULL, 0, 0, S_NULL, 0},
	{"EMBLEM7", 0, SPR_EMBM,  6, -1, NULL, 0, 0, S_NULL, 0},
	{"EMBLEM8", 0, SPR_EMBM,  7, -1, NULL, 0, 0, S_NULL, 0},
	{"EMBLEM9", 0, SPR_EMBM,  8, -1, NULL, 0, 0, S_NULL, 0},
	{"EMBLEM10", 0, SPR_EMBM,  9, -1, NULL, 0, 0, S_NULL, 0},
	{"EMBLEM11", 0, SPR_EMBM, 10, -1, NULL, 0, 0, S_NULL, 0},
	{"EMBLEM12", 0, SPR_EMBM, 11, -1, NULL, 0, 0, S_NULL, 0},
	{"EMBLEM13", 0, SPR_EMBM, 12, -1, NULL, 0, 0, S_NULL, 0},
	{"EMBLEM14", 0, SPR_EMBM, 13, -1, NULL, 0, 0, S_NULL, 0},
	{"EMBLEM15", 0, SPR_EMBM, 14, -1, NULL, 0, 0, S_NULL, 0},
	{"EMBLEM16", 0, SPR_EMBM, 15, -1, NULL, 0, 0, S_NULL, 0},
	{"EMBLEM17", 0, SPR_EMBM, 16, -1, NULL, 0, 0, S_NULL, 0},
	{"EMBLEM18", 0, SPR_EMBM, 17, -1, NULL, 0, 0, S_NULL, 0},
	{"EMBLEM19", 0, SPR_EMBM, 18, -1, NULL, 0, 0, S_NULL, 0},
	{"EMBLEM20", 0, SPR_EMBM, 19, -1, NULL, 0, 0, S_NULL, 0},
	{"EMBLEM21", 0, SPR_EMBM, 20, -1, NULL, 0, 0, S_NULL, 0},
	{"EMBLEM22", 0, SPR_EMBM, 21, -1, NULL, 0, 0, S_NULL, 0},
	{"EMBLEM23", 0, SPR_EMBM, 22, -1, NULL, 0, 0, S_NULL, 0},
	{"EMBLEM24", 0, SPR_EMBM, 23, -1, NULL, 0, 0, S_NULL, 0},
	{"EMBLEM25", 0, SPR_EMBM, 24, -1, NULL, 0, 0, S_NULL, 0},
	{"EMBLEM26", 0, SPR_EMBM, 25, -1, NULL, 0, 0, S_NULL, 0},

	// Chaos Emeralds
	{"CEMG1", 0, SPR_CEMG, FF_FULLBRIGHT,   -1, NULL, 0, 0, S_NULL, 0},
	{"CEMG2", 0, SPR_CEMG, FF_FULLBRIGHT|1, -1, NULL, 0, 0, S_NULL, 0},
	{"CEMG3", 0, SPR_CEMG, FF_FULLBRIGHT|2, -1, NULL, 0, 0, S_NULL, 0},
	{"CEMG4", 0, SPR_CEMG, FF_FULLBRIGHT|3, -1, NULL, 0, 0, S_NULL, 0},
	{"CEMG5", 0, SPR_CEMG, FF_FULLBRIGHT|4, -1, NULL, 0, 0, S_NULL, 0},
	{"CEMG6", 0, SPR_CEMG, FF_FULLBRIGHT|5, -1, NULL, 0, 0, S_NULL, 0},
	{"CEMG7", 0, SPR_CEMG, FF_FULLBRIGHT|6, -1, NULL, 0, 0, S_NULL, 0},

	// Emerald hunt shards
	{"SHRD1", 0, SPR_SHRD, FF_SEMIBRIGHT|0, -1, NULL, 0, 0, S_NULL, 0},
	{"SHRD2", 0, SPR_SHRD, FF_SEMIBRIGHT|1, -1, NULL, 0, 0, S_NULL, 0},
	{"SHRD3", 0, SPR_SHRD, FF_SEMIBRIGHT|2, -1, NULL, 0, 0, S_NULL, 0},

	// Bubble Source
	{"BUBBLES1", 0, SPR_BBLS, 0, 8, A_BubbleSpawn, 2048, 0, S_BUBBLES2, 0},
	{"BUBBLES2", 0, SPR_BBLS, 1, 8, A_BubbleCheck, 0, 0, S_BUBBLES3, 0},
	{"BUBBLES3", 0, SPR_BBLS, 2, 8, A_BubbleSpawn, 2048, 0, S_BUBBLES4, 0},
	{"BUBBLES4", 0, SPR_BBLS, 3, 8, A_BubbleCheck, 0, 0, S_BUBBLES1, 0},

	// Level End Sign
	{"SIGN", 0, SPR_SIGN,                 0, -1, A_SignPlayer, -3, 0, S_NULL, 0},
	{"SIGNSPIN1", 0, SPR_SIGN,                 0,  1,   A_SignSpin, 30, 0, S_SIGNSPIN2, 0},
	{"SIGNSPIN2", 0, SPR_SIGN,                 0,  0,     A_Repeat,  4, S_SIGNSPIN1, S_SIGNSPIN3, 0},
	{"SIGNSPIN3", 0, SPR_SIGN,                 0,  0, A_SignPlayer, -2, 0, S_SIGNSPIN4, 0},
	{"SIGNSPIN4", 0, SPR_SIGN,                 0,  1,   A_SignSpin, 30, 0, S_SIGNSPIN5, 0},
	{"SIGNSPIN5", 0, SPR_SIGN,                 0,  0,     A_Repeat,  4, S_SIGNSPIN4, S_SIGNSPIN6, 0},
	{"SIGNSPIN6", 0, SPR_SIGN,                 0,  0, A_SignPlayer, -3, 0, S_SIGNSPIN1, 0},
	{"SIGNPLAYER", 0, SPR_SIGN,                 0,  1, A_SignPlayer, -1, 0, S_SIGNSLOW, 0},
	{"SIGNSLOW", 0, SPR_SIGN,                 0,  1,   A_SignSpin, 30, 0, S_SIGNSLOW, 0},
	{"SIGNSTOP", 0, SPR_SIGN,                 0, -1,         NULL,  0, 0, S_NULL, 0},
	{"SIGNBOARD", 0, SPR_SIGN, FF_PAPERSPRITE| 2, -1,         NULL,  0, 0, S_NULL, 0},
	{"EGGMANSIGN", 0, SPR_SIGN, FF_PAPERSPRITE| 1, -1,         NULL,  0, 29, S_NULL, 0},
	{"CLEARSIGN", 0, SPR_SIGN, FF_PAPERSPRITE|18, -1,         NULL,  0, 29, S_NULL, 0},

	// Spike Ball
	{"SPIKEBALL1", 0, SPR_SPIK, 0, 1, NULL, 0, 0, S_SPIKEBALL2, 0},
	{"SPIKEBALL2", 0, SPR_SPIK, 1, 1, NULL, 0, 0, S_SPIKEBALL3, 0},
	{"SPIKEBALL3", 0, SPR_SPIK, 2, 1, NULL, 0, 0, S_SPIKEBALL4, 0},
	{"SPIKEBALL4", 0, SPR_SPIK, 3, 1, NULL, 0, 0, S_SPIKEBALL5, 0},
	{"SPIKEBALL5", 0, SPR_SPIK, 4, 1, NULL, 0, 0, S_SPIKEBALL6, 0},
	{"SPIKEBALL6", 0, SPR_SPIK, 5, 1, NULL, 0, 0, S_SPIKEBALL7, 0},
	{"SPIKEBALL7", 0, SPR_SPIK, 6, 1, NULL, 0, 0, S_SPIKEBALL8, 0},
	{"SPIKEBALL8", 0, SPR_SPIK, 7, 1, NULL, 0, 0, S_SPIKEBALL1, 0},

	// Elemental Shield's Spawn
	{"SPINFIRE1", 0, SPR_SFLM, FF_FULLBRIGHT,   2, NULL, 0, 0, S_SPINFIRE2, 0},
	{"SPINFIRE2", 0, SPR_SFLM, FF_FULLBRIGHT|1, 2, NULL, 0, 0, S_SPINFIRE3, 0},
	{"SPINFIRE3", 0, SPR_SFLM, FF_FULLBRIGHT|2, 2, NULL, 0, 0, S_SPINFIRE4, 0},
	{"SPINFIRE4", 0, SPR_SFLM, FF_FULLBRIGHT|3, 2, NULL, 0, 0, S_SPINFIRE5, 0},
	{"SPINFIRE5", 0, SPR_SFLM, FF_FULLBRIGHT|4, 2, NULL, 0, 0, S_SPINFIRE6, 0},
	{"SPINFIRE6", 0, SPR_SFLM, FF_FULLBRIGHT|5, 2, NULL, 0, 0, S_SPINFIRE1, 0},

	{"TEAM_SPINFIRE1", 0, SPR_TFLM, FF_FULLBRIGHT,   2, NULL, 0, 0, S_TEAM_SPINFIRE2, 0},
	{"TEAM_SPINFIRE2", 0, SPR_TFLM, FF_FULLBRIGHT|1, 2, NULL, 0, 0, S_TEAM_SPINFIRE3, 0},
	{"TEAM_SPINFIRE3", 0, SPR_TFLM, FF_FULLBRIGHT|2, 2, NULL, 0, 0, S_TEAM_SPINFIRE4, 0},
	{"TEAM_SPINFIRE4", 0, SPR_TFLM, FF_FULLBRIGHT|3, 2, NULL, 0, 0, S_TEAM_SPINFIRE5, 0},
	{"TEAM_SPINFIRE5", 0, SPR_TFLM, FF_FULLBRIGHT|4, 2, NULL, 0, 0, S_TEAM_SPINFIRE6, 0},
	{"TEAM_SPINFIRE6", 0, SPR_TFLM, FF_FULLBRIGHT|5, 2, NULL, 0, 0, S_TEAM_SPINFIRE1, 0},

	// Floor Spike
	{"SPIKE1", 0, SPR_USPK, 0,-1, A_SpikeRetract, 1, 0, S_SPIKE2, 0},  // -- Fully extended
	{"SPIKE2", 0, SPR_USPK, 1, 2, A_Pain,         0, 0, S_SPIKE3, 0},
	{"SPIKE3", 0, SPR_USPK, 2, 2, NULL,           0, 0, S_SPIKE4, 0},
	{"SPIKE4", 0, SPR_USPK, 3,-1, A_SpikeRetract, 0, 0, S_SPIKE5, 0},  // -- Fully retracted
	{"SPIKE5", 0, SPR_USPK, 2, 2, A_Pain,         0, 0, S_SPIKE6, 0},
	{"SPIKE6", 0, SPR_USPK, 1, 2, NULL,           0, 0, S_SPIKE1, 0},
	{"SPIKED1", 0, SPR_USPK, 4,-1, NULL, 0, 0, S_NULL, 0},  // -- Busted spike particles
	{"SPIKED2", 0, SPR_USPK, 5,-1, NULL, 0, 0, S_NULL, 0},

	// Wall Spike
	{"WALLSPIKE1", 0, SPR_WSPK, 0|FF_PAPERSPRITE,-1, A_SpikeRetract, 1, 0, S_WALLSPIKE2, 0},  // -- Fully extended
	{"WALLSPIKE2", 0, SPR_WSPK, 1|FF_PAPERSPRITE, 2, A_Pain,         0, 0, S_WALLSPIKE3, 0},
	{"WALLSPIKE3", 0, SPR_WSPK, 2|FF_PAPERSPRITE, 2, NULL,           0, 0, S_WALLSPIKE4, 0},
	{"WALLSPIKE4", 0, SPR_WSPK, 3|FF_PAPERSPRITE,-1, A_SpikeRetract, 0, 0, S_WALLSPIKE5, 0},  // -- Fully retracted
	{"WALLSPIKE5", 0, SPR_WSPK, 2|FF_PAPERSPRITE, 2, A_Pain,         0, 0, S_WALLSPIKE6, 0},
	{"WALLSPIKE6", 0, SPR_WSPK, 1|FF_PAPERSPRITE, 2, NULL,           0, 0, S_WALLSPIKE1, 0},
	{"WALLSPIKEBASE", 0, SPR_WSPB, 0|FF_PAPERSPRITE,-1, NULL, 0, 0, S_NULL, 0},  // -- Base
	{"WALLSPIKED1", 0, SPR_WSPK, 4,-1, NULL, 0, 0, S_NULL, 0},  // -- Busted spike particles
	{"WALLSPIKED2", 0, SPR_WSPK, 5,-1, NULL, 0, 0, S_NULL, 0},

	// Starpost
	{"STARPOST_IDLE", 0, SPR_STPT, 0            , -1, NULL,  0, 0, S_NULL, 0},
	{"STARPOST_FLASH", 0, SPR_STPT, FF_ANIMATE|17, -1, NULL,  5, 1, S_NULL, 0},
	{"STARPOST_STARTSPIN", 0, SPR_STPT, FF_ANIMATE|13,  2, NULL,  1, 1, S_STARPOST_SPIN, 0},
	{"STARPOST_SPIN", 0, SPR_STPT, FF_ANIMATE|1 , 23, NULL, 11, 1, S_STARPOST_ENDSPIN, 0},
	{"STARPOST_ENDSPIN", 0, SPR_STPT, FF_ANIMATE|15,  2, NULL,  1, 1, S_STARPOST_FLASH, 0},

	// Big floating mine
	{"BIGMINE_IDLE", 0, SPR_BMNE, 0,  2, A_Look,      ((224<<FRACBITS)|1), 0, S_BIGMINE_IDLE, 0},
	{"BIGMINE_ALERT1", 0, SPR_BMNE, 1,  2, A_MineRange, 112,                 0, S_BIGMINE_ALERT2, 0},
	{"BIGMINE_ALERT2", 0, SPR_BMNE, 2,  2, A_MineRange, 112,                 0, S_BIGMINE_ALERT3, 0},
	{"BIGMINE_ALERT3", 0, SPR_BMNE, 0,  1, A_Look,      ((224<<FRACBITS)|1), 1, S_BIGMINE_IDLE, 0},
	{"BIGMINE_SET1", 0, SPR_BMNE, 3, 25, A_Pain,           0,            0, S_BIGMINE_SET2, 0},
	{"BIGMINE_SET1", 0, SPR_BMNE, 3, 10, A_SetObjectFlags, MF_SHOOTABLE, 1, S_BIGMINE_SET3, 0},
	{"BIGMINE_SET3", 0, SPR_BMNE, 3,  1, A_MineExplode,    0,            0, S_BIGMINE_BLAST1, 0},
	{"BIGMINE_BLAST1", 0, SPR_BMNB,   FF_FULLBRIGHT, 2, NULL, 0, 0, S_BIGMINE_BLAST2, 0},
	{"BIGMINE_BLAST2", 0, SPR_BMNB, 1|FF_FULLBRIGHT, 2, NULL, 0, 0, S_BIGMINE_BLAST3, 0},
	{"BIGMINE_BLAST3", 0, SPR_BMNB, 2|FF_FULLBRIGHT, 1, NULL, 0, 0, S_BIGMINE_BLAST4, 0},
	{"BIGMINE_BLAST4", 0, SPR_BMNB, 3|FF_FULLBRIGHT, 1, NULL, 0, 0, S_BIGMINE_BLAST5, 0},
	{"BIGMINE_BLAST5", 0, SPR_NULL, 0, 35, NULL, 0, 0, S_NULL, 0},

	// Cannon launcher
	{"CANNONLAUNCHER1", 0, SPR_NULL, 0, 1,    A_FindTarget,     MT_PLAYER,         0, S_CANNONLAUNCHER2, 0},
	{"CANNONLAUNCHER2", 0, SPR_NULL, 0, 1,       A_LobShot, MT_CANNONBALL, 4*TICRATE, S_CANNONLAUNCHER3, 0},
	{"CANNONLAUNCHER3", 0, SPR_NULL, 0, 2, A_SetRandomTics,     TICRATE/2, 3*TICRATE, S_CANNONLAUNCHER1, 0},

	// Monitor Miscellany
	{"BOXSPARKLE1", 0, SPR_NSPK, 0, 16, NULL, 0, 0, S_BOXSPARKLE2, 0},
	{"BOXSPARKLE2", 0, SPR_NSPK, 1, 12, NULL, 0, 0, S_BOXSPARKLE3, 0},
	{"BOXSPARKLE3", 0, SPR_NSPK, 2,  8, NULL, 0, 0, S_BOXSPARKLE4, 0},
	{"BOXSPARKLE4", 0, SPR_NSPK, 3,  4, NULL, 0, 0, S_NULL, 0},

	{"BOX_FLICKER", 0, SPR_MSTV, 0,  1, NULL, 0, 0, S_SPAWNSTATE, 0},
	{"BOX_POP1", 0, SPR_MSTV, 0,  4, A_MonitorPop, 0, 0, S_BOX_POP2, 0},
	{"BOX_POP2", 0, SPR_MSTV, 1, -1, NULL, 0, 0, S_NULL, 0},

	{"GOLDBOX_FLICKER", 0, SPR_XLTV, 0,  1, NULL, 0, 0, S_SPAWNSTATE, 0},
	{"GOLDBOX_OFF1", 0, SPR_XLTV, 1, 89, A_GoldMonitorPop, 0, 0, S_GOLDBOX_OFF2, 0},
	{"GOLDBOX_OFF2", 0, SPR_XLTV, 2,  4, A_PlayAttackSound, 0, 0, S_GOLDBOX_OFF3, 0},
	{"GOLDBOX_OFF3", 0, SPR_XLTV, 3,  4, NULL, 0, 0, S_GOLDBOX_OFF4, 0},
	{"GOLDBOX_OFF4", 0, SPR_XLTV, 4,  4, NULL, 0, 0, S_GOLDBOX_OFF5, 0},
	{"GOLDBOX_OFF5", 0, SPR_XLTV, 5,  2, NULL, 0, 0, S_GOLDBOX_OFF6, 0},
	{"GOLDBOX_OFF6", 0, SPR_XLTV, 6,  2, NULL, 0, 0, S_GOLDBOX_OFF7, 0},
	{"GOLDBOX_OFF7", 0, SPR_XLTV, 6,  0, A_GoldMonitorRestore, 0, 0, S_SPAWNSTATE, 0},

	// Monitor States (one per box)
	{"MYSTERY_BOX", 0, SPR_TVMY, 0, 2, NULL, 0, 0, S_BOX_FLICKER, 0},
	{"RING_BOX", 0, SPR_TVRI, 0, 2, NULL, 0, 0, S_BOX_FLICKER, 0},
	{"PITY_BOX", 0, SPR_TVPI, 0, 2, NULL, 0, 0, S_BOX_FLICKER, 0},
	{"ATTRACT_BOX", 0, SPR_TVAT, 0, 2, NULL, 0, 0, S_BOX_FLICKER, 0},
	{"FORCE_BOX", 0, SPR_TVFO, 0, 2, NULL, 0, 0, S_BOX_FLICKER, 0},
	{"ARMAGEDDON_BOX", 0, SPR_TVAR, 0, 2, NULL, 0, 0, S_BOX_FLICKER, 0},
	{"WHIRLWIND_BOX", 0, SPR_TVWW, 0, 2, NULL, 0, 0, S_BOX_FLICKER, 0},
	{"ELEMENTAL_BOX", 0, SPR_TVEL, 0, 2, NULL, 0, 0, S_BOX_FLICKER, 0},
	{"SNEAKERS_BOX", 0, SPR_TVSS, 0, 2, NULL, 0, 0, S_BOX_FLICKER, 0},
	{"INVULN_BOX", 0, SPR_TVIV, 0, 2, NULL, 0, 0, S_BOX_FLICKER, 0},
	{"1UP_BOX", 0, SPR_TV1U, 0, 2, A_1upThinker, 0, 0, S_BOX_FLICKER, 0},
	{"EGGMAN_BOX", 0, SPR_TVEG, 0, 2, NULL, 0, 0, S_BOX_FLICKER, 0},
	{"MIXUP_BOX", 0, SPR_TVMX, 0, 2, NULL, 0, 0, S_BOX_FLICKER, 0},
	{"GRAVITY_BOX", 0, SPR_TVGV, 0, 2, NULL, 0, 0, S_BOX_FLICKER, 0},
	{"RECYCLER_BOX", 0, SPR_TVRC, 0, 2, NULL, 0, 0, S_BOX_FLICKER, 0},
	{"SCORE1K_BOX", 0, SPR_TV1K, 0, 2, NULL, 0, 0, S_BOX_FLICKER, 0},
	{"SCORE10K_BOX", 0, SPR_TVTK, 0, 2, NULL, 0, 0, S_BOX_FLICKER, 0},
	{"FLAMEAURA_BOX", 0, SPR_TVFL, 0, 2, NULL, 0, 0, S_BOX_FLICKER, 0},
	{"BUBBLEWRAP_BOX", 0, SPR_TVBB, 0, 2, NULL, 0, 0, S_BOX_FLICKER, 0},
	{"THUNDERCOIN_BOX", 0, SPR_TVZP, 0, 2, NULL, 0, 0, S_BOX_FLICKER, 0},

	// Gold Repeat Monitor States (one per box)
	{"PITY_GOLDBOX", 0, SPR_TVPI, 1, 2, A_GoldMonitorSparkle, 0, 0, S_GOLDBOX_FLICKER, 0},
	{"ATTRACT_GOLDBOX", 0, SPR_TVAT, 1, 2, A_GoldMonitorSparkle, 0, 0, S_GOLDBOX_FLICKER, 0},
	{"FORCE_GOLDBOX", 0, SPR_TVFO, 1, 2, A_GoldMonitorSparkle, 0, 0, S_GOLDBOX_FLICKER, 0},
	{"ARMAGEDDON_GOLDBOX", 0, SPR_TVAR, 1, 2, A_GoldMonitorSparkle, 0, 0, S_GOLDBOX_FLICKER, 0},
	{"WHIRLWIND_GOLDBOX", 0, SPR_TVWW, 1, 2, A_GoldMonitorSparkle, 0, 0, S_GOLDBOX_FLICKER, 0},
	{"ELEMENTAL_GOLDBOX", 0, SPR_TVEL, 1, 2, A_GoldMonitorSparkle, 0, 0, S_GOLDBOX_FLICKER, 0},
	{"SNEAKERS_GOLDBOX", 0, SPR_TVSS, 1, 2, A_GoldMonitorSparkle, 0, 0, S_GOLDBOX_FLICKER, 0},
	{"INVULN_GOLDBOX", 0, SPR_TVIV, 1, 2, A_GoldMonitorSparkle, 0, 0, S_GOLDBOX_FLICKER, 0},
	{"EGGMAN_GOLDBOX", 0, SPR_TVEG, 1, 2, A_GoldMonitorSparkle, 0, 0, S_GOLDBOX_FLICKER, 0},
	{"GRAVITY_GOLDBOX", 0, SPR_TVGV, 1, 2, A_GoldMonitorSparkle, 0, 0, S_GOLDBOX_FLICKER, 0},
	{"FLAMEAURA_GOLDBOX", 0, SPR_TVFL, 1, 2, A_GoldMonitorSparkle, 0, 0, S_GOLDBOX_FLICKER, 0},
	{"BUBBLEWRAP_GOLDBOX", 0, SPR_TVBB, 1, 2, A_GoldMonitorSparkle, 0, 0, S_GOLDBOX_FLICKER, 0},
	{"THUNDERCOIN_GOLDBOX", 0, SPR_TVZP, 1, 2, A_GoldMonitorSparkle, 0, 0, S_GOLDBOX_FLICKER, 0},

	// Team Ring Boxes (these are special)
	{"RING_REDBOX1", 0, SPR_TRRI, 0, 2, NULL, 0, 0, S_RING_REDBOX2, 0},
	{"RING_REDBOX2", 0, SPR_TRRI, 1, 1, NULL, 0, 0, S_RING_REDBOX1, 0},
	{"REDBOX_POP1", 0, SPR_TRRI, 1, 4, A_MonitorPop, 0, 0, S_REDBOX_POP2, 0},
	{"REDBOX_POP2", 0, SPR_TRRI, 2, -1, NULL, 0, 0, S_NULL, 0},

	{"RING_BLUEBOX1", 0, SPR_TBRI, 0, 2, NULL, 0, 0, S_RING_BLUEBOX2, 0},
	{"RING_BLUEBOX2", 0, SPR_TBRI, 1, 1, NULL, 0, 0, S_RING_BLUEBOX1, 0},
	{"BLUEBOX_POP1", 0, SPR_TBRI, 1, 4, A_MonitorPop, 0, 0, S_BLUEBOX_POP2, 0},
	{"BLUEBOX_POP2", 0, SPR_TBRI, 2, -1, NULL, 0, 0, S_NULL, 0},

	// Box Icons -- 2 states each, animation and action
	{"RING_ICON1", 0, SPR_TVRI, FF_ANIMATE|2, 18, NULL, 3, 4, S_RING_ICON2, 0},
	{"RING_ICON2", 0, SPR_TVRI, 2, 18, A_RingBox, 0, 0, S_NULL, 0},

	{"PITY_ICON1", 0, SPR_TVPI, FF_ANIMATE|2, 18, NULL, 3, 4, S_PITY_ICON2, 0},
	{"PITY_ICON2", 0, SPR_TVPI, 2, 18, A_GiveShield, SH_PITY, 0, S_NULL, 0},

	{"ATTRACT_ICON1", 0, SPR_TVAT, FF_ANIMATE|2, 18, NULL, 3, 4, S_ATTRACT_ICON2, 0},
	{"ATTRACT_ICON2", 0, SPR_TVAT, 2, 18, A_GiveShield, SH_ATTRACT, 0, S_NULL, 0},

	{"FORCE_ICON1", 0, SPR_TVFO, FF_ANIMATE|2, 18, NULL, 3, 4, S_FORCE_ICON2, 0},
	{"FORCE_ICON2", 0, SPR_TVFO, 2, 18, A_GiveShield, SH_FORCE|1, 0, S_NULL, 0},

	{"ARMAGEDDON_ICON1", 0, SPR_TVAR, FF_ANIMATE|2, 18, NULL, 3, 4, S_ARMAGEDDON_ICON2, 0},
	{"ARMAGEDDON_ICON2", 0, SPR_TVAR, 2, 18, A_GiveShield, SH_ARMAGEDDON, 0, S_NULL, 0},

	{"WHIRLWIND_ICON1", 0, SPR_TVWW, FF_ANIMATE|2, 18, NULL, 3, 4, S_WHIRLWIND_ICON2, 0},
	{"WHIRLWIND_ICON2", 0, SPR_TVWW, 2, 18, A_GiveShield, SH_WHIRLWIND, 0, S_NULL, 0},

	{"ELEMENTAL_ICON1", 0, SPR_TVEL, FF_ANIMATE|2, 18, NULL, 3, 4, S_ELEMENTAL_ICON2, 0},
	{"ELEMENTAL_ICON2", 0, SPR_TVEL, 2, 18, A_GiveShield, SH_ELEMENTAL, 0, S_NULL, 0},

	{"SNEAKERS_ICON1", 0, SPR_TVSS, FF_ANIMATE|2, 18, NULL, 3, 4, S_SNEAKERS_ICON2, 0},
	{"SNEAKERS_ICON2", 0, SPR_TVSS, 2, 18, A_SuperSneakers, 0, 0, S_NULL, 0},

	{"INVULN_ICON1", 0, SPR_TVIV, FF_ANIMATE|2, 18, NULL, 3, 4, S_INVULN_ICON2, 0},
	{"INVULN_ICON2", 0, SPR_TVIV, 2, 18, A_Invincibility, 0, 0, S_NULL, 0},

	{"1UP_ICON1", 0, SPR_TV1U, FF_ANIMATE|2, 18, NULL, 3, 4, S_1UP_ICON2, 0},
	{"1UP_ICON2", 0, SPR_TV1U, 2, 18, A_ExtraLife,  0, 0, S_NULL, 0},

	{"EGGMAN_ICON1", 0, SPR_TVEG, FF_ANIMATE|2, 18, NULL, 3, 4, S_EGGMAN_ICON2, 0},
	{"EGGMAN_ICON2", 0, SPR_TVEG, 2, 18, A_EggmanBox, 0, 0, S_NULL, 0},

	{"MIXUP_ICON1", 0, SPR_TVMX, FF_ANIMATE|2, 18, NULL, 3, 4, S_MIXUP_ICON2, 0},
	{"MIXUP_ICON2", 0, SPR_TVMX, 2, 18, A_MixUp, 0, 0, S_NULL, 0},

	{"GRAVITY_ICON1", 0, SPR_TVGV, FF_ANIMATE|2, 18, NULL, 3, 4, S_GRAVITY_ICON2, 0},
	{"GRAVITY_ICON2", 0, SPR_TVGV, 2, 18, A_GravityBox, 0, 0, S_NULL, 0},

	{"RECYCLER_ICON1", 0, SPR_TVRC, FF_ANIMATE|2, 18, NULL, 3, 4, S_RECYCLER_ICON2, 0},
	{"RECYCLER_ICON2", 0, SPR_TVRC, 2, 18, A_RecyclePowers, 0, 0, S_NULL, 0},

	{"SCORE1K_ICON1", 0, SPR_TV1K, FF_ANIMATE|2, 18, NULL, 3, 4, S_SCORE1K_ICON2, 0},
	{"SCORE1K_ICON2", 0, SPR_TV1K, 2, 18, A_AwardScore, 0, 0, S_NULL, 0},

	{"SCORE10K_ICON1", 0, SPR_TVTK, FF_ANIMATE|2, 18, NULL, 3, 4, S_SCORE10K_ICON2, 0},
	{"SCORE10K_ICON2", 0, SPR_TVTK, 2, 18, A_AwardScore, 0, 0, S_NULL, 0},

	{"FLAMEAURA_ICON1", 0, SPR_TVFL, FF_ANIMATE|2, 18, NULL, 3, 4, S_FLAMEAURA_ICON2, 0},
	{"FLAMEAURA_ICON2", 0, SPR_TVFL, 2, 18, A_GiveShield, SH_FLAMEAURA, 0, S_NULL, 0},

	{"BUBBLEWRAP_ICON1", 0, SPR_TVBB, FF_ANIMATE|2, 18, NULL, 3, 4, S_BUBBLEWRAP_ICON2, 0},
	{"BUBBLEWRAP_ICON2", 0, SPR_TVBB, 2, 18, A_GiveShield, SH_BUBBLEWRAP, 0, S_NULL, 0},

	{"THUNDERCOIN_ICON1", 0, SPR_TVZP, FF_ANIMATE|2, 18, NULL, 3, 4, S_THUNDERCOIN_ICON2, 0},
	{"THUNDERCOIN_ICON2", 0, SPR_TVZP, 2, 18, A_GiveShield, SH_THUNDERCOIN, 0, S_NULL, 0},

	// ---

	{"ROCKET", 0, SPR_MISL, FF_FULLBRIGHT, 1, A_SmokeTrailer, MT_SMOKE, 0, S_ROCKET, 0},

	{"LASER", 0, SPR_LASR, FF_FULLBRIGHT|0, 2, NULL, 0, 0, S_NULL, 0},
	{"LASER2", 0, SPR_LASR, FF_FULLBRIGHT|1, 2, NULL, 0, 0, S_NULL, 0},
	{"LASERFLASH", 0, SPR_LASR, FF_FULLBRIGHT|2, 2, NULL, 0, 0, S_NULL, 0},

	{"LASERFLAME1", 0, SPR_LASF,                           FF_FULLBRIGHT|0,       2,           NULL, 0, 0, S_LASERFLAME2, 0},
	{"LASERFLAME2", 0, SPR_LASF,                           FF_FULLBRIGHT|1,       1, A_ChangeHeight, 156*FRACUNIT, 3, S_LASERFLAME3, 0},
	{"LASERFLAME3", 0, SPR_LASF,                           FF_FULLBRIGHT|2,       0, A_ChangeHeight, 32*FRACUNIT, 3, S_LASERFLAME4, 0},
	{"LASERFLAME4", 0, SPR_LASF, FF_ANIMATE|FF_PAPERSPRITE|FF_FULLBRIGHT|2,       4,           NULL, 1, 2, S_LASERFLAME5, 0},
	{"LASERFLAME5", 0, SPR_LASF, FF_ANIMATE|FF_PAPERSPRITE|FF_FULLBRIGHT|4,      28,           NULL, 2, 2, S_NULL, 0},

	{"TORPEDO", 0, SPR_TORP, 0, 1, A_SmokeTrailer, MT_SMOKE, 0, S_TORPEDO, 0},

	{"ENERGYBALL1", 0, SPR_ENRG, FF_FULLBRIGHT|FF_TRANS30, 1, NULL, 0, 0, S_ENERGYBALL2, 0},
	{"ENERGYBALL2", 0, SPR_NULL, 0, 1, NULL, 0, 0, S_ENERGYBALL1, 0},

	// Skim Mine (also dropped by Jetty-Syn bomber)
	{"MINE1", 0, SPR_MINE, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"MINE_BOOM1", 0, SPR_MINE, 1, 1, A_Fall, 0, 0, S_MINE_BOOM2, 0},
	{"MINE_BOOM2", 0, SPR_MINE, 2, 3, A_Scream, 0, 0, S_MINE_BOOM3, 0},
	{"MINE_BOOM3", 0, SPR_MINE, 3, 3, A_Explode, 0, 0, S_MINE_BOOM4, 0},
	{"MINE_BOOM4", 0, SPR_MINE, 4, 3, NULL, 0, 0, S_NULL, 0},

	// Jetty-Syn Bullet
	{"JETBULLET1", 0, SPR_JBUL, FF_FULLBRIGHT,   1, NULL, 0, 0, S_JETBULLET2, 0},
	{"JETBULLET2", 0, SPR_JBUL, FF_FULLBRIGHT|1, 1, NULL, 0, 0, S_JETBULLET1, 0},

	{"TURRETLASER", 0, SPR_TRLS, FF_FULLBRIGHT,   1, NULL, 0, 0, S_TURRETLASER, 0},
	{"TURRETLASEREXPLODE1", 0, SPR_TRLS, FF_FULLBRIGHT|1, 2, NULL, 0, 0, S_TURRETLASEREXPLODE2, 0},
	{"TURRETLASEREXPLODE2", 0, SPR_TRLS, FF_FULLBRIGHT|2, 2, NULL, 0, 0, S_NULL, 0},

	{"CANNONBALL1", 0, SPR_CBLL, 0, -1, NULL, 0, 0, S_NULL, 0},

	{"ARROW", 0, SPR_AROW, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"ARROWBONK", 0, SPR_AROW, FF_ANIMATE, TICRATE, A_ArrowBonks, 7, 2, S_NULL, 0},

	{"DEMONFIRE", 0, SPR_CFIR, FF_FULLBRIGHT|FF_ANIMATE, -1, NULL, 5, 2, S_NULL, 0},

	{"LETTER", 0, SPR_LETR, FF_PAPERSPRITE, -1, NULL, 0, 0, S_NULL, 0},

	// Tutorial scenery
	{"TUTORIALLEAF1", 0, SPR_TUPL, FF_SEMIBRIGHT|FF_ADD|FF_PAPERSPRITE|0, 3, NULL, 0, 0, S_TUTORIALLEAF2, 0},
	{"TUTORIALLEAF2", 0, SPR_TUPL, FF_SEMIBRIGHT|FF_ADD|FF_PAPERSPRITE|1, 3, NULL, 0, 0, S_TUTORIALLEAF3, 0},
	{"TUTORIALLEAF3", 0, SPR_TUPL, FF_SEMIBRIGHT|FF_ADD|FF_PAPERSPRITE|2, 3, NULL, 0, 0, S_TUTORIALLEAF4, 0},
	{"TUTORIALLEAF4", 0, SPR_TUPL, FF_SEMIBRIGHT|FF_ADD|FF_PAPERSPRITE|3, 3, NULL, 0, 0, S_TUTORIALLEAF5, 0},
	{"TUTORIALLEAF5", 0, SPR_TUPL, FF_SEMIBRIGHT|FF_ADD|FF_PAPERSPRITE|4, 3, NULL, 0, 0, S_TUTORIALLEAF6, 0},
	{"TUTORIALLEAF6", 0, SPR_TUPL, FF_SEMIBRIGHT|FF_ADD|FF_PAPERSPRITE|5, 3, NULL, 0, 0, S_TUTORIALLEAF7, 0},
	{"TUTORIALLEAF7", 0, SPR_TUPL, FF_SEMIBRIGHT|FF_ADD|FF_PAPERSPRITE|6, 3, NULL, 0, 0, S_TUTORIALLEAF8, 0},
	{"TUTORIALLEAF8", 0, SPR_TUPL, FF_SEMIBRIGHT|FF_ADD|FF_PAPERSPRITE|7, 3, NULL, 0, 0, S_TUTORIALLEAF9, 0},
	{"TUTORIALLEAF9", 0, SPR_TUPL, FF_SEMIBRIGHT|FF_ADD|FF_PAPERSPRITE|7, 3, NULL, 0, 0, S_TUTORIALLEAF10, 0},
	{"TUTORIALLEAF10", 0, SPR_TUPL, FF_SEMIBRIGHT|FF_ADD|FF_PAPERSPRITE|6, 3, NULL, 0, 0, S_TUTORIALLEAF11, 0},
	{"TUTORIALLEAF11", 0, SPR_TUPL, FF_SEMIBRIGHT|FF_ADD|FF_PAPERSPRITE|5, 3, NULL, 0, 0, S_TUTORIALLEAF12, 0},
	{"TUTORIALLEAF12", 0, SPR_TUPL, FF_SEMIBRIGHT|FF_ADD|FF_PAPERSPRITE|4, 3, NULL, 0, 0, S_TUTORIALLEAF13, 0},
	{"TUTORIALLEAF13", 0, SPR_TUPL, FF_SEMIBRIGHT|FF_ADD|FF_PAPERSPRITE|3, 3, NULL, 0, 0, S_TUTORIALLEAF14, 0},
	{"TUTORIALLEAF14", 0, SPR_TUPL, FF_SEMIBRIGHT|FF_ADD|FF_PAPERSPRITE|2, 3, NULL, 0, 0, S_TUTORIALLEAF15, 0},
	{"TUTORIALLEAF15", 0, SPR_TUPL, FF_SEMIBRIGHT|FF_ADD|FF_PAPERSPRITE|1, 3, NULL, 0, 0, S_TUTORIALLEAF16, 0},
	{"TUTORIALLEAF16", 0, SPR_TUPL, FF_SEMIBRIGHT|FF_ADD|FF_PAPERSPRITE|0, 3, NULL, 0, 0, S_TUTORIALLEAF1, 0},
	{"TUTORIALFLOWER1", 0, SPR_TUPF, FF_SEMIBRIGHT|FF_ADD|FF_PAPERSPRITE|0, 3, NULL, 0, 0, S_TUTORIALFLOWER2, 0},
	{"TUTORIALFLOWER2", 0, SPR_TUPF, FF_SEMIBRIGHT|FF_ADD|FF_PAPERSPRITE|1, 3, NULL, 0, 0, S_TUTORIALFLOWER3, 0},
	{"TUTORIALFLOWER3", 0, SPR_TUPF, FF_SEMIBRIGHT|FF_ADD|FF_PAPERSPRITE|2, 3, NULL, 0, 0, S_TUTORIALFLOWER4, 0},
	{"TUTORIALFLOWER4", 0, SPR_TUPF, FF_SEMIBRIGHT|FF_ADD|FF_PAPERSPRITE|3, 3, NULL, 0, 0, S_TUTORIALFLOWER5, 0},
	{"TUTORIALFLOWER5", 0, SPR_TUPF, FF_SEMIBRIGHT|FF_ADD|FF_PAPERSPRITE|4, 3, NULL, 0, 0, S_TUTORIALFLOWER6, 0},
	{"TUTORIALFLOWER6", 0, SPR_TUPF, FF_SEMIBRIGHT|FF_ADD|FF_PAPERSPRITE|5, 3, NULL, 0, 0, S_TUTORIALFLOWER7, 0},
	{"TUTORIALFLOWER7", 0, SPR_TUPF, FF_SEMIBRIGHT|FF_ADD|FF_PAPERSPRITE|6, 3, NULL, 0, 0, S_TUTORIALFLOWER8, 0},
	{"TUTORIALFLOWER8", 0, SPR_TUPF, FF_SEMIBRIGHT|FF_ADD|FF_PAPERSPRITE|7, 3, NULL, 0, 0, S_TUTORIALFLOWER9, 0},
	{"TUTORIALFLOWER9", 0, SPR_TUPF, FF_SEMIBRIGHT|FF_ADD|FF_PAPERSPRITE|7, 3, NULL, 0, 0, S_TUTORIALFLOWER10, 0},
	{"TUTORIALFLOWER10", 0, SPR_TUPF, FF_SEMIBRIGHT|FF_ADD|FF_PAPERSPRITE|6, 3, NULL, 0, 0, S_TUTORIALFLOWER11, 0},
	{"TUTORIALFLOWER11", 0, SPR_TUPF, FF_SEMIBRIGHT|FF_ADD|FF_PAPERSPRITE|5, 3, NULL, 0, 0, S_TUTORIALFLOWER12, 0},
	{"TUTORIALFLOWER12", 0, SPR_TUPF, FF_SEMIBRIGHT|FF_ADD|FF_PAPERSPRITE|4, 3, NULL, 0, 0, S_TUTORIALFLOWER13, 0},
	{"TUTORIALFLOWER13", 0, SPR_TUPF, FF_SEMIBRIGHT|FF_ADD|FF_PAPERSPRITE|3, 3, NULL, 0, 0, S_TUTORIALFLOWER14, 0},
	{"TUTORIALFLOWER14", 0, SPR_TUPF, FF_SEMIBRIGHT|FF_ADD|FF_PAPERSPRITE|2, 3, NULL, 0, 0, S_TUTORIALFLOWER15, 0},
	{"TUTORIALFLOWER15", 0, SPR_TUPF, FF_SEMIBRIGHT|FF_ADD|FF_PAPERSPRITE|1, 3, NULL, 0, 0, S_TUTORIALFLOWER16, 0},
	{"TUTORIALFLOWER16", 0, SPR_TUPF, FF_SEMIBRIGHT|FF_ADD|FF_PAPERSPRITE|0, 3, NULL, 0, 0, S_TUTORIALFLOWER1, 0},
	{"TUTORIALFLOWERF1", 0, SPR_TUPF, FF_SEMIBRIGHT|FF_ADD|FF_FLOORSPRITE|0, 3, NULL, 0, 0, S_TUTORIALFLOWERF2, 0},
	{"TUTORIALFLOWERF2", 0, SPR_TUPF, FF_SEMIBRIGHT|FF_ADD|FF_FLOORSPRITE|1, 3, NULL, 0, 0, S_TUTORIALFLOWERF3, 0},
	{"TUTORIALFLOWERF3", 0, SPR_TUPF, FF_SEMIBRIGHT|FF_ADD|FF_FLOORSPRITE|2, 3, NULL, 0, 0, S_TUTORIALFLOWERF4, 0},
	{"TUTORIALFLOWERF4", 0, SPR_TUPF, FF_SEMIBRIGHT|FF_ADD|FF_FLOORSPRITE|3, 3, NULL, 0, 0, S_TUTORIALFLOWERF5, 0},
	{"TUTORIALFLOWERF5", 0, SPR_TUPF, FF_SEMIBRIGHT|FF_ADD|FF_FLOORSPRITE|4, 3, NULL, 0, 0, S_TUTORIALFLOWERF6, 0},
	{"TUTORIALFLOWERF6", 0, SPR_TUPF, FF_SEMIBRIGHT|FF_ADD|FF_FLOORSPRITE|5, 3, NULL, 0, 0, S_TUTORIALFLOWERF7, 0},
	{"TUTORIALFLOWERF7", 0, SPR_TUPF, FF_SEMIBRIGHT|FF_ADD|FF_FLOORSPRITE|6, 3, NULL, 0, 0, S_TUTORIALFLOWERF8, 0},
	{"TUTORIALFLOWERF8", 0, SPR_TUPF, FF_SEMIBRIGHT|FF_ADD|FF_FLOORSPRITE|7, 3, NULL, 0, 0, S_TUTORIALFLOWERF9, 0},
	{"TUTORIALFLOWERF9", 0, SPR_TUPF, FF_SEMIBRIGHT|FF_ADD|FF_FLOORSPRITE|7, 3, NULL, 0, 0, S_TUTORIALFLOWERF10, 0},
	{"TUTORIALFLOWERF10", 0, SPR_TUPF, FF_SEMIBRIGHT|FF_ADD|FF_FLOORSPRITE|6, 3, NULL, 0, 0, S_TUTORIALFLOWERF11, 0},
	{"TUTORIALFLOWERF11", 0, SPR_TUPF, FF_SEMIBRIGHT|FF_ADD|FF_FLOORSPRITE|5, 3, NULL, 0, 0, S_TUTORIALFLOWERF12, 0},
	{"TUTORIALFLOWERF12", 0, SPR_TUPF, FF_SEMIBRIGHT|FF_ADD|FF_FLOORSPRITE|4, 3, NULL, 0, 0, S_TUTORIALFLOWERF13, 0},
	{"TUTORIALFLOWERF13", 0, SPR_TUPF, FF_SEMIBRIGHT|FF_ADD|FF_FLOORSPRITE|3, 3, NULL, 0, 0, S_TUTORIALFLOWERF14, 0},
	{"TUTORIALFLOWERF14", 0, SPR_TUPF, FF_SEMIBRIGHT|FF_ADD|FF_FLOORSPRITE|2, 3, NULL, 0, 0, S_TUTORIALFLOWERF15, 0},
	{"TUTORIALFLOWERF15", 0, SPR_TUPF, FF_SEMIBRIGHT|FF_ADD|FF_FLOORSPRITE|1, 3, NULL, 0, 0, S_TUTORIALFLOWERF16, 0},
	{"TUTORIALFLOWERF16", 0, SPR_TUPF, FF_SEMIBRIGHT|FF_ADD|FF_FLOORSPRITE|0, 3, NULL, 0, 0, S_TUTORIALFLOWERF1, 0},

	// GFZ flowers
	{"GFZFLOWERA", 0, SPR_FWR1, FF_ANIMATE, -1, NULL,  7, 3, S_NULL, 0},
	{"GFZFLOWERB", 0, SPR_FWR2, FF_ANIMATE, -1, NULL, 19, 3, S_NULL, 0},
	{"GFZFLOWERC", 0, SPR_FWR3, FF_ANIMATE, -1, NULL, 11, 4, S_NULL, 0},

	{"BLUEBERRYBUSH", 0, SPR_BUS3, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"BERRYBUSH", 0, SPR_BUS1, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"BUSH", 0, SPR_BUS2, 0, -1, NULL, 0, 0, S_NULL, 0},

	// Trees
	{"GFZTREE", 0, SPR_TRE1, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"GFZBERRYTREE", 0, SPR_TRE1, 1, -1, NULL, 0, 0, S_NULL, 0},
	{"GFZCHERRYTREE", 0, SPR_TRE1, 2, -1, NULL, 0, 0, S_NULL, 0},
	{"CHECKERTREE", 0, SPR_TRE2, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"CHECKERSUNSETTREE", 0, SPR_TRE2, 1, -1, NULL, 0, 0, S_NULL, 0},
	{"FHZTREE", 0, SPR_TRE3, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"FHZPINKTREE", 0, SPR_TRE3, 1, -1, NULL, 0, 0, S_NULL, 0},
	{"POLYGONTREE", 0, SPR_TRE4, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"BUSHTREE", 0, SPR_TRE5, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"BUSHREDTREE", 0, SPR_TRE5, 1, -1, NULL, 0, 0, S_NULL, 0},
	{"SPRINGTREE", 0, SPR_TRE6, 0, -1, NULL, 0, 0, S_NULL, 0},

	// THZ flowers
	{"THZFLOWERA", 0, SPR_THZP, FF_ANIMATE, -1, NULL,  7, 4, S_NULL, 0},
	{"THZFLOWERB", 0, SPR_FWR5, FF_ANIMATE, -1, NULL, 19, 2, S_NULL, 0},
	{"THZFLOWERC", 0, SPR_FWR6, FF_ANIMATE, -1, NULL, 19, 2, S_NULL, 0},

	// THZ Steam Whistle tree/bush
	{"THZTREE", 0, SPR_THZT, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"THZTREEBRANCH1", 0, SPR_THZT,  1|FF_PAPERSPRITE, 40, NULL, 0, 0, S_THZTREEBRANCH2, 0},
	{"THZTREEBRANCH2", 0, SPR_THZT,  2|FF_PAPERSPRITE,  4, NULL, 0, 0, S_THZTREEBRANCH3, 0},
	{"THZTREEBRANCH3", 0, SPR_THZT,  3|FF_PAPERSPRITE,  4, NULL, 0, 0, S_THZTREEBRANCH4, 0},
	{"THZTREEBRANCH4", 0, SPR_THZT,  4|FF_PAPERSPRITE,  4, NULL, 0, 0, S_THZTREEBRANCH5, 0},
	{"THZTREEBRANCH5", 0, SPR_THZT,  5|FF_PAPERSPRITE,  4, NULL, 0, 0, S_THZTREEBRANCH6, 0},
	{"THZTREEBRANCH6", 0, SPR_THZT,  6|FF_PAPERSPRITE,  4, NULL, 0, 0, S_THZTREEBRANCH7, 0},
	{"THZTREEBRANCH7", 0, SPR_THZT,  7|FF_PAPERSPRITE,  4, NULL, 0, 0, S_THZTREEBRANCH8, 0},
	{"THZTREEBRANCH8", 0, SPR_THZT,  8|FF_PAPERSPRITE,  4, NULL, 0, 0, S_THZTREEBRANCH9, 0},
	{"THZTREEBRANCH9", 0, SPR_THZT,  9|FF_PAPERSPRITE,  4, NULL, 0, 0, S_THZTREEBRANCH10, 0},
	{"THZTREEBRANCH10", 0, SPR_THZT, 10|FF_PAPERSPRITE,  4, NULL, 0, 0, S_THZTREEBRANCH11, 0},
	{"THZTREEBRANCH11", 0, SPR_THZT, 11|FF_PAPERSPRITE,  4, NULL, 0, 0, S_THZTREEBRANCH12, 0},
	{"THZTREEBRANCH12", 0, SPR_THZT, 12|FF_PAPERSPRITE,  4, NULL, 0, 0, S_THZTREEBRANCH13, 0},
	{"THZTREEBRANCH13", 0, SPR_THZT, 13|FF_PAPERSPRITE,  4, NULL, 0, 0, S_THZTREEBRANCH1, 0},

	// THZ Alarm
	{"ALARM1", 0, SPR_ALRM, FF_FULLBRIGHT, 35, A_Scream, 0, 0, S_ALARM1, 0},

	// Deep Sea Gargoyle
	{"GARGOYLE", 0, SPR_GARG, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"BIGGARGOYLE", 0, SPR_GARG, 1, -1, NULL, 0, 0, S_NULL, 0},

	// DSZ Seaweed
	{"SEAWEED1", 0, SPR_SEWE, FF_ANIMATE|FF_RANDOMANIM, -1, NULL, 26, 3, S_SEAWEED1, 0},
	{"SEAWEED2", 0, SPR_SEWE, 1, 5, NULL, 0, 0, S_SEAWEED3, 0},
	{"SEAWEED3", 0, SPR_SEWE, 2, 5, NULL, 0, 0, S_SEAWEED4, 0},
	{"SEAWEED4", 0, SPR_SEWE, 3, 5, NULL, 0, 0, S_SEAWEED5, 0},
	{"SEAWEED5", 0, SPR_SEWE, 4, 5, NULL, 0, 0, S_SEAWEED6, 0},
	{"SEAWEED6", 0, SPR_SEWE, 5, 5, NULL, 0, 0, S_SEAWEED1, 0},

	// Dripping water
	{"DRIPA1", 0, SPR_NULL, FF_TRANS30  , 3*TICRATE, NULL,                  0, 0, S_DRIPA2, 0},
	{"DRIPA2", 0, SPR_DRIP, FF_TRANS30  ,         2, NULL,                  0, 0, S_DRIPA3, 0},
	{"DRIPA3", 0, SPR_DRIP, FF_TRANS30|1,         2, NULL,                  0, 0, S_DRIPA4, 0},
	{"DRIPA4", 0, SPR_DRIP, FF_TRANS30|2,         2, A_SpawnObjectRelative, 0, MT_WATERDROP, S_DRIPA1, 0},
	{"DRIPB1", 0, SPR_DRIP, FF_TRANS30|3,        -1, NULL,                  0, 0, S_DRIPB1, 0},
	{"DRIPC1", 0, SPR_DRIP, FF_TRANS30|4,         1, NULL,                  0, 0, S_DRIPC2, 0},
	{"DRIPC2", 0, SPR_DRIP, FF_TRANS30|5,         1, NULL,                  0, 0,   S_NULL, 0},

	// Coral
	{"CORAL1", 0, SPR_CORL, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"CORAL2", 0, SPR_CORL, 1, -1, NULL, 0, 0, S_NULL, 0},
	{"CORAL3", 0, SPR_CORL, 2, -1, NULL, 0, 0, S_NULL, 0},
	{"CORAL4", 0, SPR_CORL, 3, -1, NULL, 0, 0, S_NULL, 0},
	{"CORAL5", 0, SPR_CORL, 4, -1, NULL, 0, 0, S_NULL, 0},

	// Blue Crystal
	{"BLUECRYSTAL1", 0, SPR_BCRY, FF_TRANS30, -1, NULL, 0, 0, S_NULL, 0},

	// Kelp
	{"KELP", 0, SPR_KELP, 0, -1, NULL, 0, 0, S_NULL, 0},

	// Animated algae
	{"ANIMALGAETOP1", 0, SPR_ALGA, 0, 1, A_ConnectToGround, MT_ANIMALGAESEG, 0, S_ANIMALGAETOP2, 0},
	{"ANIMALGAETOP2", 0, SPR_ALGA, 0|FF_ANIMATE|FF_RANDOMANIM, -1, NULL, 11, 4, S_NULL, 0},
	{"ANIMALGAESEG", 0, SPR_ALGB, 0|FF_ANIMATE|FF_RANDOMANIM, -1, NULL, 11, 4, S_NULL, 0},

	// DSZ Stalagmites
	{"DSZSTALAGMITE", 0, SPR_DSTG, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"DSZ2STALAGMITE", 0, SPR_DSTG, 1, -1, NULL, 0, 0, S_NULL, 0},

	// DSZ Light beam
	{"LIGHTBEAM1", 0, SPR_LIBE, 0|FF_TRANS80|FF_FULLBRIGHT|FF_PAPERSPRITE, 4, A_LightBeamReset, 0, 0, S_LIGHTBEAM2, 0},
	{"LIGHTBEAM2", 0, SPR_LIBE, 0|FF_TRANS70|FF_FULLBRIGHT|FF_PAPERSPRITE, 4, NULL, 0, 0, S_LIGHTBEAM3, 0},
	{"LIGHTBEAM3", 0, SPR_LIBE, 0|FF_TRANS60|FF_FULLBRIGHT|FF_PAPERSPRITE, 4, NULL, 0, 0, S_LIGHTBEAM4, 0},
	{"LIGHTBEAM4", 0, SPR_LIBE, 0|FF_TRANS50|FF_FULLBRIGHT|FF_PAPERSPRITE, 2, NULL, 0, 0, S_LIGHTBEAM5, 0},
	{"LIGHTBEAM5", 0, SPR_LIBE, 0|FF_TRANS40|FF_FULLBRIGHT|FF_PAPERSPRITE, 2, NULL, 0, 0, S_LIGHTBEAM6, 0},
	{"LIGHTBEAM6", 0, SPR_LIBE, 0|FF_TRANS30|FF_FULLBRIGHT|FF_PAPERSPRITE, 9, NULL, 0, 0, S_LIGHTBEAM7, 0},
	{"LIGHTBEAM7", 0, SPR_LIBE, 0|FF_TRANS40|FF_FULLBRIGHT|FF_PAPERSPRITE, 2, NULL, 0, 0, S_LIGHTBEAM8, 0},
	{"LIGHTBEAM8", 0, SPR_LIBE, 0|FF_TRANS50|FF_FULLBRIGHT|FF_PAPERSPRITE, 2, NULL, 0, 0, S_LIGHTBEAM9, 0},
	{"LIGHTBEAM9", 0, SPR_LIBE, 0|FF_TRANS60|FF_FULLBRIGHT|FF_PAPERSPRITE, 4, NULL, 0, 0, S_LIGHTBEAM10, 0},
	{"LIGHTBEAM10", 0, SPR_LIBE, 0|FF_TRANS70|FF_FULLBRIGHT|FF_PAPERSPRITE, 4, NULL, 0, 0, S_LIGHTBEAM11, 0},
	{"LIGHTBEAM11", 0, SPR_LIBE, 0|FF_TRANS80|FF_FULLBRIGHT|FF_PAPERSPRITE, 4, NULL, 0, 0, S_LIGHTBEAM12, 0},
	{"LIGHTBEAM12", 0, SPR_NULL, 0, 2, A_SetRandomTics, 4, 35, S_LIGHTBEAM1, 0},

	// CEZ Chain
	{"CEZCHAIN", 0, SPR_CHAN, 0, -1, NULL, 0, 0, S_NULL, 0},

	// Flame
	{"FLAME", 0, SPR_FLAM, FF_FULLBRIGHT|FF_ANIMATE,       3*8, A_FlameParticle, 7, 3, S_FLAME, 0},
	{"FLAMEPARTICLE", 0, SPR_FLAM, FF_FULLBRIGHT|FF_ANIMATE|8, TICRATE,            NULL, 3, 3, S_NULL, 0},
	{"FLAMEREST", 0, SPR_FLAM, FF_FULLBRIGHT|FF_ANIMATE,        -1,            NULL, 7, 3, S_NULL, 0},

	// Eggman statue
	{"EGGSTATUE1", 0, SPR_ESTA, 0, -1, NULL, 0, 0, S_NULL, 0},

	// Hidden sling appears
	{"SLING1", 0, SPR_NULL, 0, -1, NULL,          0, 0, S_SLING2, 0},
	{"SLING2", 0, SPR_NULL, 0, -1, A_SlingAppear, 0, 0, S_NULL, 0},

	// CEZ maces and chains
	{"SMALLMACECHAIN", 0, SPR_SMCH, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"BIGMACECHAIN", 0, SPR_BMCH, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"SMALLMACE", 0, SPR_SMCE, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"BIGMACE", 0, SPR_BMCE, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"SMALLGRABCHAIN", 0, SPR_SMCH, 1, -1, NULL, 0, 0, S_NULL, 0},
	{"BIGGRABCHAIN", 0, SPR_BMCH, 1, -1, NULL, 0, 0, S_NULL, 0},

	// Blue spring on a ball
	{"BLUESPRINGBALL", 0, SPR_BSPB, 0, -1, NULL,   0, 0, S_NULL, 0},
	{"BLUESPRINGBALL2", 0, SPR_BSPB, 4,  4, A_Pain, 0, 0, S_BLUESPRINGBALL3, 0},
	{"BLUESPRINGBALL3", 0, SPR_BSPB, 3,  1, NULL,   0, 0, S_BLUESPRINGBALL4, 0},
	{"BLUESPRINGBALL4", 0, SPR_BSPB, 2,  1, NULL,   0, 0, S_BLUESPRINGBALL5, 0},
	{"BLUESPRINGBALL5", 0, SPR_BSPB, 1,  1, NULL,   0, 0, S_BLUESPRINGBALL, 0},

	// Yellow spring on a ball
	{"YELLOWSPRINGBALL", 0, SPR_YSPB, 0, -1, NULL,   0, 0, S_NULL, 0},
	{"YELLOWSPRINGBALL2", 0, SPR_YSPB, 4,  4, A_Pain, 0, 0, S_YELLOWSPRINGBALL3, 0},
	{"YELLOWSPRINGBALL3", 0, SPR_YSPB, 3,  1, NULL,   0, 0, S_YELLOWSPRINGBALL4, 0},
	{"YELLOWSPRINGBALL4", 0, SPR_YSPB, 2,  1, NULL,   0, 0, S_YELLOWSPRINGBALL5, 0},
	{"YELLOWSPRINGBALL5", 0, SPR_YSPB, 1,  1, NULL,   0, 0, S_YELLOWSPRINGBALL, 0},

	// Red spring on a ball
	{"REDSPRINGBALL", 0, SPR_RSPB, 0, -1, NULL,   0, 0, S_NULL, 0},
	{"REDSPRINGBALL2", 0, SPR_RSPB, 4,  4, A_Pain, 0, 0, S_REDSPRINGBALL3, 0},
	{"REDSPRINGBALL3", 0, SPR_RSPB, 3,  1, NULL,   0, 0, S_REDSPRINGBALL4, 0},
	{"REDSPRINGBALL4", 0, SPR_RSPB, 2,  1, NULL,   0, 0, S_REDSPRINGBALL5, 0},
	{"REDSPRINGBALL5", 0, SPR_RSPB, 1,  1, NULL,   0, 0, S_REDSPRINGBALL, 0},

	// Small Firebar
	{"SMALLFIREBAR1", 0, SPR_SFBR, FF_FULLBRIGHT,     1, NULL,            0, 0, S_SMALLFIREBAR2, 0},
	{"SMALLFIREBAR2", 0, SPR_SFBR, FF_FULLBRIGHT| 1,  1, NULL,            0, 0, S_SMALLFIREBAR3, 0},
	{"SMALLFIREBAR3", 0, SPR_SFBR, FF_FULLBRIGHT| 2,  1, A_FlameParticle, 0, 0, S_SMALLFIREBAR4, 0},
	{"SMALLFIREBAR4", 0, SPR_SFBR, FF_FULLBRIGHT| 3,  1, NULL,            0, 0, S_SMALLFIREBAR5, 0},
	{"SMALLFIREBAR5", 0, SPR_SFBR, FF_FULLBRIGHT| 4,  1, NULL,            0, 0, S_SMALLFIREBAR6, 0},
	{"SMALLFIREBAR6", 0, SPR_SFBR, FF_FULLBRIGHT| 5,  1, NULL,            0, 0, S_SMALLFIREBAR7, 0},
	{"SMALLFIREBAR7", 0, SPR_SFBR, FF_FULLBRIGHT| 6,  1, A_FlameParticle, 0, 0, S_SMALLFIREBAR8, 0},
	{"SMALLFIREBAR8", 0, SPR_SFBR, FF_FULLBRIGHT| 7,  1, NULL,            0, 0, S_SMALLFIREBAR9, 0},
	{"SMALLFIREBAR9", 0, SPR_SFBR, FF_FULLBRIGHT| 8,  1, NULL,            0, 0, S_SMALLFIREBAR10, 0},
	{"SMALLFIREBAR10", 0, SPR_SFBR, FF_FULLBRIGHT| 9,  1, NULL,            0, 0, S_SMALLFIREBAR11, 0},
	{"SMALLFIREBAR11", 0, SPR_SFBR, FF_FULLBRIGHT|10,  1, A_FlameParticle, 0, 0, S_SMALLFIREBAR12, 0},
	{"SMALLFIREBAR12", 0, SPR_SFBR, FF_FULLBRIGHT|11,  1, NULL,            0, 0, S_SMALLFIREBAR13, 0},
	{"SMALLFIREBAR13", 0, SPR_SFBR, FF_FULLBRIGHT|12,  1, NULL,            0, 0, S_SMALLFIREBAR14, 0},
	{"SMALLFIREBAR14", 0, SPR_SFBR, FF_FULLBRIGHT|13,  1, NULL,            0, 0, S_SMALLFIREBAR15, 0},
	{"SMALLFIREBAR15", 0, SPR_SFBR, FF_FULLBRIGHT|14,  1, A_FlameParticle, 0, 0, S_SMALLFIREBAR16, 0},
	{"SMALLFIREBAR16", 0, SPR_SFBR, FF_FULLBRIGHT|15,  1, NULL,            0, 0, S_SMALLFIREBAR1, 0},

	// Big Firebar
	{"BIGFIREBAR1", 0, SPR_BFBR, FF_FULLBRIGHT,     1, NULL,            0, 0, S_BIGFIREBAR2, 0},
	{"BIGFIREBAR2", 0, SPR_BFBR, FF_FULLBRIGHT| 1,  1, NULL,            0, 0, S_BIGFIREBAR3, 0},
	{"BIGFIREBAR3", 0, SPR_BFBR, FF_FULLBRIGHT| 2,  1, A_FlameParticle, 0, 0, S_BIGFIREBAR4, 0},
	{"BIGFIREBAR4", 0, SPR_BFBR, FF_FULLBRIGHT| 3,  1, NULL,            0, 0, S_BIGFIREBAR5, 0},
	{"BIGFIREBAR5", 0, SPR_BFBR, FF_FULLBRIGHT| 4,  1, NULL,            0, 0, S_BIGFIREBAR6, 0},
	{"BIGFIREBAR6", 0, SPR_BFBR, FF_FULLBRIGHT| 5,  1, NULL,            0, 0, S_BIGFIREBAR7, 0},
	{"BIGFIREBAR7", 0, SPR_BFBR, FF_FULLBRIGHT| 6,  1, A_FlameParticle, 0, 0, S_BIGFIREBAR8, 0},
	{"BIGFIREBAR8", 0, SPR_BFBR, FF_FULLBRIGHT| 7,  1, NULL,            0, 0, S_BIGFIREBAR9, 0},
	{"BIGFIREBAR9", 0, SPR_BFBR, FF_FULLBRIGHT| 8,  1, NULL,            0, 0, S_BIGFIREBAR10, 0},
	{"BIGFIREBAR10", 0, SPR_BFBR, FF_FULLBRIGHT| 9,  1, NULL,            0, 0, S_BIGFIREBAR11, 0},
	{"BIGFIREBAR11", 0, SPR_BFBR, FF_FULLBRIGHT|10,  1, A_FlameParticle, 0, 0, S_BIGFIREBAR12, 0},
	{"BIGFIREBAR12", 0, SPR_BFBR, FF_FULLBRIGHT|11,  1, NULL,            0, 0, S_BIGFIREBAR13, 0},
	{"BIGFIREBAR13", 0, SPR_BFBR, FF_FULLBRIGHT|12,  1, NULL,            0, 0, S_BIGFIREBAR14, 0},
	{"BIGFIREBAR14", 0, SPR_BFBR, FF_FULLBRIGHT|13,  1, NULL,            0, 0, S_BIGFIREBAR15, 0},
	{"BIGFIREBAR15", 0, SPR_BFBR, FF_FULLBRIGHT|14,  1, A_FlameParticle, 0, 0, S_BIGFIREBAR16, 0},
	{"BIGFIREBAR16", 0, SPR_BFBR, FF_FULLBRIGHT|15,  1, NULL,            0, 0, S_BIGFIREBAR1, 0},

	{"CEZFLOWER", 0, SPR_FWR4, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"CEZPOLE", 0, SPR_BANR, 0, -1, NULL, 0, 0, S_NULL, 0},

	{"CEZBANNER1", 0, SPR_BANR, FF_PAPERSPRITE|1, -1, NULL, 0, 0, S_NULL, 0},
	{"CEZBANNER2", 0, SPR_BANR, FF_PAPERSPRITE|2, -1, NULL, 0, 0, S_NULL, 0},

	{"PINETREE", 0, SPR_PINE, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"CEZBUSH1", 0, SPR_CEZB, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"CEZBUSH2", 0, SPR_CEZB, 1, -1, NULL, 0, 0, S_NULL, 0},

	{"CANDLE", 0, SPR_CNDL, FF_FULLBRIGHT,   -1, NULL, 0, 0, S_NULL, 0},
	{"CANDLEPRICKET", 0, SPR_CNDL, FF_FULLBRIGHT|1, -1, NULL, 0, 0, S_NULL, 0},

	{"FLAMEHOLDER", 0, SPR_FLMH, 0, -1, NULL, 0, 0, S_NULL, 0},

	{"FIRETORCH", 0, SPR_CTRC, FF_FULLBRIGHT|FF_ANIMATE, 8*3, A_FlameParticle, 3, 3, S_FIRETORCH, 0},

	{"WAVINGFLAG", 0, SPR_CFLG,                0, -1, NULL, 0, 0, S_NULL, 0},
	{"WAVINGFLAGSEG1", 0, SPR_CFLG, FF_PAPERSPRITE|1, -1, NULL, 0, 0, S_NULL, 0},
	{"WAVINGFLAGSEG2", 0, SPR_CFLG, FF_PAPERSPRITE|2, -1, NULL, 0, 0, S_NULL, 0},

	{"CRAWLASTATUE", 0, SPR_CSTA, 0, -1, NULL, 0, 0, S_NULL, 0},

	{"FACESTABBERSTATUE", 0, SPR_CBBS, 0, -1, NULL, 0, 0, S_NULL, 0},

	{"SUSPICIOUSFACESTABBERSTATUE_WAIT", 0, SPR_CBBS, 0, 5, A_Look, 768*FRACUNIT, 0, S_SUSPICIOUSFACESTABBERSTATUE_WAIT, 0},
	{"SUSPICIOUSFACESTABBERSTATUE_BURST1", 0, SPR_CBBS, FF_ANIMATE, 23, NULL,    6, 1, S_SUSPICIOUSFACESTABBERSTATUE_BURST2, 0},
	{"SUSPICIOUSFACESTABBERSTATUE_BURST2", 0, SPR_NULL, 0, 40, A_StatueBurst, MT_FACESTABBER, S_FACESTABBER_CHARGE2, S_NULL, 0},

	{"BRAMBLES", 0, SPR_CABR, 0, -1, NULL, 0, 0, S_NULL, 0},

	// Big Tumbleweed
	{"BIGTUMBLEWEED", 0, SPR_BTBL, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"BIGTUMBLEWEED_ROLL1", 0, SPR_BTBL, 0,  5, NULL, 0, 0, S_BIGTUMBLEWEED_ROLL2, 0},
	{"BIGTUMBLEWEED_ROLL2", 0, SPR_BTBL, 1,  5, NULL, 0, 0, S_BIGTUMBLEWEED_ROLL3, 0},
	{"BIGTUMBLEWEED_ROLL3", 0, SPR_BTBL, 2,  5, NULL, 0, 0, S_BIGTUMBLEWEED_ROLL4, 0},
	{"BIGTUMBLEWEED_ROLL4", 0, SPR_BTBL, 3,  5, NULL, 0, 0, S_BIGTUMBLEWEED_ROLL5, 0},
	{"BIGTUMBLEWEED_ROLL5", 0, SPR_BTBL, 4,  5, NULL, 0, 0, S_BIGTUMBLEWEED_ROLL6, 0},
	{"BIGTUMBLEWEED_ROLL6", 0, SPR_BTBL, 5,  5, NULL, 0, 0, S_BIGTUMBLEWEED_ROLL7, 0},
	{"BIGTUMBLEWEED_ROLL7", 0, SPR_BTBL, 6,  5, NULL, 0, 0, S_BIGTUMBLEWEED_ROLL8, 0},
	{"BIGTUMBLEWEED_ROLL8", 0, SPR_BTBL, 7,  5, NULL, 0, 0, S_BIGTUMBLEWEED_ROLL1, 0},

	// Little Tumbleweed
	{"LITTLETUMBLEWEED", 0, SPR_STBL, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"LITTLETUMBLEWEED_ROLL1", 0, SPR_STBL, 0, 5, NULL, 0, 0, S_LITTLETUMBLEWEED_ROLL2, 0},
	{"LITTLETUMBLEWEED_ROLL2", 0, SPR_STBL, 1, 5, NULL, 0, 0, S_LITTLETUMBLEWEED_ROLL3, 0},
	{"LITTLETUMBLEWEED_ROLL3", 0, SPR_STBL, 2, 5, NULL, 0, 0, S_LITTLETUMBLEWEED_ROLL4, 0},
	{"LITTLETUMBLEWEED_ROLL4", 0, SPR_STBL, 3, 5, NULL, 0, 0, S_LITTLETUMBLEWEED_ROLL5, 0},
	{"LITTLETUMBLEWEED_ROLL5", 0, SPR_STBL, 4, 5, NULL, 0, 0, S_LITTLETUMBLEWEED_ROLL6, 0},
	{"LITTLETUMBLEWEED_ROLL6", 0, SPR_STBL, 5, 5, NULL, 0, 0, S_LITTLETUMBLEWEED_ROLL7, 0},
	{"LITTLETUMBLEWEED_ROLL7", 0, SPR_STBL, 6, 5, NULL, 0, 0, S_LITTLETUMBLEWEED_ROLL8, 0},
	{"LITTLETUMBLEWEED_ROLL8", 0, SPR_STBL, 7, 5, NULL, 0, 0, S_LITTLETUMBLEWEED_ROLL1, 0},

	// Cacti
	{"CACTI1", 0, SPR_CACT, 0, -1, A_ConnectToGround, MT_CACTITINYSEG, 0, S_NULL, 0},
	{"CACTI2", 0, SPR_CACT, 1, -1, A_ConnectToGround, MT_CACTISMALLSEG, 0, S_NULL, 0},
	{"CACTI3", 0, SPR_CACT, 2, -1, A_ConnectToGround, MT_CACTITINYSEG, 0, S_NULL, 0},
	{"CACTI4", 0, SPR_CACT, 3, -1, A_ConnectToGround, MT_CACTISMALLSEG, 0, S_NULL, 0},
	{"CACTI5", 0, SPR_CACT, 4, -1, NULL, 0, 0, S_NULL, 0},
	{"CACTI6", 0, SPR_CACT, 5, -1, NULL, 0, 0, S_NULL, 0},
	{"CACTI7", 0, SPR_CACT, 6, -1, NULL, 0, 0, S_NULL, 0},
	{"CACTI8", 0, SPR_CACT, 7, -1, NULL, 0, 0, S_NULL, 0},
	{"CACTI9", 0, SPR_CACT, 8, -1, NULL, 0, 0, S_NULL, 0},
	{"CACTI10", 0, SPR_CACT, 9, -1, A_ConnectToGround, MT_CACTITINYSEG, 0, S_NULL, 0},
	{"CACTI11", 0, SPR_CACT, 10, -1, A_ConnectToGround, MT_CACTISMALLSEG, 0, S_NULL, 0},
	{"CACTITINYSEG", 0, SPR_CACT, 11, -1, NULL, 0, 0, S_NULL, 0},
	{"CACTISMALLSEG", 0, SPR_CACT, 12, -1, NULL, 0, 0, S_NULL, 0},

	// Warning Signs
	{"ARIDSIGN_CAUTION", 0, SPR_WWSG, FF_PAPERSPRITE, -1, NULL, 0, 0, S_NULL, 0},
	{"ARIDSIGN_CACTI", 0, SPR_WWS2, FF_PAPERSPRITE, -1, NULL, 0, 0, S_NULL, 0},
	{"ARIDSIGN_SHARPTURN", 0, SPR_WWS3, FF_PAPERSPRITE, -1, NULL, 0, 0, S_NULL, 0},

	// Oil lamp
	{"OILLAMP", 0, SPR_OILL, FF_FULLBRIGHT, -1, NULL, 0, 0, S_NULL, 0},
	{"OILLAMPFLARE", 0, SPR_OILF, FF_TRANS90|FF_FULLBRIGHT, -1, NULL, 0, 0, S_NULL, 0},

	// TNT barrel
	{"TNTBARREL_STND1", 0, SPR_BARR, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"TNTBARREL_EXPL1", 0, SPR_BARX, 0, 0, A_RollAngle, 0, 1, S_TNTBARREL_EXPL2, 0},
	{"TNTBARREL_EXPL2", 0, SPR_BARX, 0|FF_FULLBRIGHT, 3, A_SetObjectFlags, MF_NOCLIP|MF_NOGRAVITY|MF_NOBLOCKMAP, 0, S_TNTBARREL_EXPL3, 0},
	{"TNTBARREL_EXPL3", 0, SPR_BARX, 1|FF_FULLBRIGHT, 2, A_TNTExplode, MT_TNTDUST, 0, S_TNTBARREL_EXPL4, 0},
	{"TNTBARREL_EXPL4", 0, SPR_BARX, 1|FF_FULLBRIGHT, 1, NULL, 0, 0, S_TNTBARREL_EXPL5, 0},
	{"TNTBARREL_EXPL5", 0, SPR_BARX, 2|FF_FULLBRIGHT, 3, NULL, 0, 0, S_TNTBARREL_EXPL6, 0},
	{"TNTBARREL_EXPL6", 0, SPR_BARX, 3|FF_FULLBRIGHT, 3, NULL, 0, 0, S_TNTBARREL_EXPL7, 0},
	{"TNTBARREL_EXPL7", 0, SPR_NULL, 0, 35, NULL, 0, 0, S_NULL, 0},
#ifndef ROTSPRITE
	{"TNTBARREL_FLYING", 0, SPR_BARR, 1|FF_ANIMATE, -1, NULL, 7, 2, S_NULL, 0},
#else
	{"TNTBARREL_FLYING", 0, SPR_BARR, 1, 1, A_RollAngle, 14, 0, S_TNTBARREL_FLYING, 0},
#endif

	// TNT proximity shell
	{"PROXIMITY_TNT", 0, SPR_REMT, 0, 10, A_Look, 33554433, 0, S_PROXIMITY_TNT, 0},
	{"PROXIMITY_TNT_TRIGGER1", 0, SPR_REMT, 1|FF_FULLBRIGHT, 1, A_PlayActiveSound, 0, 0, S_PROXIMITY_TNT_TRIGGER2, 0},
	{"PROXIMITY_TNT_TRIGGER2", 0, SPR_REMT, 0, 16, NULL, 0, 0, S_PROXIMITY_TNT_TRIGGER3, 0},
	{"PROXIMITY_TNT_TRIGGER3", 0, SPR_REMT, 1|FF_FULLBRIGHT, 1, A_PlayActiveSound, 0, 0, S_PROXIMITY_TNT_TRIGGER4, 0},
	{"PROXIMITY_TNT_TRIGGER4", 0, SPR_REMT, 0, 16, NULL, 0, 0, S_PROXIMITY_TNT_TRIGGER5, 0},
	{"PROXIMITY_TNT_TRIGGER5", 0, SPR_REMT, 1|FF_FULLBRIGHT, 1, A_PlayActiveSound, 0, 0, S_PROXIMITY_TNT_TRIGGER6, 0},
	{"PROXIMITY_TNT_TRIGGER6", 0, SPR_REMT, 0, 4, NULL, 0, 0, S_PROXIMITY_TNT_TRIGGER7, 0},
	{"PROXIMITY_TNT_TRIGGER7", 0, SPR_REMT, 1|FF_FULLBRIGHT, 1, A_PlayActiveSound, 0, 0, S_PROXIMITY_TNT_TRIGGER8, 0},
	{"PROXIMITY_TNT_TRIGGER8", 0, SPR_REMT, 0, 4, NULL, 0, 0, S_PROXIMITY_TNT_TRIGGER9, 0},
	{"PROXIMITY_TNT_TRIGGER9", 0, SPR_REMT, 1|FF_FULLBRIGHT, 1, A_PlayActiveSound, 0, 0, S_PROXIMITY_TNT_TRIGGER10, 0},
	{"PROXIMITY_TNT_TRIGGER10", 0, SPR_REMT, 0, 4, NULL, 0, 0, S_PROXIMITY_TNT_TRIGGER11, 0},
	{"PROXIMITY_TNT_TRIGGER11", 0, SPR_REMT, 1|FF_FULLBRIGHT, 1, A_PlayActiveSound, 0, 0, S_PROXIMITY_TNT_TRIGGER12, 0},
	{"PROXIMITY_TNT_TRIGGER12", 0, SPR_REMT, 0, 4, NULL, 0, 0, S_PROXIMITY_TNT_TRIGGER13, 0},
	{"PROXIMITY_TNT_TRIGGER13", 0, SPR_REMT, 1|FF_FULLBRIGHT, 1, A_PlayActiveSound, 0, 0, S_PROXIMITY_TNT_TRIGGER14, 0},
	{"PROXIMITY_TNT_TRIGGER14", 0, SPR_REMT, 0, 2, NULL, 0, 0, S_PROXIMITY_TNT_TRIGGER15, 0},
	{"PROXIMITY_TNT_TRIGGER15", 0, SPR_REMT, 1|FF_FULLBRIGHT, 1, A_PlayActiveSound, 0, 0, S_PROXIMITY_TNT_TRIGGER16, 0},
	{"PROXIMITY_TNT_TRIGGER16", 0, SPR_REMT, 0, 2, NULL, 0, 0, S_PROXIMITY_TNT_TRIGGER17, 0},
	{"PROXIMITY_TNT_TRIGGER17", 0, SPR_REMT, 1|FF_FULLBRIGHT, 1, A_PlayActiveSound, 0, 0, S_PROXIMITY_TNT_TRIGGER18, 0},
	{"PROXIMITY_TNT_TRIGGER18", 0, SPR_REMT, 0, 2, NULL, 0, 0, S_PROXIMITY_TNT_TRIGGER19, 0},
	{"PROXIMITY_TNT_TRIGGER19", 0, SPR_REMT, 1|FF_FULLBRIGHT, 1, A_PlayActiveSound, 0, 0, S_PROXIMITY_TNT_TRIGGER20, 0},
	{"PROXIMITY_TNT_TRIGGER20", 0, SPR_REMT, 0, 2, NULL, 0, 0, S_PROXIMITY_TNT_TRIGGER21, 0},
	{"PROXIMITY_TNT_TRIGGER21", 0, SPR_REMT, 1|FF_FULLBRIGHT, 1, A_PlayActiveSound, 0, 0, S_PROXIMITY_TNT_TRIGGER22, 0},
	{"PROXIMITY_TNT_TRIGGER22", 0, SPR_REMT, 0, 2, NULL, 0, 0, S_PROXIMITY_TNT_TRIGGER23, 0},
	{"PROXIMITY_TNT_TRIGGER23", 0, SPR_REMT, 1|FF_FULLBRIGHT, 1, A_PlayActiveSound, 0, 0, S_TNTBARREL_EXPL1, 0},

	// Dust devil
	{"DUSTDEVIL", 0, SPR_NULL, 0, 1, A_DustDevilThink, 0, 0, S_DUSTDEVIL, 0},
	{"DUSTLAYER1", 0, SPR_TAZD, 1|FF_PAPERSPRITE|FF_TRANS70, 2 * TICRATE, NULL, 0, 0, S_DUSTLAYER2, 0},
	{"DUSTLAYER2", 0, SPR_TAZD, 1|FF_PAPERSPRITE|FF_TRANS70, 5, NULL, 0, 0, S_DUSTLAYER3, 0},
	{"DUSTLAYER3", 0, SPR_TAZD, 1|FF_PAPERSPRITE|FF_TRANS80, 5, NULL, 0, 0, S_DUSTLAYER4, 0},
	{"DUSTLAYER4", 0, SPR_TAZD, 1|FF_PAPERSPRITE|FF_TRANS80, 5, NULL, 0, 0, S_DUSTLAYER5, 0},
	{"DUSTLAYER5", 0, SPR_TAZD, 1|FF_PAPERSPRITE|FF_TRANS90, 5, NULL, 0, 0, S_NULL, 0},
	{"ARIDDUST1", 0, SPR_ADST, 0|FF_ANIMATE, 24, NULL, 3, 8, S_NULL, 0},
	{"ARIDDUST2", 0, SPR_ADST, 3|FF_ANIMATE, 24, NULL, 3, 8, S_NULL, 0},
	{"ARIDDUST3", 0, SPR_ADST, 6|FF_ANIMATE, 24, NULL, 3, 8, S_NULL, 0},

	// Minecart
	{"MINECART_IDLE", 0, SPR_NULL, 0,                            1, NULL,                 0, 0, S_MINECART_IDLE, 0},
	{"MINECART_DTH1", 0, SPR_NULL, 0,                            0, A_KillSegments,       0, 0, S_TNTBARREL_EXPL4, 0},
	{"MINECARTEND", 0, SPR_MCRT, 8|FF_PAPERSPRITE,            -1, NULL,                 0, 0, S_NULL, 0},
	{"MINECARTSEG_FRONT", 0, SPR_MCRT, 0|FF_PAPERSPRITE,            -1, NULL,                 0, 0, S_NULL, 0},
	{"MINECARTSEG_BACK", 0, SPR_MCRT, 1|FF_PAPERSPRITE,            -1, NULL,                 0, 0, S_NULL, 0},
	{"MINECARTSEG_LEFT", 0, SPR_MCRT, 2|FF_PAPERSPRITE|FF_ANIMATE, -1, NULL,                 2, 3, S_NULL, 0},
	{"MINECARTSEG_RIGHT", 0, SPR_MCRT, 5|FF_PAPERSPRITE|FF_ANIMATE, -1, NULL,                 2, 3, S_NULL, 0},
	{"MINECARTSIDEMARK1", 0, SPR_LCKN, 2|FF_FULLBRIGHT,              2, NULL,                 0, 0, S_NULL, 0},
	{"MINECARTSIDEMARK2", 0, SPR_LCKN, 0|FF_FULLBRIGHT,              2, NULL,                 0, 0, S_NULL, 0},
	{"MINECARTSPARK", 0, SPR_MCSP, FF_FULLBRIGHT,                1, A_MinecartSparkThink, 0, 0, S_MINECARTSPARK, 0},

	// Saloon door
	{"SALOONDOOR", 0, SPR_SALD, 0|FF_PAPERSPRITE, -1, NULL, 0, 0, S_NULL, 0},
	{"SALOONDOORCENTER", 0, SPR_NULL, 0, -1, A_SaloonDoorSpawn, MT_SALOONDOOR, 48, S_NULL, 0},

	// Train cameo
	{"TRAINCAMEOSPAWNER_1", 0, SPR_NULL, 0, -1, NULL, 0, 0, S_TRAINCAMEOSPAWNER_2, 0},
	{"TRAINCAMEOSPAWNER_2", 0, SPR_NULL, 0, 14, A_TrainCameo, 20, 18, S_TRAINCAMEOSPAWNER_3, 0},
	{"TRAINCAMEOSPAWNER_3", 0, SPR_NULL, 0, 1, A_Repeat, 1, 0, S_TRAINCAMEOSPAWNER_4, 0},
	{"TRAINCAMEOSPAWNER_4", 0, SPR_NULL, 0, 18, A_TrainCameo2, 20, 44, S_TRAINCAMEOSPAWNER_5, 0},
	{"TRAINCAMEOSPAWNER_5", 0, SPR_NULL, 0, 1, A_Repeat, 5, S_TRAINCAMEOSPAWNER_4, S_NULL, 0},
	{"TRAINPUFFMAKER", 0, SPR_NULL, 0, 2, A_SmokeTrailer, MT_SMOKE, 0, S_TRAINPUFFMAKER, 0},

	{"TRAINDUST", 0, SPR_ADST, FF_TRANS50, -1, NULL, 0, 0, S_NULL, 0},
	{"TRAINSTEAM", 0, SPR_STEA, FF_TRANS50, -1, NULL, 0, 0, S_NULL, 0},

	// Flame jet
	{"FLAMEJETSTND", 0, SPR_NULL, 0, 2*TICRATE, NULL,             0, 0, S_FLAMEJETSTART, 0},
	{"FLAMEJETSTART", 0, SPR_NULL, 0, 3*TICRATE, A_ToggleFlameJet, 0, 0,  S_FLAMEJETSTOP, 0},
	{"FLAMEJETSTOP", 0, SPR_NULL, 0,         1, A_ToggleFlameJet, 0, 0,  S_FLAMEJETSTND, 0},
	{"FLAMEJETFLAME1", 0, SPR_FLME, FF_FULLBRIGHT  ,  4, NULL, 0, 0, S_FLAMEJETFLAME2, 0},
	{"FLAMEJETFLAME2", 0, SPR_FLME, FF_FULLBRIGHT|1,  5, NULL, 0, 0, S_FLAMEJETFLAME3, 0},
	{"FLAMEJETFLAME3", 0, SPR_FLME, FF_FULLBRIGHT|2, 11, NULL, 0, 0,           S_NULL, 0},
	{"FLAMEJETFLAME4", 0, SPR_FLME, FF_FULLBRIGHT|3,  4, NULL, 0, 0, S_FLAMEJETFLAME5, 0},
	{"FLAMEJETFLAME5", 0, SPR_FLME, FF_FULLBRIGHT|4,  5, NULL, 0, 0, S_FLAMEJETFLAME6, 0},
	{"FLAMEJETFLAME6", 0, SPR_FLME, FF_FULLBRIGHT|5, 11, NULL, 0, 0,           S_NULL, 0},
	{"FLAMEJETFLAME7", 0, SPR_FLME, FF_FULLBRIGHT|6,  4, NULL, 0, 0, S_FLAMEJETFLAME8, 0},
	{"FLAMEJETFLAME8", 0, SPR_FLME, FF_FULLBRIGHT|7,  5, NULL, 0, 0, S_FLAMEJETFLAME9, 0},
	{"FLAMEJETFLAME9", 0, SPR_FLME, FF_FULLBRIGHT|8, 11, NULL, 0, 0,           S_NULL, 0},

	// Spinning flame jets
	// A: Counter-clockwise
	{"FJSPINAXISA1", 0, SPR_NULL, 0, 1,            A_TrapShot, MT_FLAMEJETFLAMEB, -(16<<16)|(1<<15)|64, S_FJSPINAXISA2, 0},
	{"FJSPINAXISA2", 0, SPR_NULL, 0, 2, A_ChangeAngleRelative,                 6,         6, S_FJSPINAXISA1, 0},

	// B: Clockwise
	{"FJSPINAXISB1", 0, SPR_NULL, 0, 1,            A_TrapShot, MT_FLAMEJETFLAMEB, -(16<<16)|(1<<15)|64, S_FJSPINAXISB2, 0},
	{"FJSPINAXISB2", 0, SPR_NULL, 0, 2, A_ChangeAngleRelative,                -6,        -6, S_FJSPINAXISB1, 0},

	// Blade's flame
	{"FLAMEJETFLAMEB1", 0, SPR_DFLM, FF_FULLBRIGHT|FF_TRANS40, 1, A_MoveRelative, 0, 5, S_FLAMEJETFLAMEB2, 0},
	{"FLAMEJETFLAMEB2", 0, SPR_DFLM, FF_FULLBRIGHT|FF_TRANS40, 1, A_MoveRelative, 0, 7, S_FLAMEJETFLAMEB3, 0},
	{"FLAMEJETFLAMEB3", 0, SPR_DFLM, FF_FULLBRIGHT|FF_TRANS40|FF_ANIMATE, (12*7), NULL, 7, 12, S_NULL, 0},

	// Lavafall
	{"LAVAFALL_DORMANT", 0, SPR_LFAL, 5, 1, NULL, 0, 0, S_LAVAFALL_DORMANT, 0},
	{"LAVAFALL_TELL", 0, SPR_LFAL, 6|FF_ANIMATE, 4, A_LavafallRocks, 1, 2, S_LAVAFALL_TELL, 0},
	{"LAVAFALL_SHOOT", 0, SPR_LFAL, 9|FF_FULLBRIGHT|FF_ANIMATE, 2, A_LavafallLava, 1, 1, S_LAVAFALL_SHOOT, 0},
	{"LAVAFALL_LAVA1", 0, SPR_LFAL, FF_FULLBRIGHT, 1, A_FallingLavaCheck, 0, 0, S_LAVAFALL_LAVA2, 0},
	{"LAVAFALL_LAVA2", 0, SPR_LFAL, FF_FULLBRIGHT, 1, A_FallingLavaCheck, 0, 0, S_LAVAFALL_LAVA1, 0},
	{"LAVAFALL_LAVA3", 0, SPR_LFAL, 2|FF_FULLBRIGHT|FF_ANIMATE, 9, NULL, 2, 3, S_NULL, 0},
	{"LAVAFALLROCK", 0, SPR_LFAL, 11|FF_ANIMATE|FF_RANDOMANIM, 12, NULL, 3, 3, S_LAVAFALLROCK, 0},

	// Rollout Rock
	{"ROLLOUTSPAWN", 0, SPR_NULL, 0, 1, A_RolloutSpawn, 256*FRACUNIT, MT_ROLLOUTROCK, S_ROLLOUTSPAWN, 0},
	{"ROLLOUTROCK", 0, SPR_PUMI, 0, 1, A_RolloutRock,    63*FRACUNIT/64,  7*FRACUNIT/10,  S_ROLLOUTROCK, 0},

	// RVZ scenery
	{"BIGFERNLEAF", 0, SPR_JPLA, FF_PAPERSPRITE, -1, NULL, 0, 0, S_NULL, 0},
	{"BIGFERN1", 0, SPR_JPLA, 1, 1, NULL, 0, 0, S_BIGFERN2, 0},
	{"BIGFERN2", 0, SPR_JPLA, 1, -1, NULL, 0, 0, S_NULL, 0},
	{"JUNGLEPALM", 0, SPR_JPLA, 2, -1, NULL, 0, 0, S_NULL, 0},
	{"TORCHFLOWER", 0, SPR_TFLO, FF_FULLBRIGHT, -1, NULL, 0, 0, S_TORCHFLOWER, 0},
	{"WALLVINE_LONG", 0, SPR_WVIN, FF_PAPERSPRITE, -1, NULL, 0, 0, S_NULL, 0},
	{"WALLVINE_SHORT", 0, SPR_WVIN, 1|FF_PAPERSPRITE, -1, NULL, 0, 0, S_NULL, 0},

	// Glaregoyles
	{"GLAREGOYLE", 0, SPR_BGAR,            0, 22, NULL,       0, 0, S_GLAREGOYLE_CHARGE, 0},
	{"GLAREGOYLE_CHARGE", 0, SPR_BGAR,            2,  6, NULL,       0, 0, S_GLAREGOYLE_BLINK, 0},
	{"GLAREGOYLE_BLINK", 0, SPR_BGAR, FF_ANIMATE|1, 18, NULL,       1, 3, S_GLAREGOYLE_HOLD, 0},
	{"GLAREGOYLE_HOLD", 0, SPR_BGAR,            1,  9, NULL,       0, 0, S_GLAREGOYLE_FIRE, 0},
	{"GLAREGOYLE_FIRE", 0, SPR_BGAR,            1,  1, A_TrapShot, (16<<16)+MT_DEMONFIRE, (30<<16), S_GLAREGOYLE_LOOP, 0},
	{"GLAREGOYLE_LOOP", 0, SPR_BGAR,            1,  0, A_Repeat,   3, S_GLAREGOYLE_FIRE, S_GLAREGOYLE_COOLDOWN, 0},
	{"GLAREGOYLE_COOLDOWN", 0, SPR_BGAR, FF_ANIMATE|1, 15, NULL,       1, 9, S_GLAREGOYLE, 0},

	{"GLAREGOYLEUP", 0, SPR_BGAR,            0, 22, NULL,       0, 0, S_GLAREGOYLEUP_CHARGE, 0},
	{"GLAREGOYLEUP_CHARGE", 0, SPR_BGAR,            2,  6, NULL,       0, 0, S_GLAREGOYLEUP_BLINK, 0},
	{"GLAREGOYLEUP_BLINK", 0, SPR_BGAR, FF_ANIMATE|1, 18, NULL,       1, 3, S_GLAREGOYLEUP_HOLD, 0},
	{"GLAREGOYLEUP_HOLD", 0, SPR_BGAR,            1,  9, NULL,       0, 0, S_GLAREGOYLEUP_FIRE, 0},
	{"GLAREGOYLEUP_FIRE", 0, SPR_BGAR,            1,  1, A_TrapShot, (16<<16)+MT_DEMONFIRE, (30<<16)+45, S_GLAREGOYLEUP_LOOP, 0},
	{"GLAREGOYLEUP_LOOP", 0, SPR_BGAR,            1,  0, A_Repeat,   3, S_GLAREGOYLEUP_FIRE, S_GLAREGOYLEUP_COOLDOWN, 0},
	{"GLAREGOYLEUP_COOLDOWN", 0, SPR_BGAR, FF_ANIMATE|1, 15, NULL,       1, 9, S_GLAREGOYLEUP, 0},

	{"GLAREGOYLEDOWN", 0, SPR_BGAR,            0, 22, NULL,       0, 0, S_GLAREGOYLEDOWN_CHARGE, 0},
	{"GLAREGOYLEDOWN_CHARGE", 0, SPR_BGAR,            2,  6, NULL,       0, 0, S_GLAREGOYLEDOWN_BLINK, 0},
	{"GLAREGOYLEDOWN_BLINK", 0, SPR_BGAR, FF_ANIMATE|1, 18, NULL,       1, 3, S_GLAREGOYLEDOWN_HOLD, 0},
	{"GLAREGOYLEDOWN_HOLD", 0, SPR_BGAR,            1,  9, NULL,       0, 0, S_GLAREGOYLEDOWN_FIRE, 0},
	{"GLAREGOYLEDOWN_FIRE", 0, SPR_BGAR,            1,  1, A_TrapShot, (16<<16)+MT_DEMONFIRE, (30<<16)+315, S_GLAREGOYLEDOWN_LOOP, 0},
	{"GLAREGOYLEDOWN_LOOP", 0, SPR_BGAR,            1,  0, A_Repeat,   3, S_GLAREGOYLEDOWN_FIRE, S_GLAREGOYLEDOWN_COOLDOWN, 0},
	{"GLAREGOYLEDOWN_COOLDOWN", 0, SPR_BGAR, FF_ANIMATE|1, 15, NULL,       1, 9, S_GLAREGOYLEDOWN, 0},

	{"GLAREGOYLELONG", 0, SPR_BGAR,            0, 90, NULL,       0, 0, S_GLAREGOYLELONG_CHARGE, 0},
	{"GLAREGOYLELONG_CHARGE", 0, SPR_BGAR,            2,  6, NULL,       0, 0, S_GLAREGOYLELONG_BLINK, 0},
	{"GLAREGOYLELONG_BLINK", 0, SPR_BGAR, FF_ANIMATE|1, 18, NULL,       1, 3, S_GLAREGOYLELONG_HOLD, 0},
	{"GLAREGOYLELONG_HOLD", 0, SPR_BGAR,            1,  9, NULL,       0, 0, S_GLAREGOYLELONG_FIRE, 0},
	{"GLAREGOYLELONG_FIRE", 0, SPR_BGAR,            1,  1, A_TrapShot, (16<<16)+MT_DEMONFIRE, (30<<16), S_GLAREGOYLELONG_LOOP, 0},
	{"GLAREGOYLELONG_LOOP", 0, SPR_BGAR,            1,  0, A_Repeat,   5, S_GLAREGOYLELONG_FIRE, S_GLAREGOYLELONG_COOLDOWN, 0},
	{"GLAREGOYLELONG_COOLDOWN", 0, SPR_BGAR, FF_ANIMATE|1, 15, NULL,       1, 9, S_GLAREGOYLELONG, 0},

	// Target/Red Crystal
	{"TARGET_IDLE", 0, SPR_RCRY,               0, -1, NULL,                  0, 0, S_TARGET_IDLE, 0},
	{"TARGET_HIT1", 0, SPR_RCRY, FF_FULLBRIGHT|1,  0, A_PlaySound,           sfx_ding, 1, S_TARGET_HIT2, 0},
	{"TARGET_HIT2", 0, SPR_RCRY, FF_FULLBRIGHT|1, 45, A_SetObjectFlags,      MF_PUSHABLE, 2, S_TARGET_RESPAWN, 0},
	{"TARGET_RESPAWN", 0, SPR_RCRY,               1,  0, A_SpawnObjectRelative, 0, MT_TARGET, S_NULL, 0},
	{"TARGET_ALLDONE", 0, SPR_RCRY, FF_FULLBRIGHT|1, -1, A_SetObjectFlags,      MF_PUSHABLE, 1, S_TARGET_ALLDONE, 0},

	// Green flame
	{"GREENFLAME", 0, SPR_CFLM, FF_FULLBRIGHT|FF_ANIMATE|FF_RANDOMANIM, -1, NULL, 7, 3, S_GREENFLAME, 0},

	// ATZ Blue Gargoyle
	{"BLUEGARGOYLE", 0, SPR_BGAR, 3, -1, NULL, 0, 0, S_NULL, 0},

	// Stalagmites
	{"STG0", 0, SPR_STLG, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"STG1", 0, SPR_STLG, 1, -1, NULL, 0, 0, S_NULL, 0},
	{"STG2", 0, SPR_STLG, 2, -1, NULL, 0, 0, S_NULL, 0},
	{"STG3", 0, SPR_STLG, 3, -1, NULL, 0, 0, S_NULL, 0},
	{"STG4", 0, SPR_STLG, 4, -1, NULL, 0, 0, S_NULL, 0},
	{"STG5", 0, SPR_STLG, 5, -1, NULL, 0, 0, S_NULL, 0},
	{"STG6", 0, SPR_STLG, 6, -1, NULL, 0, 0, S_NULL, 0},
	{"STG7", 0, SPR_STLG, 7, -1, NULL, 0, 0, S_NULL, 0},
	{"STG8", 0, SPR_STLG, 8, -1, NULL, 0, 0, S_NULL, 0},
	{"STG9", 0, SPR_STLG, 9, -1, NULL, 0, 0, S_NULL, 0},

	// Xmas-specific stuff
	{"XMASPOLE", 0, SPR_XMS1, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"CANDYCANE", 0, SPR_XMS2, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"SNOWMAN", 0, SPR_XMS3, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"SNOWMANHAT", 0, SPR_XMS3, 1, -1, NULL, 0, 0, S_NULL, 0},
	{"LAMPPOST1", 0, SPR_XMS4, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"LAMPPOST2", 0, SPR_XMS4, 1, -1, NULL, 0, 0, S_NULL, 0},
	{"HANGSTAR", 0, SPR_XMS5, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"MISTLETOE", 0, SPR_XMS6, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"SSZTREE", 0, SPR_SNTT, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"SSZTREE_BRANCH", 0, SPR_SNTT, 1|FF_PAPERSPRITE, -1, NULL, 0, 0, S_NULL, 0},
	{"SSZTREE2", 0, SPR_SSTT, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"SSZTREE2_BRANCH", 0, SPR_SSTT, 1|FF_PAPERSPRITE, -1, NULL, 0, 0, S_NULL, 0},
	// Xmas GFZ bushes
	{"XMASBLUEBERRYBUSH", 0, SPR_BUS3, 1, -1, NULL, 0, 0, S_NULL, 0},
	{"XMASBERRYBUSH", 0, SPR_BUS1, 1, -1, NULL, 0, 0, S_NULL, 0},
	{"XMASBUSH", 0, SPR_BUS2, 1, -1, NULL, 0, 0, S_NULL, 0},
	// FHZ
	{"FHZICE1", 0, SPR_FHZI, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"FHZICE2", 0, SPR_FHZI, 1, -1, NULL, 0, 0, S_NULL, 0},
	// Amy FHZ cameo
	{"ROSY_IDLE", 0, SPR_PLAY, SPR2_CNT1|FF_ANIMATE,      -1, NULL, 0, 0, S_NULL, 0},
	{"ROSY_JUMP", 0, SPR_PLAY,            SPR2_MSC0,      -1, NULL, 0, 0, S_NULL, 0},
	{"ROSY_FALL", 0, SPR_PLAY,            SPR2_MSC1,      -1, NULL, 0, 0, S_NULL, 0},
	{"ROSY_WALK", 0, SPR_PLAY,            SPR2_WALK,      -1, NULL, 7, 0, S_NULL, 0},
	{"ROSY_HUG", 0, SPR_PLAY,            SPR2_MSC2,      -1, NULL, 0, 0, S_NULL, 0},
	{"ROSY_PAIN", 0, SPR_PLAY,            SPR2_PAIN,      -1, NULL, 0, 0, S_NULL, 0},
	{"ROSY_STND", 0, SPR_PLAY, SPR2_WAIT|FF_ANIMATE,      -1, NULL, 0, 5, S_NULL, 0},
	{"ROSY_UNHAPPY", 0, SPR_PLAY, SPR2_MSC3|FF_ANIMATE, TICRATE, NULL, 0, 4, S_ROSY_WALK, 0},

	// Halloween Scenery
	// Pumpkins
	{"JACKO1", 0, SPR_PUMK,  0, -1, NULL, 0, 0, S_NULL, 0},
	{"JACKO1OVERLAY_1", 0, SPR_PUMK,  3|FF_FULLBRIGHT, 5, NULL, 0, 0, S_JACKO1OVERLAY_2, 0},
	{"JACKO1OVERLAY_2", 0, SPR_PUMK,  4|FF_FULLBRIGHT, 5, NULL, 0, 0, S_JACKO1OVERLAY_3, 0},
	{"JACKO1OVERLAY_3", 0, SPR_PUMK,  5|FF_FULLBRIGHT, 5, NULL, 0, 0, S_JACKO1OVERLAY_4, 0},
	{"JACKO1OVERLAY_4", 0, SPR_PUMK,  4|FF_FULLBRIGHT, 5, NULL, 0, 0, S_JACKO1OVERLAY_1, 0},
	{"JACKO2", 0, SPR_PUMK,  1, -1, NULL, 0, 0, S_NULL, 0},
	{"JACKO2OVERLAY_1", 0, SPR_PUMK,  6|FF_FULLBRIGHT, 5, NULL, 0, 0, S_JACKO2OVERLAY_2, 0},
	{"JACKO2OVERLAY_2", 0, SPR_PUMK,  7|FF_FULLBRIGHT, 5, NULL, 0, 0, S_JACKO2OVERLAY_3, 0},
	{"JACKO2OVERLAY_3", 0, SPR_PUMK,  8|FF_FULLBRIGHT, 5, NULL, 0, 0, S_JACKO2OVERLAY_4, 0},
	{"JACKO2OVERLAY_4", 0, SPR_PUMK,  7|FF_FULLBRIGHT, 5, NULL, 0, 0, S_JACKO2OVERLAY_1, 0},
	{"JACKO3", 0, SPR_PUMK,  2, -1, NULL, 0, 0, S_NULL, 0},
	{"JACKO3OVERLAY_1", 0, SPR_PUMK,  9|FF_FULLBRIGHT, 5, NULL, 0, 0, S_JACKO3OVERLAY_2, 0},
	{"JACKO3OVERLAY_2", 0, SPR_PUMK, 10|FF_FULLBRIGHT, 5, NULL, 0, 0, S_JACKO3OVERLAY_3, 0},
	{"JACKO3OVERLAY_3", 0, SPR_PUMK, 11|FF_FULLBRIGHT, 5, NULL, 0, 0, S_JACKO3OVERLAY_4, 0},
	{"JACKO3OVERLAY_4", 0, SPR_PUMK, 10|FF_FULLBRIGHT, 5, NULL, 0, 0, S_JACKO3OVERLAY_1, 0},
	// Dr Seuss Trees
	{"HHZTREE_TOP", 0, SPR_HHPL, 2, -1, A_ConnectToGround, MT_HHZTREE_PART, 0, S_NULL, 0},
	{"HHZTREE_TRUNK", 0, SPR_HHPL, 1, -1, NULL, 0, 0, S_NULL, 0},
	{"HHZTREE_LEAF", 0, SPR_HHPL, FF_PAPERSPRITE, -1, NULL, 0, 0, S_NULL, 0},
	// Mushroom
	{"HHZSHROOM_1", 0, SPR_SHRM, 4,  3, NULL, 0, 0, S_HHZSHROOM_2, 0},
	{"HHZSHROOM_2", 0, SPR_SHRM, 3,  3, NULL, 0, 0, S_HHZSHROOM_3, 0},
	{"HHZSHROOM_3", 0, SPR_SHRM, 2,  2, NULL, 0, 0, S_HHZSHROOM_4, 0},
	{"HHZSHROOM_4", 0, SPR_SHRM, 1,  1, NULL, 0, 0, S_HHZSHROOM_5, 0},
	{"HHZSHROOM_5", 0, SPR_SHRM, 0,  1, NULL, 0, 0, S_HHZSHROOM_6, 0},
	{"HHZSHROOM_6", 0, SPR_SHRM, 1,  4, NULL, 0, 0, S_HHZSHROOM_7, 0},
	{"HHZSHROOM_7", 0, SPR_SHRM, 2,  2, NULL, 0, 0, S_HHZSHROOM_8, 0},
	{"HHZSHROOM_8", 0, SPR_SHRM, 3,  3, NULL, 0, 0, S_HHZSHROOM_9, 0},
	{"HHZSHROOM_9", 0, SPR_SHRM, 4,  3, NULL, 0, 0, S_HHZSHROOM_10, 0},
	{"HHZSHROOM_10", 0, SPR_SHRM, 3,  3, NULL, 0, 0, S_HHZSHROOM_11, 0},
	{"HHZSHROOM_11", 0, SPR_SHRM, 5,  2, NULL, 0, 0, S_HHZSHROOM_12, 0},
	{"HHZSHROOM_12", 0, SPR_SHRM, 6,  1, NULL, 0, 0, S_HHZSHROOM_13, 0},
	{"HHZSHROOM_13", 0, SPR_SHRM, 7,  1, NULL, 0, 0, S_HHZSHROOM_14, 0},
	{"HHZSHROOM_14", 0, SPR_SHRM, 6,  4, NULL, 0, 0, S_HHZSHROOM_15, 0},
	{"HHZSHROOM_15", 0, SPR_SHRM, 5,  2, NULL, 0, 0, S_HHZSHROOM_16, 0},
	{"HHZSHROOM_16", 0, SPR_SHRM, 3,  3, NULL, 0, 0, S_HHZSHROOM_1, 0},
	// Misc
	{"HHZGRASS", 0, SPR_HHZM, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"HHZTENT1", 0, SPR_HHZM, 1, -1, NULL, 0, 0, S_NULL, 0},
	{"HHZTENT2", 0, SPR_HHZM, 2, -1, NULL, 0, 0, S_NULL, 0},
	{"HHZSTALAGMITE_TALL", 0, SPR_HHZM, 4, -1, NULL, 0, 0, S_NULL, 0},
	{"HHZSTALAGMITE_SHORT", 0, SPR_HHZM, 5, -1, NULL, 0, 0, S_NULL, 0},

	// Loads of Botanic Serenity bullshit
	{"BSZTALLFLOWER_RED", 0, SPR_BSZ1, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"BSZTALLFLOWER_PURPLE", 0, SPR_BSZ1, 1, -1, NULL, 0, 0, S_NULL, 0},
	{"BSZTALLFLOWER_BLUE", 0, SPR_BSZ1, 2, -1, NULL, 0, 0, S_NULL, 0},
	{"BSZTALLFLOWER_CYAN", 0, SPR_BSZ1, 3, -1, NULL, 0, 0, S_NULL, 0},
	{"BSZTALLFLOWER_YELLOW", 0, SPR_BSZ1, 4, -1, NULL, 0, 0, S_NULL, 0},
	{"BSZTALLFLOWER_ORANGE", 0, SPR_BSZ1, 5, -1, NULL, 0, 0, S_NULL, 0},
	{"BSZFLOWER_RED", 0, SPR_BSZ2, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"BSZFLOWER_PURPLE", 0, SPR_BSZ2, 1, -1, NULL, 0, 0, S_NULL, 0},
	{"BSZFLOWER_BLUE", 0, SPR_BSZ2, 2, -1, NULL, 0, 0, S_NULL, 0},
	{"BSZFLOWER_CYAN", 0, SPR_BSZ2, 3, -1, NULL, 0, 0, S_NULL, 0},
	{"BSZFLOWER_YELLOW", 0, SPR_BSZ2, 4, -1, NULL, 0, 0, S_NULL, 0},
	{"BSZFLOWER_ORANGE", 0, SPR_BSZ2, 5, -1, NULL, 0, 0, S_NULL, 0},
	{"BSZSHORTFLOWER_RED", 0, SPR_BSZ3, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"BSZSHORTFLOWER_PURPLE", 0, SPR_BSZ3, 1, -1, NULL, 0, 0, S_NULL, 0},
	{"BSZSHORTFLOWER_BLUE", 0, SPR_BSZ3, 2, -1, NULL, 0, 0, S_NULL, 0},
	{"BSZSHORTFLOWER_CYAN", 0, SPR_BSZ3, 3, -1, NULL, 0, 0, S_NULL, 0},
	{"BSZSHORTFLOWER_YELLOW", 0, SPR_BSZ3, 4, -1, NULL, 0, 0, S_NULL, 0},
	{"BSZSHORTFLOWER_ORANGE", 0, SPR_BSZ3, 5, -1, NULL, 0, 0, S_NULL, 0},
	{"BSZTULIP_RED", 0, SPR_BST1, FF_ANIMATE, -1, NULL, 11, 4, S_NULL, 0},
	{"BSZTULIP_PURPLE", 0, SPR_BST2, FF_ANIMATE, -1, NULL, 11, 4, S_NULL, 0},
	{"BSZTULIP_BLUE", 0, SPR_BST3, FF_ANIMATE, -1, NULL, 11, 4, S_NULL, 0},
	{"BSZTULIP_CYAN", 0, SPR_BST4, FF_ANIMATE, -1, NULL, 11, 4, S_NULL, 0},
	{"BSZTULIP_YELLOW", 0, SPR_BST5, FF_ANIMATE, -1, NULL, 11, 4, S_NULL, 0},
	{"BSZTULIP_ORANGE", 0, SPR_BST6, FF_ANIMATE, -1, NULL, 11, 4, S_NULL, 0},
	{"BSZCLUSTER_RED", 0, SPR_BSZ5, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"BSZCLUSTER_PURPLE", 0, SPR_BSZ5, 1, -1, NULL, 0, 0, S_NULL, 0},
	{"BSZCLUSTER_BLUE", 0, SPR_BSZ5, 2, -1, NULL, 0, 0, S_NULL, 0},
	{"BSZCLUSTER_CYAN", 0, SPR_BSZ5, 3, -1, NULL, 0, 0, S_NULL, 0},
	{"BSZCLUSTER_YELLOW", 0, SPR_BSZ5, 4, -1, NULL, 0, 0, S_NULL, 0},
	{"BSZCLUSTER_ORANGE", 0, SPR_BSZ5, 5, -1, NULL, 0, 0, S_NULL, 0},
	{"BSZBUSH_RED", 0, SPR_BSZ6, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"BSZBUSH_PURPLE", 0, SPR_BSZ6, 1, -1, NULL, 0, 0, S_NULL, 0},
	{"BSZBUSH_BLUE", 0, SPR_BSZ6, 2, -1, NULL, 0, 0, S_NULL, 0},
	{"BSZBUSH_CYAN", 0, SPR_BSZ6, 3, -1, NULL, 0, 0, S_NULL, 0},
	{"BSZBUSH_YELLOW", 0, SPR_BSZ6, 4, -1, NULL, 0, 0, S_NULL, 0},
	{"BSZBUSH_ORANGE", 0, SPR_BSZ6, 5, -1, NULL, 0, 0, S_NULL, 0},
	{"BSZVINE_RED", 0, SPR_BSZ7, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"BSZVINE_PURPLE", 0, SPR_BSZ7, 1, -1, NULL, 0, 0, S_NULL, 0},
	{"BSZVINE_BLUE", 0, SPR_BSZ7, 2, -1, NULL, 0, 0, S_NULL, 0},
	{"BSZVINE_CYAN", 0, SPR_BSZ7, 3, -1, NULL, 0, 0, S_NULL, 0},
	{"BSZVINE_YELLOW", 0, SPR_BSZ7, 4, -1, NULL, 0, 0, S_NULL, 0},
	{"BSZVINE_ORANGE", 0, SPR_BSZ7, 5, -1, NULL, 0, 0, S_NULL, 0},
	{"BSZSHRUB", 0, SPR_BSZ8, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"BSZCLOVER", 0, SPR_BSZ8, 1, -1, NULL, 0, 0, S_NULL, 0},
	{"BIG_PALMTREE_TRUNK", 0, SPR_BSZ8, 2, -1, NULL, 0, 0, S_NULL, 0},
	{"BIG_PALMTREE_TOP", 0, SPR_BSZ8, 3, -1, A_ConnectToGround, MT_BIG_PALMTREE_TRUNK, 0, S_NULL, 0},
	{"PALMTREE_TRUNK", 0, SPR_BSZ8, 4, -1, NULL, 0, 0, S_NULL, 0},
	{"PALMTREE_TOP", 0, SPR_BSZ8, 5, -1, A_ConnectToGround,     MT_PALMTREE_TRUNK, 0, S_NULL, 0},

	// Disco ball
	{"DBALL1", 0, SPR_DBAL, FF_FULLBRIGHT,   5, NULL, 0, 0, S_DBALL2, 0},
	{"DBALL2", 0, SPR_DBAL, FF_FULLBRIGHT|1, 5, NULL, 0, 0, S_DBALL3, 0},
	{"DBALL3", 0, SPR_DBAL, FF_FULLBRIGHT|2, 5, NULL, 0, 0, S_DBALL4, 0},
	{"DBALL4", 0, SPR_DBAL, FF_FULLBRIGHT|3, 5, NULL, 0, 0, S_DBALL5, 0},
	{"DBALL5", 0, SPR_DBAL, FF_FULLBRIGHT|4, 5, NULL, 0, 0, S_DBALL6, 0},
	{"DBALL6", 0, SPR_DBAL, FF_FULLBRIGHT|5, 5, NULL, 0, 0, S_DBALL1, 0},

	{"EGGSTATUE2", 0, SPR_ESTA, 1, -1, NULL, 0, 0, S_NULL, 0},

	{"GINE", 0, SPR_GINE, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"PPAL", 0, SPR_PPAL, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"PPEL", 0, SPR_PPAL, 1, -1, NULL, 0, 0, S_NULL, 0},

	// Shield Orb
	{"ARMA1", 0, SPR_ARMA, FF_TRANS40   , 2, NULL, 0, 0, S_ARMA2 , 0},
	{"ARMA2", 0, SPR_ARMA, FF_TRANS40| 1, 2, NULL, 0, 0, S_ARMA3 , 0},
	{"ARMA3", 0, SPR_ARMA, FF_TRANS40| 2, 2, NULL, 0, 0, S_ARMA4 , 0},
	{"ARMA4", 0, SPR_ARMA, FF_TRANS40| 3, 2, NULL, 0, 0, S_ARMA5 , 0},
	{"ARMA5", 0, SPR_ARMA, FF_TRANS40| 4, 2, NULL, 0, 0, S_ARMA6 , 0},
	{"ARMA6", 0, SPR_ARMA, FF_TRANS40| 5, 2, NULL, 0, 0, S_ARMA7 , 0},
	{"ARMA7", 0, SPR_ARMA, FF_TRANS40| 6, 2, NULL, 0, 0, S_ARMA8 , 0},
	{"ARMA8", 0, SPR_ARMA, FF_TRANS40| 7, 2, NULL, 0, 0, S_ARMA9 , 0},
	{"ARMA9", 0, SPR_ARMA, FF_TRANS40| 8, 2, NULL, 0, 0, S_ARMA10, 0},
	{"ARMA10", 0, SPR_ARMA, FF_TRANS40| 9, 2, NULL, 0, 0, S_ARMA11, 0},
	{"ARMA11", 0, SPR_ARMA, FF_TRANS40|10, 2, NULL, 0, 0, S_ARMA12, 0},
	{"ARMA12", 0, SPR_ARMA, FF_TRANS40|11, 2, NULL, 0, 0, S_ARMA13, 0},
	{"ARMA13", 0, SPR_ARMA, FF_TRANS40|12, 2, NULL, 0, 0, S_ARMA14, 0},
	{"ARMA14", 0, SPR_ARMA, FF_TRANS40|13, 2, NULL, 0, 0, S_ARMA15, 0},
	{"ARMA15", 0, SPR_ARMA, FF_TRANS40|14, 2, NULL, 0, 0, S_ARMA16, 0},
	{"ARMA16", 0, SPR_ARMA, FF_TRANS40|15, 2, NULL, 0, 0, S_ARMA1 , 0},

	{"ARMF1", 0, SPR_ARMF, FF_FULLBRIGHT   , 2, NULL, 0, 0, S_ARMF2 , 0},
	{"ARMF2", 0, SPR_ARMF, FF_FULLBRIGHT| 1, 2, NULL, 0, 0, S_ARMF3 , 0},
	{"ARMF3", 0, SPR_ARMF, FF_FULLBRIGHT| 2, 2, NULL, 0, 0, S_ARMF4 , 0},
	{"ARMF4", 0, SPR_ARMF, FF_FULLBRIGHT| 3, 2, NULL, 0, 0, S_ARMF5 , 0},
	{"ARMF5", 0, SPR_ARMF, FF_FULLBRIGHT| 4, 2, NULL, 0, 0, S_ARMF6 , 0},
	{"ARMF6", 0, SPR_ARMF, FF_FULLBRIGHT| 5, 2, NULL, 0, 0, S_ARMF7 , 0},
	{"ARMF7", 0, SPR_ARMF, FF_FULLBRIGHT| 6, 2, NULL, 0, 0, S_ARMF8 , 0},
	{"ARMF8", 0, SPR_ARMF, FF_FULLBRIGHT| 7, 2, NULL, 0, 0, S_ARMF9 , 0},
	{"ARMF9", 0, SPR_ARMF, FF_FULLBRIGHT| 8, 2, NULL, 0, 0, S_ARMF10, 0},
	{"ARMF10", 0, SPR_ARMF, FF_FULLBRIGHT| 9, 2, NULL, 0, 0, S_ARMF11, 0},
	{"ARMF11", 0, SPR_ARMF, FF_FULLBRIGHT|10, 2, NULL, 0, 0, S_ARMF12, 0},
	{"ARMF12", 0, SPR_ARMF, FF_FULLBRIGHT|11, 2, NULL, 0, 0, S_ARMF13, 0},
	{"ARMF13", 0, SPR_ARMF, FF_FULLBRIGHT|12, 2, NULL, 0, 0, S_ARMF14, 0},
	{"ARMF14", 0, SPR_ARMF, FF_FULLBRIGHT|13, 2, NULL, 0, 0, S_ARMF15, 0},
	{"ARMF15", 0, SPR_ARMF, FF_FULLBRIGHT|14, 2, NULL, 0, 0, S_ARMF16, 0},
	{"ARMF16", 0, SPR_ARMF, FF_FULLBRIGHT|15, 2, NULL, 0, 0, S_ARMF17, 0},
	{"ARMF17", 0, SPR_ARMB, FF_FULLBRIGHT   , 2, NULL, 0, 0, S_ARMF18, 0},
	{"ARMF18", 0, SPR_ARMB, FF_FULLBRIGHT| 1, 2, NULL, 0, 0, S_ARMF19, 0},
	{"ARMF19", 0, SPR_ARMB, FF_FULLBRIGHT| 2, 2, NULL, 0, 0, S_ARMF20, 0},
	{"ARMF20", 0, SPR_ARMB, FF_FULLBRIGHT| 3, 2, NULL, 0, 0, S_ARMF21, 0},
	{"ARMF21", 0, SPR_ARMB, FF_FULLBRIGHT| 4, 2, NULL, 0, 0, S_ARMF22, 0},
	{"ARMF22", 0, SPR_ARMB, FF_FULLBRIGHT| 5, 2, NULL, 0, 0, S_ARMF23, 0},
	{"ARMF23", 0, SPR_ARMB, FF_FULLBRIGHT| 6, 2, NULL, 0, 0, S_ARMF24, 0},
	{"ARMF24", 0, SPR_ARMB, FF_FULLBRIGHT| 7, 2, NULL, 0, 0, S_ARMF25, 0},
	{"ARMF25", 0, SPR_ARMB, FF_FULLBRIGHT| 8, 2, NULL, 0, 0, S_ARMF26, 0},
	{"ARMF26", 0, SPR_ARMB, FF_FULLBRIGHT| 9, 2, NULL, 0, 0, S_ARMF27, 0},
	{"ARMF27", 0, SPR_ARMB, FF_FULLBRIGHT|10, 2, NULL, 0, 0, S_ARMF28, 0},
	{"ARMF28", 0, SPR_ARMB, FF_FULLBRIGHT|11, 2, NULL, 0, 0, S_ARMF29, 0},
	{"ARMF29", 0, SPR_ARMB, FF_FULLBRIGHT|12, 2, NULL, 0, 0, S_ARMF30, 0},
	{"ARMF30", 0, SPR_ARMB, FF_FULLBRIGHT|13, 2, NULL, 0, 0, S_ARMF31, 0},
	{"ARMF31", 0, SPR_ARMB, FF_FULLBRIGHT|14, 2, NULL, 0, 0, S_ARMF32, 0},
	{"ARMF32", 0, SPR_ARMB, FF_FULLBRIGHT|15, 2, NULL, 0, 0, S_ARMF1 , 0},

	{"ARMB1", 0, SPR_ARMB, FF_FULLBRIGHT   , 2, NULL, 1, 0, S_ARMB2 , 0},
	{"ARMB2", 0, SPR_ARMB, FF_FULLBRIGHT| 1, 2, NULL, 1, 0, S_ARMB3 , 0},
	{"ARMB3", 0, SPR_ARMB, FF_FULLBRIGHT| 2, 2, NULL, 1, 0, S_ARMB4 , 0},
	{"ARMB4", 0, SPR_ARMB, FF_FULLBRIGHT| 3, 2, NULL, 1, 0, S_ARMB5 , 0},
	{"ARMB5", 0, SPR_ARMB, FF_FULLBRIGHT| 4, 2, NULL, 1, 0, S_ARMB6 , 0},
	{"ARMB6", 0, SPR_ARMB, FF_FULLBRIGHT| 5, 2, NULL, 1, 0, S_ARMB7 , 0},
	{"ARMB7", 0, SPR_ARMB, FF_FULLBRIGHT| 6, 2, NULL, 1, 0, S_ARMB8 , 0},
	{"ARMB8", 0, SPR_ARMB, FF_FULLBRIGHT| 7, 2, NULL, 1, 0, S_ARMB9 , 0},
	{"ARMB9", 0, SPR_ARMB, FF_FULLBRIGHT| 8, 2, NULL, 1, 0, S_ARMB10, 0},
	{"ARMB10", 0, SPR_ARMB, FF_FULLBRIGHT| 9, 2, NULL, 1, 0, S_ARMB11, 0},
	{"ARMB11", 0, SPR_ARMB, FF_FULLBRIGHT|10, 2, NULL, 1, 0, S_ARMB12, 0},
	{"ARMB12", 0, SPR_ARMB, FF_FULLBRIGHT|11, 2, NULL, 1, 0, S_ARMB13, 0},
	{"ARMB13", 0, SPR_ARMB, FF_FULLBRIGHT|12, 2, NULL, 1, 0, S_ARMB14, 0},
	{"ARMB14", 0, SPR_ARMB, FF_FULLBRIGHT|13, 2, NULL, 1, 0, S_ARMB15, 0},
	{"ARMB15", 0, SPR_ARMB, FF_FULLBRIGHT|14, 2, NULL, 1, 0, S_ARMB16, 0},
	{"ARMB16", 0, SPR_ARMB, FF_FULLBRIGHT|15, 2, NULL, 1, 0, S_ARMB17, 0},
	{"ARMB17", 0, SPR_ARMF, FF_FULLBRIGHT   , 2, NULL, 1, 0, S_ARMB18, 0},
	{"ARMB18", 0, SPR_ARMF, FF_FULLBRIGHT| 1, 2, NULL, 1, 0, S_ARMB19, 0},
	{"ARMB19", 0, SPR_ARMF, FF_FULLBRIGHT| 2, 2, NULL, 1, 0, S_ARMB20, 0},
	{"ARMB20", 0, SPR_ARMF, FF_FULLBRIGHT| 3, 2, NULL, 1, 0, S_ARMB21, 0},
	{"ARMB21", 0, SPR_ARMF, FF_FULLBRIGHT| 4, 2, NULL, 1, 0, S_ARMB22, 0},
	{"ARMB22", 0, SPR_ARMF, FF_FULLBRIGHT| 5, 2, NULL, 1, 0, S_ARMB23, 0},
	{"ARMB23", 0, SPR_ARMF, FF_FULLBRIGHT| 6, 2, NULL, 1, 0, S_ARMB24, 0},
	{"ARMB24", 0, SPR_ARMF, FF_FULLBRIGHT| 7, 2, NULL, 1, 0, S_ARMB25, 0},
	{"ARMB25", 0, SPR_ARMF, FF_FULLBRIGHT| 8, 2, NULL, 1, 0, S_ARMB26, 0},
	{"ARMB26", 0, SPR_ARMF, FF_FULLBRIGHT| 9, 2, NULL, 1, 0, S_ARMB27, 0},
	{"ARMB27", 0, SPR_ARMF, FF_FULLBRIGHT|10, 2, NULL, 1, 0, S_ARMB28, 0},
	{"ARMB28", 0, SPR_ARMF, FF_FULLBRIGHT|11, 2, NULL, 1, 0, S_ARMB29, 0},
	{"ARMB29", 0, SPR_ARMF, FF_FULLBRIGHT|12, 2, NULL, 1, 0, S_ARMB30, 0},
	{"ARMB30", 0, SPR_ARMF, FF_FULLBRIGHT|13, 2, NULL, 1, 0, S_ARMB31, 0},
	{"ARMB31", 0, SPR_ARMF, FF_FULLBRIGHT|14, 2, NULL, 1, 0, S_ARMB32, 0},
	{"ARMB32", 0, SPR_ARMF, FF_FULLBRIGHT|15, 2, NULL, 1, 0, S_ARMB1 , 0},

	{"WIND1", 0, SPR_WIND, FF_TRANS70  , 2, NULL, 0, 0, S_WIND2, 0},
	{"WIND2", 0, SPR_WIND, FF_TRANS70|1, 2, NULL, 0, 0, S_WIND3, 0},
	{"WIND3", 0, SPR_WIND, FF_TRANS70|2, 2, NULL, 0, 0, S_WIND4, 0},
	{"WIND4", 0, SPR_WIND, FF_TRANS70|3, 2, NULL, 0, 0, S_WIND5, 0},
	{"WIND5", 0, SPR_WIND, FF_TRANS70|4, 2, NULL, 0, 0, S_WIND6, 0},
	{"WIND6", 0, SPR_WIND, FF_TRANS70|5, 2, NULL, 0, 0, S_WIND7, 0},
	{"WIND7", 0, SPR_WIND, FF_TRANS70|6, 2, NULL, 0, 0, S_WIND8, 0},
	{"WIND8", 0, SPR_WIND, FF_TRANS70|7, 2, NULL, 0, 0, S_WIND1, 0},

	{"MAGN1", 0, SPR_MAGN, FF_FULLBRIGHT|FF_TRANS40   , 2, NULL, 0, 0, S_MAGN2 , 0},
	{"MAGN2", 0, SPR_MAGN, FF_FULLBRIGHT|FF_TRANS40| 1, 2, NULL, 0, 0, S_MAGN3 , 0},
	{"MAGN3", 0, SPR_MAGN, FF_FULLBRIGHT|FF_TRANS40| 2, 2, NULL, 0, 0, S_MAGN4 , 0},
	{"MAGN4", 0, SPR_MAGN, FF_FULLBRIGHT|FF_TRANS40| 3, 2, NULL, 0, 0, S_MAGN5 , 0},
	{"MAGN5", 0, SPR_MAGN, FF_FULLBRIGHT|FF_TRANS40| 4, 2, NULL, 0, 0, S_MAGN6 , 0},
	{"MAGN6", 0, SPR_MAGN, FF_FULLBRIGHT|FF_TRANS40| 5, 2, NULL, 0, 0, S_MAGN7 , 0},
	{"MAGN7", 0, SPR_MAGN, FF_FULLBRIGHT|FF_TRANS40| 6, 2, NULL, 0, 0, S_MAGN8 , 0},
	{"MAGN8", 0, SPR_MAGN, FF_FULLBRIGHT|FF_TRANS40| 7, 2, NULL, 0, 0, S_MAGN9 , 0},
	{"MAGN9", 0, SPR_MAGN, FF_FULLBRIGHT|FF_TRANS40| 8, 2, NULL, 0, 0, S_MAGN10, 0},
	{"MAGN10", 0, SPR_MAGN, FF_FULLBRIGHT|FF_TRANS40| 9, 2, NULL, 0, 0, S_MAGN11, 0},
	{"MAGN11", 0, SPR_MAGN, FF_FULLBRIGHT|FF_TRANS40|10, 2, NULL, 0, 0, S_MAGN12, 0},
	{"MAGN12", 0, SPR_MAGN, FF_FULLBRIGHT|FF_TRANS40|11, 2, NULL, 0, 0, S_MAGN1 , 0},

	{"MAGN13", 0, SPR_MAGN, FF_FULLBRIGHT|FF_TRANS10|12, 2, NULL, 0, 0, S_MAGN1 , 0},

	{"FORC1", 0, SPR_FORC, FF_TRANS50  , 3, NULL, 0, 0, S_FORC2 , 0},
	{"FORC2", 0, SPR_FORC, FF_TRANS50|1, 3, NULL, 0, 0, S_FORC3 , 0},
	{"FORC3", 0, SPR_FORC, FF_TRANS50|2, 3, NULL, 0, 0, S_FORC4 , 0},
	{"FORC4", 0, SPR_FORC, FF_TRANS50|3, 3, NULL, 0, 0, S_FORC5 , 0},
	{"FORC5", 0, SPR_FORC, FF_TRANS50|4, 3, NULL, 0, 0, S_FORC6 , 0},
	{"FORC6", 0, SPR_FORC, FF_TRANS50|5, 3, NULL, 0, 0, S_FORC7 , 0},
	{"FORC7", 0, SPR_FORC, FF_TRANS50|6, 3, NULL, 0, 0, S_FORC8 , 0},
	{"FORC8", 0, SPR_FORC, FF_TRANS50|7, 3, NULL, 0, 0, S_FORC9 , 0},
	{"FORC9", 0, SPR_FORC, FF_TRANS50|8, 3, NULL, 0, 0, S_FORC10, 0},
	{"FORC10", 0, SPR_FORC, FF_TRANS50|9, 3, NULL, 0, 0, S_FORC1 , 0},

	{"FORC11", 0, SPR_FORC, FF_TRANS50|10, 3, NULL, 0, 0, S_FORC12, 0},
	{"FORC12", 0, SPR_FORC, FF_TRANS50|11, 3, NULL, 0, 0, S_FORC13, 0},
	{"FORC13", 0, SPR_FORC, FF_TRANS50|12, 3, NULL, 0, 0, S_FORC14, 0},
	{"FORC14", 0, SPR_FORC, FF_TRANS50|13, 3, NULL, 0, 0, S_FORC15, 0},
	{"FORC15", 0, SPR_FORC, FF_TRANS50|14, 3, NULL, 0, 0, S_FORC16, 0},
	{"FORC16", 0, SPR_FORC, FF_TRANS50|15, 3, NULL, 0, 0, S_FORC17, 0},
	{"FORC17", 0, SPR_FORC, FF_TRANS50|16, 3, NULL, 0, 0, S_FORC18, 0},
	{"FORC18", 0, SPR_FORC, FF_TRANS50|17, 3, NULL, 0, 0, S_FORC19, 0},
	{"FORC19", 0, SPR_FORC, FF_TRANS50|18, 3, NULL, 0, 0, S_FORC20, 0},
	{"FORC20", 0, SPR_FORC, FF_TRANS50|19, 3, NULL, 0, 0, S_FORC11, 0},

	{"FORC21", 0, SPR_FORC, FF_TRANS50|20, -1, NULL, 0, 0, S_NULL, 0},

	{"ELEM1", 0, SPR_ELEM, FF_TRANS50   , 4, NULL, 0, 0, S_ELEM2 , 0},
	{"ELEM2", 0, SPR_ELEM, FF_TRANS50| 1, 4, NULL, 0, 0, S_ELEM3 , 0},
	{"ELEM3", 0, SPR_ELEM, FF_TRANS50| 2, 4, NULL, 0, 0, S_ELEM4 , 0},
	{"ELEM4", 0, SPR_ELEM, FF_TRANS50| 3, 4, NULL, 0, 0, S_ELEM5 , 0},
	{"ELEM5", 0, SPR_ELEM, FF_TRANS50| 4, 4, NULL, 0, 0, S_ELEM6 , 0},
	{"ELEM6", 0, SPR_ELEM, FF_TRANS50| 5, 4, NULL, 0, 0, S_ELEM7 , 0},
	{"ELEM7", 0, SPR_ELEM, FF_TRANS50| 6, 4, NULL, 0, 0, S_ELEM8 , 0},
	{"ELEM8", 0, SPR_ELEM, FF_TRANS50| 7, 4, NULL, 0, 0, S_ELEM9 , 0},
	{"ELEM9", 0, SPR_ELEM, FF_TRANS50| 8, 4, NULL, 0, 0, S_ELEM10, 0},
	{"ELEM10", 0, SPR_ELEM, FF_TRANS50| 9, 4, NULL, 0, 0, S_ELEM11, 0},
	{"ELEM11", 0, SPR_ELEM, FF_TRANS50|10, 4, NULL, 0, 0, S_ELEM12, 0},
	{"ELEM12", 0, SPR_ELEM, FF_TRANS50|11, 4, NULL, 0, 0, S_ELEM1 , 0},

	{"ELEM13", 0, SPR_NULL,             0, 1, NULL, 0, 0, S_ELEM14, 0},
	{"ELEM14", 0, SPR_ELEM, FF_TRANS50|11, 1, NULL, 0, 0, S_ELEM1 , 0},

	{"ELEMF1", 0, SPR_ELEM, FF_FULLBRIGHT|12, 3, NULL, 0, 0, S_ELEMF2 , 0},
	{"ELEMF2", 0, SPR_ELEM, FF_FULLBRIGHT|13, 3, NULL, 0, 0, S_ELEMF3 , 0},
	{"ELEMF3", 0, SPR_ELEM, FF_FULLBRIGHT|14, 3, NULL, 0, 0, S_ELEMF4 , 0},
	{"ELEMF4", 0, SPR_ELEM, FF_FULLBRIGHT|15, 3, NULL, 0, 0, S_ELEMF5 , 0},
	{"ELEMF5", 0, SPR_ELEM, FF_FULLBRIGHT|16, 3, NULL, 0, 0, S_ELEMF6 , 0},
	{"ELEMF6", 0, SPR_ELEM, FF_FULLBRIGHT|17, 3, NULL, 0, 0, S_ELEMF7 , 0},
	{"ELEMF7", 0, SPR_ELEM, FF_FULLBRIGHT|18, 3, NULL, 0, 0, S_ELEMF8 , 0},
	{"ELEMF8", 0, SPR_ELEM, FF_FULLBRIGHT|19, 3, NULL, 0, 0, S_ELEMF1 , 0},

	{"ELEMF9", 0, SPR_ELEM, FF_FULLBRIGHT|20, 1, NULL, 0, 0, S_ELEMF10, 0},
	{"ELEMF10", 0, SPR_NULL, 0,                1, NULL, 0, 0, S_ELEMF1 , 0},

	{"PITY1", 0, SPR_PITY, FF_TRANS30   , 2, NULL, 0, 0, S_PITY2, 0},
	{"PITY2", 0, SPR_PITY, FF_TRANS30| 1, 2, NULL, 0, 0, S_PITY3, 0},
	{"PITY3", 0, SPR_PITY, FF_TRANS30| 2, 2, NULL, 0, 0, S_PITY4, 0},
	{"PITY4", 0, SPR_PITY, FF_TRANS30| 3, 2, NULL, 0, 0, S_PITY5, 0},
	{"PITY5", 0, SPR_PITY, FF_TRANS30| 4, 2, NULL, 0, 0, S_PITY6, 0},
	{"PITY6", 0, SPR_PITY, FF_TRANS30| 5, 2, NULL, 0, 0, S_PITY7, 0},
	{"PITY7", 0, SPR_PITY, FF_TRANS30| 6, 2, NULL, 0, 0, S_PITY8, 0},
	{"PITY8", 0, SPR_PITY, FF_TRANS30| 7, 2, NULL, 0, 0, S_PITY9, 0},
	{"PITY9", 0, SPR_PITY, FF_TRANS30| 8, 2, NULL, 0, 0, S_PITY10, 0},
	{"PITY10", 0, SPR_PITY, FF_TRANS30| 9, 2, NULL, 0, 0, S_PITY11, 0},
	{"PITY11", 0, SPR_PITY, FF_TRANS30|10, 2, NULL, 0, 0, S_PITY12, 0},
	{"PITY12", 0, SPR_PITY, FF_TRANS30|11, 2, NULL, 0, 0, S_PITY1, 0},

	{"FIRS1", 0, SPR_FIRS, FF_FULLBRIGHT|FF_TRANS40  , 2, NULL, 0, 0, S_FIRS2, 0},
	{"FIRS2", 0, SPR_FIRS, FF_FULLBRIGHT|FF_TRANS40|1, 2, NULL, 0, 0, S_FIRS3, 0},
	{"FIRS3", 0, SPR_FIRS, FF_FULLBRIGHT|FF_TRANS40|2, 2, NULL, 0, 0, S_FIRS4, 0},
	{"FIRS4", 0, SPR_FIRS, FF_FULLBRIGHT|FF_TRANS40|3, 2, NULL, 0, 0, S_FIRS5, 0},
	{"FIRS5", 0, SPR_FIRS, FF_FULLBRIGHT|FF_TRANS40|4, 2, NULL, 0, 0, S_FIRS6, 0},
	{"FIRS6", 0, SPR_FIRS, FF_FULLBRIGHT|FF_TRANS40|5, 2, NULL, 0, 0, S_FIRS7, 0},
	{"FIRS7", 0, SPR_FIRS, FF_FULLBRIGHT|FF_TRANS40|6, 2, NULL, 0, 0, S_FIRS8, 0},
	{"FIRS8", 0, SPR_FIRS, FF_FULLBRIGHT|FF_TRANS40|7, 2, NULL, 0, 0, S_FIRS9, 0},
	{"FIRS9", 0, SPR_FIRS, FF_FULLBRIGHT|FF_TRANS40|8, 2, NULL, 0, 0, S_FIRS1, 0},

	{"FIRS10", 0, SPR_FIRS, FF_FULLBRIGHT|FF_TRANS40|18, 1, NULL, 0, 0, S_FIRS11, 0},
	{"FIRS11", 0, SPR_NULL, 0,                           1, NULL, 0, 0, S_FIRS1 , 0},

	{"FIRSB1", 0, SPR_FIRS, FF_FULLBRIGHT|FF_TRANS40| 9, 2, NULL, 0, 0, S_FIRSB2, 0},
	{"FIRSB2", 0, SPR_FIRS, FF_FULLBRIGHT|FF_TRANS40|10, 2, NULL, 0, 0, S_FIRSB3, 0},
	{"FIRSB3", 0, SPR_FIRS, FF_FULLBRIGHT|FF_TRANS40|11, 2, NULL, 0, 0, S_FIRSB4, 0},
	{"FIRSB4", 0, SPR_FIRS, FF_FULLBRIGHT|FF_TRANS40|12, 2, NULL, 0, 0, S_FIRSB5, 0},
	{"FIRSB5", 0, SPR_FIRS, FF_FULLBRIGHT|FF_TRANS40|13, 2, NULL, 0, 0, S_FIRSB6, 0},
	{"FIRSB6", 0, SPR_FIRS, FF_FULLBRIGHT|FF_TRANS40|14, 2, NULL, 0, 0, S_FIRSB7, 0},
	{"FIRSB7", 0, SPR_FIRS, FF_FULLBRIGHT|FF_TRANS40|15, 2, NULL, 0, 0, S_FIRSB8, 0},
	{"FIRSB8", 0, SPR_FIRS, FF_FULLBRIGHT|FF_TRANS40|16, 2, NULL, 0, 0, S_FIRSB9, 0},
	{"FIRSB9", 0, SPR_FIRS, FF_FULLBRIGHT|FF_TRANS40|17, 2, NULL, 0, 0, S_FIRSB1, 0},

	{"FIRSB10", 0, SPR_NULL, 0,                           2, NULL, 0, 0, S_FIRSB1 , 0},

	{"BUBS1", 0, SPR_BUBS, FF_TRANS30  , 3, NULL, 0, 0, S_BUBS2, 0},
	{"BUBS2", 0, SPR_BUBS, FF_TRANS30|1, 3, NULL, 0, 0, S_BUBS3, 0},
	{"BUBS3", 0, SPR_BUBS, FF_TRANS30|2, 3, NULL, 0, 0, S_BUBS4, 0},
	{"BUBS4", 0, SPR_BUBS, FF_TRANS30|3, 3, NULL, 0, 0, S_BUBS5, 0},
	{"BUBS5", 0, SPR_BUBS, FF_TRANS30|4, 3, NULL, 0, 0, S_BUBS6, 0},
	{"BUBS6", 0, SPR_BUBS, FF_TRANS30|5, 3, NULL, 0, 0, S_BUBS7, 0},
	{"BUBS7", 0, SPR_BUBS, FF_TRANS30|6, 3, NULL, 0, 0, S_BUBS8, 0},
	{"BUBS8", 0, SPR_BUBS, FF_TRANS30|7, 3, NULL, 0, 0, S_BUBS9, 0},
	{"BUBS9", 0, SPR_BUBS, FF_TRANS30|8, 3, NULL, 0, 0, S_BUBS1, 0},

	{"BUBS10", 0, SPR_NULL, 0,   3, NULL, 0, 0, S_BUBS1, 0},
	{"BUBS11", 0, SPR_NULL, 0, 4*3, NULL, 0, 0, S_BUBS1, 0},

	{"BUBSB1", 0, SPR_BUBS, FF_TRANS30| 9, 3, NULL, 0, 0, S_BUBSB2, 0},
	{"BUBSB2", 0, SPR_BUBS, FF_TRANS30|10, 3, NULL, 0, 0, S_BUBSB3, 0},
	{"BUBSB3", 0, SPR_BUBS, FF_TRANS30|11, 3, NULL, 0, 0, S_BUBSB4, 0},
	{"BUBSB4", 0, SPR_BUBS, FF_TRANS30|10, 3, NULL, 0, 0, S_BUBSB1, 0},

	{"BUBSB5", 0, SPR_BUBS, FF_TRANS30|12, 3, NULL, 0, 0, S_BUBSB3, 0},
	{"BUBSB6", 0, SPR_BUBS, FF_TRANS30|13, 3, NULL, 0, 0, S_BUBSB5, 0},

	{"ZAPS1", 0, SPR_ZAPS, FF_FULLBRIGHT|FF_TRANS20   ,   2, NULL, 0, 0, S_ZAPS2 , 0},
	{"ZAPS2", 0, SPR_ZAPS, FF_FULLBRIGHT|FF_TRANS20| 1,   2, NULL, 0, 0, S_ZAPS3 , 0},
	{"ZAPS3", 0, SPR_ZAPS, FF_FULLBRIGHT|FF_TRANS20| 2,   2, NULL, 0, 0, S_ZAPS4 , 0},
	{"ZAPS4", 0, SPR_ZAPS, FF_FULLBRIGHT|FF_TRANS20| 3,   2, NULL, 0, 0, S_ZAPS5 , 0},
	{"ZAPS5", 0, SPR_ZAPS, FF_FULLBRIGHT|FF_TRANS20| 4,   2, NULL, 0, 0, S_ZAPS6 , 0},
	{"ZAPS6", 0, SPR_ZAPS, FF_FULLBRIGHT|FF_TRANS20| 5,   2, NULL, 0, 0, S_ZAPS7 , 0},
	{"ZAPS7", 0, SPR_ZAPS, FF_FULLBRIGHT|FF_TRANS20| 6,   2, NULL, 0, 0, S_ZAPS8 , 0},
	{"ZAPS8", 0, SPR_ZAPS, FF_FULLBRIGHT|FF_TRANS20| 7,   2, NULL, 0, 0, S_ZAPS9 , 0},
	{"ZAPS9", 0, SPR_ZAPS, FF_FULLBRIGHT|FF_TRANS20| 8,   2, NULL, 0, 0, S_ZAPS10, 0},
	{"ZAPS10", 0, SPR_ZAPS, FF_FULLBRIGHT|FF_TRANS20| 9,   2, NULL, 0, 0, S_ZAPS11, 0},
	{"ZAPS11", 0, SPR_ZAPS, FF_FULLBRIGHT|FF_TRANS20|10,   2, NULL, 0, 0, S_ZAPS12, 0},
	{"ZAPS12", 0, SPR_ZAPS, FF_FULLBRIGHT|FF_TRANS20|11,   2, NULL, 0, 0, S_ZAPS13, 0},
	{"ZAPS13", 0, SPR_NULL,                           0, 9*2, NULL, 0, 0, S_ZAPS14, 0},
	{"ZAPS14", 0, SPR_ZAPS, FF_FULLBRIGHT|FF_TRANS20| 9,   2, NULL, 0, 0, S_ZAPS15, 0},
	{"ZAPS15", 0, SPR_ZAPS, FF_FULLBRIGHT|FF_TRANS20|10,   2, NULL, 0, 0, S_ZAPS16, 0},
	{"ZAPS16", 0, SPR_ZAPS, FF_FULLBRIGHT|FF_TRANS20|11,   2, NULL, 0, 0, S_ZAPS1 , 0},

	{"ZAPSB1", 0, SPR_NULL,                           0, 12*2, NULL, 0, 0, S_ZAPSB2 , 0},
	{"ZAPSB2", 0, SPR_ZAPS, FF_FULLBRIGHT|FF_TRANS20| 8,    2, NULL, 0, 0, S_ZAPSB3 , 0},
	{"ZAPSB3", 0, SPR_ZAPS, FF_FULLBRIGHT|FF_TRANS20| 7,    2, NULL, 0, 0, S_ZAPSB4 , 0},
	{"ZAPSB4", 0, SPR_ZAPS, FF_FULLBRIGHT|FF_TRANS20| 6,    2, NULL, 0, 0, S_ZAPSB5 , 0},
	{"ZAPSB5", 0, SPR_ZAPS, FF_FULLBRIGHT|FF_TRANS20| 5,    2, NULL, 0, 0, S_ZAPSB6 , 0},
	{"ZAPSB6", 0, SPR_ZAPS, FF_FULLBRIGHT|FF_TRANS20| 4,    2, NULL, 0, 0, S_ZAPSB7 , 0},
	{"ZAPSB7", 0, SPR_ZAPS, FF_FULLBRIGHT|FF_TRANS20| 3,    2, NULL, 0, 0, S_ZAPSB8 , 0},
	{"ZAPSB8", 0, SPR_ZAPS, FF_FULLBRIGHT|FF_TRANS20| 2,    2, NULL, 0, 0, S_ZAPSB9 , 0},
	{"ZAPSB9", 0, SPR_ZAPS, FF_FULLBRIGHT|FF_TRANS20| 1,    2, NULL, 0, 0, S_ZAPSB10, 0},
	{"ZAPSB10", 0, SPR_ZAPS, FF_FULLBRIGHT|FF_TRANS20   ,    2, NULL, 0, 0, S_ZAPSB11, 0},
	{"ZAPSB11", 0, SPR_NULL,                           0, 15*2, NULL, 0, 0, S_ZAPSB2 , 0},

	// Thunder spark
	{"THUNDERCOIN_SPARK", 0, SPR_SSPK, FF_ANIMATE|FF_FULLBRIGHT, -1, NULL, 1, 2, S_NULL, 0},

	// Invincibility Sparkles
	{"IVSP", 0, SPR_IVSP, FF_ANIMATE|FF_FULLBRIGHT, 32, NULL, 31, 1, S_NULL, 0},

	// Super Sonic Spark
	{"SSPK1", 0, SPR_SSPK,   FF_FULLBRIGHT, 2, NULL, 0, 0, S_SSPK2, 0},
	{"SSPK2", 0, SPR_SSPK, 1|FF_FULLBRIGHT, 2, NULL, 0, 0, S_SSPK3, 0},
	{"SSPK3", 0, SPR_SSPK, 2|FF_FULLBRIGHT, 2, NULL, 0, 0, S_SSPK4, 0},
	{"SSPK4", 0, SPR_SSPK, 1|FF_FULLBRIGHT, 2, NULL, 0, 0, S_SSPK5, 0},
	{"SSPK5", 0, SPR_SSPK,   FF_FULLBRIGHT, 2, NULL, 0, 0, S_NULL, 0},

	// Flicky-sized bubble
	{"FLICKY_BUBBLE", 0, SPR_FBUB, 0, -1, NULL, 0, 0, S_NULL, 0},

	// Bluebird
	{"FLICKY_01_OUT", 0, SPR_FL01, 0, 2, A_FlickyCheck, S_FLICKY_01_FLAP1, S_FLICKY_01_FLAP1, S_FLICKY_01_OUT, 0},
	{"FLICKY_01_FLAP1", 0, SPR_FL01, 1, 3, A_FlickyFly,          4*FRACUNIT,       16*FRACUNIT, S_FLICKY_01_FLAP2, 0},
	{"FLICKY_01_FLAP2", 0, SPR_FL01, 2, 3, A_FlickyFly,          4*FRACUNIT,       16*FRACUNIT, S_FLICKY_01_FLAP3, 0},
	{"FLICKY_01_FLAP3", 0, SPR_FL01, 3, 3, A_FlickyFly,          4*FRACUNIT,       16*FRACUNIT, S_FLICKY_01_FLAP1, 0},
	{"FLICKY_01_STAND", 0, SPR_FL01, FF_ANIMATE|1, -1, NULL, 2, 3, S_NULL, 0},
	{"FLICKY_01_CENTER", 0, SPR_NULL, 0, 15, A_FlickyCenter, MT_FLICKY_01, 384*FRACUNIT, S_FLICKY_01_CENTER, 0},

	// Rabbit
	{"FLICKY_02_OUT", 0, SPR_FL02, 0, 2, A_FlickyCheck, S_FLICKY_02_AIM,                0, S_FLICKY_02_OUT, 0},
	{"FLICKY_02_AIM", 0, SPR_FL02, 1, 1, A_FlickyAim,             ANG30,      32*FRACUNIT, S_FLICKY_02_HOP, 0},
	{"FLICKY_02_HOP", 0, SPR_FL02, 1, 1, A_FlickyHop,        6*FRACUNIT,       4*FRACUNIT, S_FLICKY_02_UP, 0},
	{"FLICKY_02_UP", 0, SPR_FL02, 2, 2, A_FlickyCheck, S_FLICKY_02_AIM, S_FLICKY_02_DOWN, S_FLICKY_02_UP, 0},
	{"FLICKY_02_DOWN", 0, SPR_FL02, 3, 2, A_FlickyCheck, S_FLICKY_02_AIM,                0, S_FLICKY_02_DOWN, 0},
	{"FLICKY_02_STAND", 0, SPR_FL02, FF_ANIMATE|1, -1, NULL, 2, 4, S_NULL, 0},
	{"FLICKY_02_CENTER", 0, SPR_NULL, 0, 15, A_FlickyCenter, MT_FLICKY_02, 384*FRACUNIT, S_FLICKY_02_CENTER, 0},

	// Chicken
	{"FLICKY_03_OUT", 0, SPR_FL03, 0, 2, A_FlickyCheck,   S_FLICKY_03_AIM, S_FLICKY_03_FLAP1, S_FLICKY_03_OUT, 0},
	{"FLICKY_03_AIM", 0, SPR_FL03, 1, 1, A_FlickyAim,            ANGLE_45,       32*FRACUNIT, S_FLICKY_03_HOP, 0},
	{"FLICKY_03_HOP", 0, SPR_FL03, 1, 1, A_FlickyHop,          7*FRACUNIT,        2*FRACUNIT, S_FLICKY_03_UP, 0},
	{"FLICKY_03_UP", 0, SPR_FL03, 2, 2, A_FlickyFlutter, S_FLICKY_03_HOP, S_FLICKY_03_FLAP1, S_FLICKY_03_UP, 0},
	{"FLICKY_03_FLAP1", 0, SPR_FL03, 3, 2, A_FlickyFlutter, S_FLICKY_03_HOP,                 0, S_FLICKY_03_FLAP2, 0},
	{"FLICKY_03_FLAP2", 0, SPR_FL03, 4, 2, A_FlickyFlutter, S_FLICKY_03_HOP,                 0, S_FLICKY_03_FLAP1, 0},
	{"FLICKY_03_STAND", 0, SPR_FL03, FF_ANIMATE|1, -1, NULL, 2, 4, S_NULL, 0},
	{"FLICKY_03_CENTER", 0, SPR_NULL, 0, 15, A_FlickyCenter, MT_FLICKY_03, 384*FRACUNIT, S_FLICKY_03_CENTER, 0},

	// Seal
	{"FLICKY_04_OUT", 0, SPR_FL04, 0, 2, A_FlickyCheck, S_FLICKY_04_AIM,                 0, S_FLICKY_04_OUT, 0},
	{"FLICKY_04_AIM", 0, SPR_FL04, 1, 1, A_FlickyAim,             ANG30,       32*FRACUNIT, S_FLICKY_04_HOP, 0},
	{"FLICKY_04_HOP", 0, SPR_FL04, 1, 1, A_FlickyHop,        3*FRACUNIT,        2*FRACUNIT, S_FLICKY_04_UP, 0},
	{"FLICKY_04_UP", 0, SPR_FL04, 2, 4, A_FlickyCheck, S_FLICKY_04_AIM,  S_FLICKY_04_DOWN, S_FLICKY_04_UP, 0},
	{"FLICKY_04_DOWN", 0, SPR_FL04, 3, 4, A_FlickyCheck, S_FLICKY_04_AIM,                 0, S_FLICKY_04_DOWN, 0},
	{"FLICKY_04_SWIM1", 0, SPR_FL04, 3, 4, A_FlickyFly,        2*FRACUNIT,       48*FRACUNIT, S_FLICKY_04_SWIM2, 0},
	{"FLICKY_04_SWIM2", 0, SPR_FL04, 4, 4, A_FlickyCoast,        FRACUNIT, S_FLICKY_04_SWIM1, S_FLICKY_04_SWIM3, 0},
	{"FLICKY_04_SWIM3", 0, SPR_FL04, 3, 4, A_FlickyCoast,        FRACUNIT, S_FLICKY_04_SWIM1, S_FLICKY_04_SWIM4, 0},
	{"FLICKY_04_SWIM4", 0, SPR_FL04, 5, 4, A_FlickyCoast,        FRACUNIT, S_FLICKY_04_SWIM1, S_FLICKY_04_SWIM1, 0},
	{"FLICKY_04_STAND", 0, SPR_FL04, FF_ANIMATE|1, -1, NULL, 2, 4, S_NULL, 0},
	{"FLICKY_04_CENTER", 0, SPR_NULL, 0, 15, A_FlickyCenter, MT_FLICKY_04, 384*FRACUNIT, S_FLICKY_04_CENTER, 0},

	// Pig
	{"FLICKY_05_OUT", 0, SPR_FL05, 0, 2, A_FlickyCheck, S_FLICKY_05_AIM,                0, S_FLICKY_05_OUT, 0},
	{"FLICKY_05_AIM", 0, SPR_FL05, 1, 1, A_FlickyAim,             ANG20,      32*FRACUNIT, S_FLICKY_05_HOP, 0},
	{"FLICKY_05_HOP", 0, SPR_FL05, 1, 1, A_FlickyHop,        4*FRACUNIT,       3*FRACUNIT, S_FLICKY_05_UP, 0},
	{"FLICKY_05_UP", 0, SPR_FL05, 2, 2, A_FlickyCheck, S_FLICKY_05_AIM, S_FLICKY_05_DOWN, S_FLICKY_05_UP, 0},
	{"FLICKY_05_DOWN", 0, SPR_FL05, 3, 2, A_FlickyCheck, S_FLICKY_05_AIM,                0, S_FLICKY_05_DOWN, 0},
	{"FLICKY_05_STAND", 0, SPR_FL05, FF_ANIMATE|1, -1, NULL, 2, 4, S_NULL, 0},
	{"FLICKY_05_CENTER", 0, SPR_NULL, 0, 15, A_FlickyCenter, MT_FLICKY_05, 384*FRACUNIT, S_FLICKY_05_CENTER, 0},

	// Chipmunk
	{"FLICKY_06_OUT", 0, SPR_FL06, 0, 2, A_FlickyCheck, S_FLICKY_06_AIM,                0, S_FLICKY_06_OUT, 0},
	{"FLICKY_06_AIM", 0, SPR_FL06, 1, 1, A_FlickyAim,          ANGLE_90,      32*FRACUNIT, S_FLICKY_06_HOP, 0},
	{"FLICKY_06_HOP", 0, SPR_FL06, 1, 1, A_FlickyHop,        5*FRACUNIT,       6*FRACUNIT, S_FLICKY_06_UP, 0},
	{"FLICKY_06_UP", 0, SPR_FL06, 2, 2, A_FlickyCheck, S_FLICKY_06_AIM, S_FLICKY_06_DOWN, S_FLICKY_06_UP, 0},
	{"FLICKY_06_DOWN", 0, SPR_FL06, 3, 2, A_FlickyCheck, S_FLICKY_06_AIM,                0, S_FLICKY_06_DOWN, 0},
	{"FLICKY_06_STAND", 0, SPR_FL06, FF_ANIMATE|1, -1, NULL, 2, 4, S_NULL, 0},
	{"FLICKY_06_CENTER", 0, SPR_NULL, 0, 15, A_FlickyCenter, MT_FLICKY_06, 384*FRACUNIT, S_FLICKY_06_CENTER, 0},

	// Penguin
	{"FLICKY_07_OUT", 0, SPR_FL07, 0, 2, A_FlickyCheck, S_FLICKY_07_AIML,                 0, S_FLICKY_07_OUT, 0},
	{"FLICKY_07_AIML", 0, SPR_FL07, 1, 1, A_FlickyAim,              ANG30,       32*FRACUNIT, S_FLICKY_07_HOPL, 0},
	{"FLICKY_07_HOPL", 0, SPR_FL07, 1, 1, A_FlickyHop,         4*FRACUNIT,        2*FRACUNIT, S_FLICKY_07_UPL, 0},
	{"FLICKY_07_UPL", 0, SPR_FL07, 2, 4, A_FlickyCheck, S_FLICKY_07_AIMR, S_FLICKY_07_DOWNL, S_FLICKY_07_UPL, 0},
	{"FLICKY_07_DOWNL", 0, SPR_FL07, 1, 4, A_FlickyCheck, S_FLICKY_07_AIMR,                 0, S_FLICKY_07_DOWNL, 0},
	{"FLICKY_07_AIMR", 0, SPR_FL07, 1, 1, A_FlickyAim,              ANG30,       32*FRACUNIT, S_FLICKY_07_HOPR, 0},
	{"FLICKY_07_HOPR", 0, SPR_FL07, 1, 1, A_FlickyHop,         4*FRACUNIT,        2*FRACUNIT, S_FLICKY_07_UPR, 0},
	{"FLICKY_07_UPR", 0, SPR_FL07, 3, 4, A_FlickyCheck, S_FLICKY_07_AIML, S_FLICKY_07_DOWNR, S_FLICKY_07_UPR, 0},
	{"FLICKY_07_DOWNR", 0, SPR_FL07, 1, 4, A_FlickyCheck, S_FLICKY_07_AIML,                 0, S_FLICKY_07_DOWNR, 0},
	{"FLICKY_07_SWIM1", 0, SPR_FL07, 4, 4, A_FlickyFly,         3*FRACUNIT,       72*FRACUNIT, S_FLICKY_07_SWIM2, 0},
	{"FLICKY_07_SWIM2", 0, SPR_FL07, 5, 4, A_FlickyCoast,         FRACUNIT, S_FLICKY_07_SWIM1, S_FLICKY_07_SWIM3, 0},
	{"FLICKY_07_SWIM3", 0, SPR_FL07, 6, 4, A_FlickyCoast,       2*FRACUNIT, S_FLICKY_07_SWIM1, S_FLICKY_07_SWIM3, 0},
	{"FLICKY_07_STAND", 0, SPR_FL07, FF_ANIMATE|1, -1, NULL, 2, 4, S_NULL, 0},
	{"FLICKY_07_CENTER", 0, SPR_NULL, 0, 15, A_FlickyCenter, MT_FLICKY_07, 384*FRACUNIT, S_FLICKY_07_CENTER, 0},

	// Fish
	{"FLICKY_08_OUT", 0, SPR_FL08, 0, 2, A_FlickyCheck, S_FLICKY_08_AIM,                 0, S_FLICKY_08_OUT, 0},
	{"FLICKY_08_AIM", 0, SPR_FL08, 2, 1, A_FlickyAim,             ANG30,       32*FRACUNIT, S_FLICKY_08_HOP, 0},
	{"FLICKY_08_HOP", 0, SPR_FL08, 2, 1, A_FlickyFlounder,   2*FRACUNIT,        1*FRACUNIT, S_FLICKY_08_FLAP1, 0},
	{"FLICKY_08_FLAP1", 0, SPR_FL08, 0, 4, A_FlickyCheck, S_FLICKY_08_AIM,                 0, S_FLICKY_08_FLAP2, 0},
	{"FLICKY_08_FLAP2", 0, SPR_FL08, 1, 4, A_FlickyCheck, S_FLICKY_08_AIM,                 0, S_FLICKY_08_FLAP3, 0},
	{"FLICKY_08_FLAP3", 0, SPR_FL08, 0, 4, A_FlickyCheck, S_FLICKY_08_AIM,                 0, S_FLICKY_08_FLAP4, 0},
	{"FLICKY_08_FLAP4", 0, SPR_FL08, 2, 4, A_FlickyCheck, S_FLICKY_08_AIM,                 0, S_FLICKY_08_FLAP1, 0},
	{"FLICKY_08_SWIM1", 0, SPR_FL08, 0, 4, A_FlickyFly,        3*FRACUNIT,       64*FRACUNIT, S_FLICKY_08_SWIM2, 0},
	{"FLICKY_08_SWIM2", 0, SPR_FL08, 1, 4, A_FlickyCoast,        FRACUNIT, S_FLICKY_08_SWIM1, S_FLICKY_08_SWIM3, 0},
	{"FLICKY_08_SWIM3", 0, SPR_FL08, 0, 4, A_FlickyCoast,        FRACUNIT, S_FLICKY_08_SWIM1, S_FLICKY_08_SWIM4, 0},
	{"FLICKY_08_SWIM4", 0, SPR_FL08, 2, 4, A_FlickyCoast,        FRACUNIT, S_FLICKY_08_SWIM1, S_FLICKY_08_SWIM4, 0},
	{"FLICKY_08_STAND", 0, SPR_FL08, FF_ANIMATE, -1, NULL, 2, 4, S_NULL, 0},
	{"FLICKY_08_CENTER", 0, SPR_NULL, 0, 15, A_FlickyCenter, MT_FLICKY_08, 384*FRACUNIT, S_FLICKY_08_CENTER, 0},

	// Ram
	{"FLICKY_09_OUT", 0, SPR_FL09, 0, 2, A_FlickyCheck, S_FLICKY_09_AIM,                0, S_FLICKY_09_OUT, 0},
	{"FLICKY_09_AIM", 0, SPR_FL09, 1, 1, A_FlickyAim,             ANG30,      32*FRACUNIT, S_FLICKY_09_HOP, 0},
	{"FLICKY_09_HOP", 0, SPR_FL09, 1, 1, A_FlickyHop,        7*FRACUNIT,       2*FRACUNIT, S_FLICKY_09_UP, 0},
	{"FLICKY_09_UP", 0, SPR_FL09, 2, 2, A_FlickyCheck, S_FLICKY_09_AIM, S_FLICKY_09_DOWN, S_FLICKY_09_UP, 0},
	{"FLICKY_09_DOWN", 0, SPR_FL09, 3, 2, A_FlickyCheck, S_FLICKY_09_AIM,                0, S_FLICKY_09_DOWN, 0},
	{"FLICKY_09_STAND", 0, SPR_FL09, FF_ANIMATE|1, -1, NULL, 2, 4, S_NULL, 0},
	{"FLICKY_09_CENTER", 0, SPR_NULL, 0, 15, A_FlickyCenter, MT_FLICKY_09, 384*FRACUNIT, S_FLICKY_09_CENTER, 0},

	// Puffin
	{"FLICKY_10_OUT", 0, SPR_FL10, 0, 2, A_FlickyCheck, S_FLICKY_10_FLAP1, S_FLICKY_10_FLAP1, S_FLICKY_10_OUT, 0},
	{"FLICKY_10_FLAP1", 0, SPR_FL10, 1, 3, A_FlickySoar,         4*FRACUNIT,       16*FRACUNIT, S_FLICKY_10_FLAP2, 0},
	{"FLICKY_10_FLAP2", 0, SPR_FL10, 2, 3, A_FlickySoar,         4*FRACUNIT,       16*FRACUNIT, S_FLICKY_10_FLAP1, 0},
	{"FLICKY_10_STAND", 0, SPR_FL10, FF_ANIMATE|1, -1, NULL, 1, 3, S_NULL, 0},
	{"FLICKY_10_CENTER", 0, SPR_NULL, 0, 15, A_FlickyCenter, MT_FLICKY_10, 384*FRACUNIT, S_FLICKY_10_CENTER, 0},

	// Cow
	{"FLICKY_11_OUT", 0, SPR_FL11, 0, 2, A_FlickyCheck, S_FLICKY_11_AIM,           0, S_FLICKY_11_OUT, 0},
	{"FLICKY_11_AIM", 0, SPR_FL11, 1, 1, A_FlickyAim,          ANGLE_90, 64*FRACUNIT, S_FLICKY_11_RUN1, 0},
	{"FLICKY_11_RUN1", 0, SPR_FL11, 1, 3, A_FlickyHop,        FRACUNIT/2,  2*FRACUNIT, S_FLICKY_11_RUN2, 0},
	{"FLICKY_11_RUN2", 0, SPR_FL11, 2, 4, A_FlickyHop,        FRACUNIT/2,  2*FRACUNIT, S_FLICKY_11_RUN3, 0},
	{"FLICKY_11_RUN3", 0, SPR_FL11, 3, 4, A_FlickyHop,        FRACUNIT/2,  2*FRACUNIT, S_FLICKY_11_AIM, 0},
	{"FLICKY_11_STAND", 0, SPR_FL11, FF_ANIMATE|1, -1, NULL, 2, 4, S_NULL, 0},
	{"FLICKY_11_CENTER", 0, SPR_NULL, 0, 15, A_FlickyCenter, MT_FLICKY_11, 384*FRACUNIT, S_FLICKY_11_CENTER, 0},

	// Rat
	{"FLICKY_12_OUT", 0, SPR_FL12, 0, 2, A_FlickyCheck, S_FLICKY_12_AIM,           0, S_FLICKY_12_OUT, 0},
	{"FLICKY_12_AIM", 0, SPR_FL12, 1, 1, A_FlickyAim,          ANGLE_90, 32*FRACUNIT, S_FLICKY_12_RUN1, 0},
	{"FLICKY_12_RUN1", 0, SPR_FL12, 1, 2, A_FlickyHop,                 1, 12*FRACUNIT, S_FLICKY_12_RUN2, 0},
	{"FLICKY_12_RUN2", 0, SPR_FL12, 2, 3, A_FlickyHop,                 1, 12*FRACUNIT, S_FLICKY_12_RUN3, 0},
	{"FLICKY_12_RUN3", 0, SPR_FL12, 3, 3, A_FlickyHop,                 1, 12*FRACUNIT, S_FLICKY_12_AIM, 0},
	{"FLICKY_12_STAND", 0, SPR_FL12, FF_ANIMATE|1, -1, NULL, 2, 4, S_NULL, 0},
	{"FLICKY_12_CENTER", 0, SPR_NULL, 0, 15, A_FlickyCenter, MT_FLICKY_12, 384*FRACUNIT, S_FLICKY_12_CENTER, 0},

	// Bear
	{"FLICKY_13_OUT", 0, SPR_FL13, 0, 2, A_FlickyCheck, S_FLICKY_13_AIM,                0, S_FLICKY_13_OUT, 0},
	{"FLICKY_13_AIM", 0, SPR_FL13, 1, 1, A_FlickyAim,             ANG30,      32*FRACUNIT, S_FLICKY_13_HOP, 0},
	{"FLICKY_13_HOP", 0, SPR_FL13, 1, 1, A_FlickyHop,        5*FRACUNIT,       3*FRACUNIT, S_FLICKY_13_UP, 0},
	{"FLICKY_13_UP", 0, SPR_FL13, 2, 2, A_FlickyCheck, S_FLICKY_13_AIM, S_FLICKY_13_DOWN, S_FLICKY_13_UP, 0},
	{"FLICKY_13_DOWN", 0, SPR_FL13, 3, 2, A_FlickyCheck, S_FLICKY_13_AIM,                0, S_FLICKY_13_DOWN, 0},
	{"FLICKY_13_STAND", 0, SPR_FL13, FF_ANIMATE|1, -1, NULL, 2, 4, S_NULL, 0},
	{"FLICKY_13_CENTER", 0, SPR_NULL, 0, 15, A_FlickyCenter, MT_FLICKY_13, 384*FRACUNIT, S_FLICKY_13_CENTER, 0},

	// Dove
	{"FLICKY_14_OUT", 0, SPR_FL14, 0, 2, A_FlickyCheck, S_FLICKY_14_FLAP1, S_FLICKY_14_FLAP1, S_FLICKY_14_OUT, 0},
	{"FLICKY_14_FLAP1", 0, SPR_FL14, 1, 3, A_FlickySoar,         4*FRACUNIT,       32*FRACUNIT, S_FLICKY_14_FLAP2, 0},
	{"FLICKY_14_FLAP2", 0, SPR_FL14, 2, 3, A_FlickySoar,         4*FRACUNIT,       32*FRACUNIT, S_FLICKY_14_FLAP3, 0},
	{"FLICKY_14_FLAP3", 0, SPR_FL14, 3, 3, A_FlickySoar,         4*FRACUNIT,       32*FRACUNIT, S_FLICKY_14_FLAP1, 0},
	{"FLICKY_14_STAND", 0, SPR_FL14, FF_ANIMATE|1, -1, NULL, 2, 3, S_NULL, 0},
	{"FLICKY_14_CENTER", 0, SPR_NULL, 0, 15, A_FlickyCenter, MT_FLICKY_14, 384*FRACUNIT, S_FLICKY_14_CENTER, 0},

	// Cat
	{"FLICKY_15_OUT", 0, SPR_FL15, 0, 2, A_FlickyCheck, S_FLICKY_15_AIM,                0, S_FLICKY_15_OUT, 0},
	{"FLICKY_15_AIM", 0, SPR_FL15, 1, 1, A_FlickyAim,             ANG30,      32*FRACUNIT, S_FLICKY_15_HOP, 0},
	{"FLICKY_15_HOP", 0, SPR_FL15, 1, 1, A_FlickyFlounder,   2*FRACUNIT,       6*FRACUNIT, S_FLICKY_15_UP, 0},
	{"FLICKY_15_UP", 0, SPR_FL15, 2, 2, A_FlickyCheck, S_FLICKY_15_AIM, S_FLICKY_15_DOWN, S_FLICKY_15_UP, 0},
	{"FLICKY_15_DOWN", 0, SPR_FL15, 3, 2, A_FlickyCheck, S_FLICKY_15_AIM,                0, S_FLICKY_15_DOWN, 0},
	{"FLICKY_15_STAND", 0, SPR_FL15, FF_ANIMATE|1, -1, NULL, 2, 4, S_NULL, 0},
	{"FLICKY_15_CENTER", 0, SPR_NULL, 0, 15, A_FlickyCenter, MT_FLICKY_15, 384*FRACUNIT, S_FLICKY_15_CENTER, 0},

	// Canary
	{"FLICKY_16_OUT", 0, SPR_FL16, 0, 2, A_FlickyHeightCheck, S_FLICKY_16_FLAP1,          0, S_FLICKY_16_OUT, 0},
	{"FLICKY_16_FLAP1", 0, SPR_FL16, 1, 3, A_FlickyFly,                4*FRACUNIT, 8*FRACUNIT, S_FLICKY_16_FLAP2, 0},
	{"FLICKY_16_FLAP2", 0, SPR_FL16, 2, 3, A_SetObjectFlags,         MF_NOGRAVITY,          1, S_FLICKY_16_FLAP3, 0},
	{"FLICKY_16_FLAP3", 0, SPR_FL16, 3, 3, A_FlickyHeightCheck, S_FLICKY_16_FLAP1,          0, S_FLICKY_16_FLAP3, 0},
	{"FLICKY_16_STAND", 0, SPR_FL16, FF_ANIMATE|1, -1, NULL, 2, 3, S_NULL, 0},
	{"FLICKY_16_CENTER", 0, SPR_NULL, 0, 15, A_FlickyCenter, MT_FLICKY_16, 384*FRACUNIT, S_FLICKY_16_CENTER, 0},

	// Spider
	{"SECRETFLICKY_01_OUT", 0, SPR_FS01, 0, 2, A_FlickyCheck, S_SECRETFLICKY_01_AIM,                      0, S_SECRETFLICKY_01_OUT, 0},
	{"SECRETFLICKY_01_AIM", 0, SPR_FS01, 1, 1, A_FlickyAim,                   ANG30,            32*FRACUNIT, S_SECRETFLICKY_01_HOP, 0},
	{"SECRETFLICKY_01_HOP", 0, SPR_FS01, 1, 1, A_FlickyFlounder,         2*FRACUNIT,             6*FRACUNIT, S_SECRETFLICKY_01_UP, 0},
	{"SECRETFLICKY_01_UP", 0, SPR_FS01, 2, 2, A_FlickyCheck, S_SECRETFLICKY_01_AIM, S_SECRETFLICKY_01_DOWN, S_SECRETFLICKY_01_UP, 0},
	{"SECRETFLICKY_01_DOWN", 0, SPR_FS01, 3, 2, A_FlickyCheck, S_SECRETFLICKY_01_AIM,                      0, S_SECRETFLICKY_01_DOWN, 0},
	{"SECRETFLICKY_01_STAND", 0, SPR_FS01, FF_ANIMATE|1, -1, NULL, 2, 4, S_NULL, 0},
	{"SECRETFLICKY_01_CENTER", 0, SPR_NULL, 0, 15, A_FlickyCenter, MT_SECRETFLICKY_01, 384*FRACUNIT, S_SECRETFLICKY_01_CENTER, 0},

	// Bat
	{"SECRETFLICKY_02_OUT", 0, SPR_FS02, 0, 2, A_FlickyHeightCheck, S_SECRETFLICKY_02_FLAP1, S_SECRETFLICKY_02_FLAP1, S_SECRETFLICKY_02_OUT, 0},
	{"SECRETFLICKY_02_FLAP1", 0, SPR_FS02, 1, 3, A_FlickyFly,                      4*FRACUNIT,             16*FRACUNIT, S_SECRETFLICKY_02_FLAP2, 0},
	{"SECRETFLICKY_02_FLAP2", 0, SPR_FS02, 2, 3, A_FlickyFly,                      4*FRACUNIT,             16*FRACUNIT, S_SECRETFLICKY_02_FLAP3, 0},
	{"SECRETFLICKY_02_FLAP3", 0, SPR_FS02, 3, 3, A_FlickyFly,                      4*FRACUNIT,             16*FRACUNIT, S_SECRETFLICKY_02_FLAP1, 0},
	{"SECRETFLICKY_02_STAND", 0, SPR_FS02, FF_ANIMATE|1, -1, NULL, 2, 2, S_NULL, 0},
	{"SECRETFLICKY_02_CENTER", 0, SPR_NULL, 0, 15, A_FlickyCenter, MT_SECRETFLICKY_02, 384*FRACUNIT, S_SECRETFLICKY_02_CENTER, 0},

	// Fan
	{"FAN", 0, SPR_FANS, 0, 1, A_FanBubbleSpawn, 2048, 0, S_FAN2, 0},
	{"FAN2", 0, SPR_FANS, 1, 1, A_FanBubbleSpawn, 1024, 0, S_FAN3, 0},
	{"FAN3", 0, SPR_FANS, 2, 1, A_FanBubbleSpawn,  512, 0, S_FAN4, 0},
	{"FAN4", 0, SPR_FANS, 3, 1, A_FanBubbleSpawn, 1024, 0, S_FAN5, 0},
	{"FAN5", 0, SPR_FANS, 4, 1, A_FanBubbleSpawn,  512, 0, S_FAN, 0},

	// Steam Riser
	{"STEAM1", 0, SPR_STEM, 0, 2, A_SetSolidSteam, 0, 0, S_STEAM2, 0},
	{"STEAM2", 0, SPR_STEM, 1, 2, A_UnsetSolidSteam, 0, 0, S_STEAM3, 0},
	{"STEAM3", 0, SPR_STEM, 2, 2, NULL, 0, 0, S_STEAM4, 0},
	{"STEAM4", 0, SPR_STEM, 3, 2, NULL, 0, 0, S_STEAM5, 0},
	{"STEAM5", 0, SPR_STEM, 4, 2, NULL, 0, 0, S_STEAM6, 0},
	{"STEAM6", 0, SPR_STEM, 5, 2, NULL, 0, 0, S_STEAM7, 0},
	{"STEAM7", 0, SPR_STEM, 6, 2, NULL, 0, 0, S_STEAM8, 0},
	{"STEAM8", 0, SPR_NULL, 0, 18, NULL, 0, 0, S_STEAM1, 0},

	// Bumpers
	{"BUMPER", 0, SPR_BUMP, FF_ANIMATE|FF_GLOBALANIM, -1, NULL,   3, 4, S_NULL, 0},
	{"BUMPERHIT", 0, SPR_BUMP, FF_ANIMATE|4,             12, A_Pain, 1, 3, S_BUMPER, 0},

	// Balloons
	{"BALLOON", 0, SPR_BLON, FF_ANIMATE, -1, NULL, 2, 5, S_NULL, 0},
	{"BALLOONPOP1", 0, SPR_BLON, 3, 0, A_RemoteDamage,   0, 1, S_BALLOONPOP2, 0},
	{"BALLOONPOP2", 0, SPR_BLON, 3, 1, A_Pain,           0, 0, S_BALLOONPOP3, 0},
	{"BALLOONPOP3", 0, SPR_BLON, 4, 1, NULL,             0, 0, S_BALLOONPOP4, 0},
	{"BALLOONPOP4", 0, SPR_NULL, 0, TICRATE, A_CheckFlags2, MF2_AMBUSH, S_BALLOONPOP5, S_NULL, 0},
	{"BALLOONPOP5", 0, SPR_NULL, 0, 15*TICRATE, NULL,    0, 0, S_BALLOONPOP6, 0},
	{"BALLOONPOP6", 0, SPR_NULL, 0, 0, A_SpawnFreshCopy, 0, 0, S_NULL, 0},

	// Yellow Spring
	{"YELLOWSPRING", 0, SPR_SPRY, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"YELLOWSPRING2", 0, SPR_SPRY, 4, 4, A_Pain, 0, 0, S_YELLOWSPRING3, 0},
	{"YELLOWSPRING3", 0, SPR_SPRY, 3, 1, NULL, 0, 0, S_YELLOWSPRING4, 0},
	{"YELLOWSPRING4", 0, SPR_SPRY, 2, 1, NULL, 0, 0, S_YELLOWSPRING5, 0},
	{"YELLOWSPRING5", 0, SPR_SPRY, 1, 1, NULL, 0, 0, S_YELLOWSPRING, 0},

	// Red Spring
	{"REDSPRING", 0, SPR_SPRR, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"REDSPRING2", 0, SPR_SPRR, 4, 4, A_Pain, 0, 0, S_REDSPRING3, 0},
	{"REDSPRING3", 0, SPR_SPRR, 3, 1, NULL, 0, 0, S_REDSPRING4, 0},
	{"REDSPRING4", 0, SPR_SPRR, 2, 1, NULL, 0, 0, S_REDSPRING5, 0},
	{"REDSPRING5", 0, SPR_SPRR, 1, 1, NULL, 0, 0, S_REDSPRING, 0},

	// Blue Spring
	{"BLUESPRING", 0, SPR_SPRB, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"BLUESPRING2", 0, SPR_SPRB, 4, 4, A_Pain, 0, 0, S_BLUESPRING3, 0},
	{"BLUESPRING3", 0, SPR_SPRB, 3, 1, NULL, 0, 0, S_BLUESPRING4, 0},
	{"BLUESPRING4", 0, SPR_SPRB, 2, 1, NULL, 0, 0, S_BLUESPRING5, 0},
	{"BLUESPRING5", 0, SPR_SPRB, 1, 1, NULL, 0, 0, S_BLUESPRING, 0},

	// Yellow Diagonal Spring
	{"YDIAG1", 0, SPR_YSPR, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"YDIAG2", 0, SPR_YSPR, 1, 1, A_Pain, 0, 0, S_YDIAG3, 0},
	{"YDIAG3", 0, SPR_YSPR, 2, 1, NULL, 0, 0, S_YDIAG4, 0},
	{"YDIAG4", 0, SPR_YSPR, 3, 1, NULL, 0, 0, S_YDIAG5, 0},
	{"YDIAG5", 0, SPR_YSPR, 4, 1, NULL, 0, 0, S_YDIAG6, 0},
	{"YDIAG6", 0, SPR_YSPR, 3, 1, NULL, 0, 0, S_YDIAG7, 0},
	{"YDIAG7", 0, SPR_YSPR, 2, 1, NULL, 0, 0, S_YDIAG8, 0},
	{"YDIAG8", 0, SPR_YSPR, 1, 1, NULL, 0, 0, S_YDIAG1, 0},

	// Red Diagonal Spring
	{"RDIAG1", 0, SPR_RSPR, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"RDIAG2", 0, SPR_RSPR, 1, 1, A_Pain, 0, 0, S_RDIAG3, 0},
	{"RDIAG3", 0, SPR_RSPR, 2, 1, NULL, 0, 0, S_RDIAG4, 0},
	{"RDIAG4", 0, SPR_RSPR, 3, 1, NULL, 0, 0, S_RDIAG5, 0},
	{"RDIAG5", 0, SPR_RSPR, 4, 1, NULL, 0, 0, S_RDIAG6, 0},
	{"RDIAG6", 0, SPR_RSPR, 3, 1, NULL, 0, 0, S_RDIAG7, 0},
	{"RDIAG7", 0, SPR_RSPR, 2, 1, NULL, 0, 0, S_RDIAG8, 0},
	{"RDIAG8", 0, SPR_RSPR, 1, 1, NULL, 0, 0, S_RDIAG1, 0},

	// Blue Diagonal Spring
	{"BDIAG1", 0, SPR_BSPR, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"BDIAG2", 0, SPR_BSPR, 1, 1, A_Pain, 0, 0, S_BDIAG3, 0},
	{"BDIAG3", 0, SPR_BSPR, 2, 1, NULL, 0, 0, S_BDIAG4, 0},
	{"BDIAG4", 0, SPR_BSPR, 3, 1, NULL, 0, 0, S_BDIAG5, 0},
	{"BDIAG5", 0, SPR_BSPR, 4, 1, NULL, 0, 0, S_BDIAG6, 0},
	{"BDIAG6", 0, SPR_BSPR, 3, 1, NULL, 0, 0, S_BDIAG7, 0},
	{"BDIAG7", 0, SPR_BSPR, 2, 1, NULL, 0, 0, S_BDIAG8, 0},
	{"BDIAG8", 0, SPR_BSPR, 1, 1, NULL, 0, 0, S_BDIAG1, 0},

	// Yellow Side Spring
	{"YHORIZ1", 0, SPR_SSWY, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"YHORIZ2", 0, SPR_SSWY, 1, 1, A_Pain, 0, 0, S_YHORIZ3, 0},
	{"YHORIZ3", 0, SPR_SSWY, 2, 1, NULL, 0, 0, S_YHORIZ4, 0},
	{"YHORIZ4", 0, SPR_SSWY, 3, 1, NULL, 0, 0, S_YHORIZ5, 0},
	{"YHORIZ5", 0, SPR_SSWY, 4, 1, NULL, 0, 0, S_YHORIZ6, 0},
	{"YHORIZ6", 0, SPR_SSWY, 3, 1, NULL, 0, 0, S_YHORIZ7, 0},
	{"YHORIZ7", 0, SPR_SSWY, 2, 1, NULL, 0, 0, S_YHORIZ8, 0},
	{"YHORIZ8", 0, SPR_SSWY, 1, 1, NULL, 0, 0, S_YHORIZ1, 0},

	// Red Side Spring
	{"RHORIZ1", 0, SPR_SSWR, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"RHORIZ2", 0, SPR_SSWR, 1, 1, A_Pain, 0, 0, S_RHORIZ3, 0},
	{"RHORIZ3", 0, SPR_SSWR, 2, 1, NULL, 0, 0, S_RHORIZ4, 0},
	{"RHORIZ4", 0, SPR_SSWR, 3, 1, NULL, 0, 0, S_RHORIZ5, 0},
	{"RHORIZ5", 0, SPR_SSWR, 4, 1, NULL, 0, 0, S_RHORIZ6, 0},
	{"RHORIZ6", 0, SPR_SSWR, 3, 1, NULL, 0, 0, S_RHORIZ7, 0},
	{"RHORIZ7", 0, SPR_SSWR, 2, 1, NULL, 0, 0, S_RHORIZ8, 0},
	{"RHORIZ8", 0, SPR_SSWR, 1, 1, NULL, 0, 0, S_RHORIZ1, 0},

	// Blue Side Spring
	{"BHORIZ1", 0, SPR_SSWB, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"BHORIZ2", 0, SPR_SSWB, 1, 1, A_Pain, 0, 0, S_BHORIZ3, 0},
	{"BHORIZ3", 0, SPR_SSWB, 2, 1, NULL, 0, 0, S_BHORIZ4, 0},
	{"BHORIZ4", 0, SPR_SSWB, 3, 1, NULL, 0, 0, S_BHORIZ5, 0},
	{"BHORIZ5", 0, SPR_SSWB, 4, 1, NULL, 0, 0, S_BHORIZ6, 0},
	{"BHORIZ6", 0, SPR_SSWB, 3, 1, NULL, 0, 0, S_BHORIZ7, 0},
	{"BHORIZ7", 0, SPR_SSWB, 2, 1, NULL, 0, 0, S_BHORIZ8, 0},
	{"BHORIZ8", 0, SPR_SSWB, 1, 1, NULL, 0, 0, S_BHORIZ1, 0},

	// Boosters
	{"BOOSTERSOUND", 0, SPR_NULL, 0, 1, A_Pain, 0, 0, S_INVISIBLE, 0},
	{"YELLOWBOOSTERROLLER", 0, SPR_BSTY,                  FF_ANIMATE, -1, NULL, 2, 1, S_NULL, 0},
	{"YELLOWBOOSTERSEG_LEFT", 0, SPR_BSTY, 3|FF_PAPERSPRITE|FF_ANIMATE, -1, NULL, 2, 3, S_NULL, 0},
	{"YELLOWBOOSTERSEG_RIGHT", 0, SPR_BSTY, 6|FF_PAPERSPRITE|FF_ANIMATE, -1, NULL, 2, 3, S_NULL, 0},
	{"YELLOWBOOSTERSEG_FACE", 0, SPR_BSTY, 9|FF_PAPERSPRITE,            -1, NULL, 0, 0, S_NULL, 0},
	{"REDBOOSTERROLLER", 0, SPR_BSTR,                  FF_ANIMATE, -1, NULL, 2, 1, S_NULL, 0},
	{"REDBOOSTERSEG_LEFT", 0, SPR_BSTR, 3|FF_PAPERSPRITE|FF_ANIMATE, -1, NULL, 2, 3, S_NULL, 0},
	{"REDBOOSTERSEG_RIGHT", 0, SPR_BSTR, 6|FF_PAPERSPRITE|FF_ANIMATE, -1, NULL, 2, 3, S_NULL, 0},
	{"REDBOOSTERSEG_FACE", 0, SPR_BSTR, 9|FF_PAPERSPRITE,            -1, NULL, 0, 0, S_NULL, 0},

	// Rain
	{"RAIN1", 0, SPR_RAIN, FF_FULLBRIGHT|FF_TRANS50, -1, NULL, 0, 0, S_NULL, 0},
	{"RAINRETURN", 0, SPR_RAIN, FF_FULLBRIGHT|FF_TRANS50, 1, NULL, 0, 0, S_RAIN1, 0},

	// Snowflake
	{"SNOW1", 0, SPR_SNO1, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"SNOW2", 0, SPR_SNO1, 1, -1, NULL, 0, 0, S_NULL, 0},
	{"SNOW3", 0, SPR_SNO1, 2, -1, NULL, 0, 0, S_NULL, 0},

	// Water Splish
	{"SPLISH1", 0, SPR_SPLH, FF_TRANS50  , 2, NULL, 0, 0, S_SPLISH2, 0},
	{"SPLISH2", 0, SPR_SPLH, FF_TRANS50|1, 2, NULL, 0, 0, S_SPLISH3, 0},
	{"SPLISH3", 0, SPR_SPLH, FF_TRANS50|2, 2, NULL, 0, 0, S_SPLISH4, 0},
	{"SPLISH4", 0, SPR_SPLH, FF_TRANS50|3, 2, NULL, 0, 0, S_SPLISH5, 0},
	{"SPLISH5", 0, SPR_SPLH, FF_TRANS50|4, 2, NULL, 0, 0, S_SPLISH6, 0},
	{"SPLISH6", 0, SPR_SPLH, FF_TRANS50|5, 2, NULL, 0, 0, S_SPLISH7, 0},
	{"SPLISH7", 0, SPR_SPLH, FF_TRANS50|6, 2, NULL, 0, 0, S_SPLISH8, 0},
	{"SPLISH8", 0, SPR_SPLH, FF_TRANS50|7, 2, NULL, 0, 0, S_SPLISH9, 0},
	{"SPLISH9", 0, SPR_SPLH, FF_TRANS50|8, 2, NULL, 0, 0, S_NULL, 0},

	// Lava splish
	{"LAVASPLISH", 0, SPR_LSPL, FF_ANIMATE, 16, NULL, 7, 2, S_NULL, 0},

	// Water Splash
	{"SPLASH1", 0, SPR_SPLA, FF_TRANS50  , 3, NULL, 0, 0, S_SPLASH2, 0},
	{"SPLASH2", 0, SPR_SPLA, FF_TRANS70|1, 3, NULL, 0, 0, S_SPLASH3, 0},
	{"SPLASH3", 0, SPR_SPLA, FF_TRANS90|2, 3, NULL, 0, 0, S_RAINRETURN, 0},

	// Smoke
	{"SMOKE1", 0, SPR_SMOK, FF_TRANS50  , 4, NULL, 0, 0, S_SMOKE2, 0},
	{"SMOKE2", 0, SPR_SMOK, FF_TRANS50|1, 5, NULL, 0, 0, S_SMOKE3, 0},
	{"SMOKE3", 0, SPR_SMOK, FF_TRANS50|2, 6, NULL, 0, 0, S_SMOKE4, 0},
	{"SMOKE4", 0, SPR_SMOK, FF_TRANS50|3, 7, NULL, 0, 0, S_SMOKE5, 0},
	{"SMOKE5", 0, SPR_SMOK, FF_TRANS50|4, 8, NULL, 0, 0, S_NULL, 0},

	// Bubbles
	{"SMALLBUBBLE", 0, SPR_BUBL, FF_TRANS50,   1, A_BubbleRise, 0, 1024, S_SMALLBUBBLE, 0},
	{"MEDIUMBUBBLE", 0, SPR_BUBL, FF_TRANS50|1, 1, A_BubbleRise, 0, 1024, S_MEDIUMBUBBLE, 0},

	// Extra Large Bubble (breathable)
	{"LARGEBUBBLE1", 0, SPR_BUBL, FF_TRANS50|FF_FULLBRIGHT|2,   8, A_BubbleRise, 0, 1024, S_LARGEBUBBLE2, 0},
	{"LARGEBUBBLE2", 0, SPR_BUBL, FF_TRANS50|FF_FULLBRIGHT|3,   8, A_BubbleRise, 0, 1024, S_EXTRALARGEBUBBLE, 0},
	{"EXTRALARGEBUBBLE", 0, SPR_BUBL, FF_TRANS50|FF_FULLBRIGHT|4,  16, A_BubbleRise, 0, 1024, S_EXTRALARGEBUBBLE, 0},

	// Extra Large Bubble goes POP!
	{"POP1", 0, SPR_BUBL, 5, 16, NULL, 0, 0, S_NULL, 0},

	{"WATERZAP", 0, SPR_WZAP, FF_TRANS10|FF_ANIMATE|FF_RANDOMANIM, 4, NULL, 3, 2, S_NULL, 0},

	// Spindash dust
	{"SPINDUST1", 0, SPR_DUST,                          0, 7, NULL, 0, 0, S_SPINDUST2, 0},
	{"SPINDUST2", 0, SPR_DUST,                          1, 6, NULL, 0, 0, S_SPINDUST3, 0},
	{"SPINDUST3", 0, SPR_DUST,               FF_TRANS30|2, 4, NULL, 0, 0, S_SPINDUST4, 0},
	{"SPINDUST4", 0, SPR_DUST,               FF_TRANS60|3, 3, NULL, 0, 0, S_NULL, 0},
	{"SPINDUST_BUBBLE1", 0, SPR_BUBL,                          0, 7, NULL, 0, 0, S_SPINDUST_BUBBLE2, 0},
	{"SPINDUST_BUBBLE2", 0, SPR_BUBL,                          0, 6, NULL, 0, 0, S_SPINDUST_BUBBLE3, 0},
	{"SPINDUST_BUBBLE3", 0, SPR_BUBL,               FF_TRANS30|0, 4, NULL, 0, 0, S_SPINDUST_BUBBLE4, 0},
	{"SPINDUST_BUBBLE4", 0, SPR_BUBL,               FF_TRANS60|0, 3, NULL, 0, 0, S_NULL, 0},
	{"SPINDUST_FIRE1", 0, SPR_FPRT,            FF_FULLBRIGHT|0, 7, NULL, 0, 0, S_SPINDUST_FIRE2, 0},
	{"SPINDUST_FIRE2", 0, SPR_FPRT,            FF_FULLBRIGHT|0, 6, NULL, 0, 0, S_SPINDUST_FIRE3, 0},
	{"SPINDUST_FIRE3", 0, SPR_FPRT, FF_FULLBRIGHT|FF_TRANS30|0, 4, NULL, 0, 0, S_SPINDUST_FIRE4, 0},
	{"SPINDUST_FIRE4", 0, SPR_FPRT, FF_FULLBRIGHT|FF_TRANS60|0, 3, NULL, 0, 0, S_NULL, 0},


	{"FOG1", 0, SPR_TFOG, FF_FULLBRIGHT|FF_TRANS50,    2, NULL, 0, 0, S_FOG2, 0},
	{"FOG2", 0, SPR_TFOG, FF_FULLBRIGHT|FF_TRANS50|1,  2, NULL, 0, 0, S_FOG3, 0},
	{"FOG3", 0, SPR_TFOG, FF_FULLBRIGHT|FF_TRANS50|2,  2, NULL, 0, 0, S_FOG4, 0},
	{"FOG4", 0, SPR_TFOG, FF_FULLBRIGHT|FF_TRANS50|3,  2, NULL, 0, 0, S_FOG5, 0},
	{"FOG5", 0, SPR_TFOG, FF_FULLBRIGHT|FF_TRANS50|4,  2, NULL, 0, 0, S_FOG6, 0},
	{"FOG6", 0, SPR_TFOG, FF_FULLBRIGHT|FF_TRANS50|5,  2, NULL, 0, 0, S_FOG7, 0},
	{"FOG7", 0, SPR_TFOG, FF_FULLBRIGHT|FF_TRANS50|6,  2, NULL, 0, 0, S_FOG8, 0},
	{"FOG8", 0, SPR_TFOG, FF_FULLBRIGHT|FF_TRANS50|7,  2, NULL, 0, 0, S_FOG9, 0},
	{"FOG9", 0, SPR_TFOG, FF_FULLBRIGHT|FF_TRANS50|8,  2, NULL, 0, 0, S_FOG10, 0},
	{"FOG10", 0, SPR_TFOG, FF_FULLBRIGHT|FF_TRANS50|9,  2, NULL, 0, 0, S_FOG11, 0},
	{"FOG11", 0, SPR_TFOG, FF_FULLBRIGHT|FF_TRANS50|10, 2, NULL, 0, 0, S_FOG12, 0},
	{"FOG12", 0, SPR_TFOG, FF_FULLBRIGHT|FF_TRANS50|11, 2, NULL, 0, 0, S_FOG13, 0},
	{"FOG13", 0, SPR_TFOG, FF_FULLBRIGHT|FF_TRANS50|12, 2, NULL, 0, 0, S_FOG14, 0},
	{"FOG14", 0, SPR_TFOG, FF_FULLBRIGHT|FF_TRANS50|13, 2, NULL, 0, 0, S_NULL, 0},

	// Flower Seed
	{"SEED", 0, SPR_SEED, FF_FULLBRIGHT|FF_ANIMATE, -1, NULL, 2, 2, S_NULL, 0},

	// Particle sprite
	{"PARTICLE", 0, SPR_PRTL, 0, 2*TICRATE, NULL, 0, 0, S_NULL, 0},

	{"SCRA", 0, SPR_SCOR, 0, 32, A_ScoreRise, 0, 0, S_NULL, 0},   // - 100
	{"SCRB", 0, SPR_SCOR, 1, 32, A_ScoreRise, 0, 0, S_NULL, 0},   // - 200
	{"SCRC", 0, SPR_SCOR, 2, 32, A_ScoreRise, 0, 0, S_NULL, 0},   // - 500
	{"SCRD", 0, SPR_SCOR, 3, 32, A_ScoreRise, 0, 0, S_NULL, 0},   // - 1000
	{"SCRE", 0, SPR_SCOR, 4, 32, A_ScoreRise, 0, 0, S_NULL, 0},   // - 10000
	{"SCRF", 0, SPR_SCOR, 5, 32, A_ScoreRise, 0, 0, S_NULL, 0},   // - 400 (mario mode)
	{"SCRG", 0, SPR_SCOR, 6, 32, A_ScoreRise, 0, 0, S_NULL, 0},   // - 800 (mario mode)
	{"SCRH", 0, SPR_SCOR, 7, 32, A_ScoreRise, 0, 0, S_NULL, 0},   // - 2000 (mario mode)
	{"SCRI", 0, SPR_SCOR, 8, 32, A_ScoreRise, 0, 0, S_NULL, 0},   // - 4000 (mario mode)
	{"SCRJ", 0, SPR_SCOR, 9, 32, A_ScoreRise, 0, 0, S_NULL, 0},   // - 8000 (mario mode)
	{"SCRK", 0, SPR_SCOR, 10, 32, A_ScoreRise, 0, 0, S_NULL, 0},  // - 1UP (mario mode)
	{"SCRL", 0, SPR_SCOR, 11, 32, A_ScoreRise, 0, 0, S_NULL, 0},  // - 10

	// Drowning Timer Numbers
	{"ZERO1", 0, SPR_DRWN, 0, 40, NULL, 0, 0, S_NULL, 0},
	{"ONE1", 0, SPR_DRWN, 1, 40, NULL, 0, 0, S_NULL, 0},
	{"TWO1", 0, SPR_DRWN, 2, 40, NULL, 0, 0, S_NULL, 0},
	{"THREE1", 0, SPR_DRWN, 3, 40, NULL, 0, 0, S_NULL, 0},
	{"FOUR1", 0, SPR_DRWN, 4, 40, NULL, 0, 0, S_NULL, 0},
	{"FIVE1", 0, SPR_DRWN, 5, 40, NULL, 0, 0, S_NULL, 0},

	{"ZERO2", 0, SPR_DRWN,  6, 40, NULL, 0, 0, S_NULL, 0},
	{"ONE2", 0, SPR_DRWN,  7, 40, NULL, 0, 0, S_NULL, 0},
	{"TWO2", 0, SPR_DRWN,  8, 40, NULL, 0, 0, S_NULL, 0},
	{"THREE2", 0, SPR_DRWN,  9, 40, NULL, 0, 0, S_NULL, 0},
	{"FOUR2", 0, SPR_DRWN, 10, 40, NULL, 0, 0, S_NULL, 0},
	{"FIVE2", 0, SPR_DRWN, 11, 40, NULL, 0, 0, S_NULL, 0},

	// Flight indicator
	{"FLIGHTINDICATOR", 0, SPR_FLII, FF_FULLBRIGHT|FF_ANIMATE|0, -1, NULL, 4, 4, S_NULL, 0},

	{"LOCKON1", 0, SPR_LCKN,   FF_FULLBRIGHT, 2, NULL, 0, 0, S_NULL, 0},
	{"LOCKON2", 0, SPR_LCKN, 1|FF_FULLBRIGHT, 2, NULL, 0, 0, S_NULL, 0},
	{"LOCKON3", 0, SPR_LCKN, 2|FF_FULLBRIGHT, 2, NULL, 0, 0, S_NULL, 0},
	{"LOCKON4", 0, SPR_LCKN, 3|FF_FULLBRIGHT, 2, NULL, 0, 0, S_NULL, 0},

	{"LOCKONINF1", 0, SPR_LCKN,   FF_FULLBRIGHT, -1, NULL, 0, 0, S_NULL, 0},
	{"LOCKONINF2", 0, SPR_LCKN, 1|FF_FULLBRIGHT, -1, NULL, 0, 0, S_NULL, 0},
	{"LOCKONINF3", 0, SPR_LCKN, 2|FF_FULLBRIGHT, -1, NULL, 0, 0, S_NULL, 0},
	{"LOCKONINF4", 0, SPR_LCKN, 3|FF_FULLBRIGHT, -1, NULL, 0, 0, S_NULL, 0},

	{"TTAG", 0, SPR_TTAG, FF_FULLBRIGHT, 1, NULL, 0, 0, S_NULL, 0},

	// CTF Sign
	{"GOTFLAG", 0, SPR_GFLG, FF_FULLBRIGHT, 1, NULL, 0, 0, S_NULL, 0},

	// Finish flag
	{"FINISHFLAG", 0, SPR_FNSF,    FF_TRANS30, -1, NULL, 0, 0, S_NULL, 0},

	{"CORK", 0, SPR_CORK,             0, -1, NULL, 0, 0, S_NULL, 0},
	{"LHRT", 0, SPR_LHRT, FF_FULLBRIGHT, -1, NULL, 0, 0, S_NULL, 0},

	// Red Rings (thrown)
	{"RRNG1", 0, SPR_RRNG, FF_FULLBRIGHT,   1, A_ThrownRing, 0, 0, S_RRNG2, 0},
	{"RRNG2", 0, SPR_RRNG, FF_FULLBRIGHT|1, 1, A_ThrownRing, 0, 0, S_RRNG3, 0},
	{"RRNG3", 0, SPR_RRNG, FF_FULLBRIGHT|2, 1, A_ThrownRing, 0, 0, S_RRNG4, 0},
	{"RRNG4", 0, SPR_RRNG, FF_FULLBRIGHT|3, 1, A_ThrownRing, 0, 0, S_RRNG5, 0},
	{"RRNG5", 0, SPR_RRNG, FF_FULLBRIGHT|4, 1, A_ThrownRing, 0, 0, S_RRNG6, 0},
	{"RRNG6", 0, SPR_RRNG, FF_FULLBRIGHT|5, 1, A_ThrownRing, 0, 0, S_RRNG7, 0},
	{"RRNG7", 0, SPR_RRNG, FF_FULLBRIGHT|6, 1, A_ThrownRing, 0, 0, S_RRNG1, 0},

	// Weapon Ring Ammo
	{"BOUNCERINGAMMO", 0, SPR_RNGB, FF_ANIMATE|FF_GLOBALANIM, -1, NULL, 34, 1, S_BOUNCERINGAMMO, 0},
	{"RAILRINGAMMO", 0, SPR_RNGR, FF_ANIMATE|FF_GLOBALANIM, -1, NULL, 34, 1, S_RAILRINGAMMO, 0},
	{"INFINITYRINGAMMO", 0, SPR_RNGI, FF_ANIMATE|FF_GLOBALANIM, -1, NULL, 34, 1, S_INFINITYRINGAMMO, 0},
	{"AUTOMATICRINGAMMO", 0, SPR_RNGA, FF_ANIMATE|FF_GLOBALANIM, -1, NULL, 34, 1, S_AUTOMATICRINGAMMO, 0},
	{"EXPLOSIONRINGAMMO", 0, SPR_RNGE, FF_ANIMATE|FF_GLOBALANIM, -1, NULL, 34, 1, S_EXPLOSIONRINGAMMO, 0},
	{"SCATTERRINGAMMO", 0, SPR_RNGS, FF_ANIMATE|FF_GLOBALANIM, -1, NULL, 34, 1, S_SCATTERRINGAMMO, 0},
	{"GRENADERINGAMMO", 0, SPR_RNGG, FF_ANIMATE|FF_GLOBALANIM, -1, NULL, 34, 1, S_GRENADERINGAMMO, 0},

	// Bounce Ring Pickup
	{"BOUNCEPICKUP", 0, SPR_PIKB, FF_ANIMATE|FF_GLOBALANIM, -1, NULL, 15, 1, S_BOUNCEPICKUP, 0},

	{"BOUNCEPICKUPFADE1", 0, SPR_PIKB,  0, 1, NULL, 0, 0, S_BOUNCEPICKUPFADE2, 0},
	{"BOUNCEPICKUPFADE2", 0, SPR_PIKB,  2, 1, NULL, 0, 0, S_BOUNCEPICKUPFADE3, 0},
	{"BOUNCEPICKUPFADE3", 0, SPR_PIKB,  4, 1, NULL, 0, 0, S_BOUNCEPICKUPFADE4, 0},
	{"BOUNCEPICKUPFADE4", 0, SPR_PIKB,  6, 1, NULL, 0, 0, S_BOUNCEPICKUPFADE5, 0},
	{"BOUNCEPICKUPFADE5", 0, SPR_PIKB,  8, 1, NULL, 0, 0, S_BOUNCEPICKUPFADE6, 0},
	{"BOUNCEPICKUPFADE6", 0, SPR_PIKB, 10, 1, NULL, 0, 0, S_BOUNCEPICKUPFADE7, 0},
	{"BOUNCEPICKUPFADE7", 0, SPR_PIKB, 12, 1, NULL, 0, 0, S_BOUNCEPICKUPFADE8, 0},
	{"BOUNCEPICKUPFADE8", 0, SPR_PIKB, 14, 1, NULL, 0, 0, S_BOUNCEPICKUPFADE1, 0},

	// Rail Ring Pickup
	{"RAILPICKUP", 0, SPR_PIKR, FF_ANIMATE|FF_GLOBALANIM, -1, NULL, 15, 1, S_RAILPICKUP, 0},

	{"RAILPICKUPFADE1", 0, SPR_PIKR,  0, 1, NULL, 0, 0, S_RAILPICKUPFADE2, 0},
	{"RAILPICKUPFADE2", 0, SPR_PIKR,  2, 1, NULL, 0, 0, S_RAILPICKUPFADE3, 0},
	{"RAILPICKUPFADE3", 0, SPR_PIKR,  4, 1, NULL, 0, 0, S_RAILPICKUPFADE4, 0},
	{"RAILPICKUPFADE4", 0, SPR_PIKR,  6, 1, NULL, 0, 0, S_RAILPICKUPFADE5, 0},
	{"RAILPICKUPFADE5", 0, SPR_PIKR,  8, 1, NULL, 0, 0, S_RAILPICKUPFADE6, 0},
	{"RAILPICKUPFADE6", 0, SPR_PIKR, 10, 1, NULL, 0, 0, S_RAILPICKUPFADE7, 0},
	{"RAILPICKUPFADE7", 0, SPR_PIKR, 12, 1, NULL, 0, 0, S_RAILPICKUPFADE8, 0},
	{"RAILPICKUPFADE8", 0, SPR_PIKR, 14, 1, NULL, 0, 0, S_RAILPICKUPFADE1, 0},

	// Auto Ring Pickup
	{"AUTOPICKUP", 0, SPR_PIKA, FF_ANIMATE|FF_GLOBALANIM, -1, NULL, 15, 1, S_AUTOPICKUP, 0},

	{"AUTOPICKUPFADE1", 0, SPR_PIKA,  0, 1, NULL, 0, 0, S_AUTOPICKUPFADE2, 0},
	{"AUTOPICKUPFADE2", 0, SPR_PIKA,  2, 1, NULL, 0, 0, S_AUTOPICKUPFADE3, 0},
	{"AUTOPICKUPFADE3", 0, SPR_PIKA,  4, 1, NULL, 0, 0, S_AUTOPICKUPFADE4, 0},
	{"AUTOPICKUPFADE4", 0, SPR_PIKA,  6, 1, NULL, 0, 0, S_AUTOPICKUPFADE5, 0},
	{"AUTOPICKUPFADE5", 0, SPR_PIKA,  8, 1, NULL, 0, 0, S_AUTOPICKUPFADE6, 0},
	{"AUTOPICKUPFADE6", 0, SPR_PIKA, 10, 1, NULL, 0, 0, S_AUTOPICKUPFADE7, 0},
	{"AUTOPICKUPFADE7", 0, SPR_PIKA, 12, 1, NULL, 0, 0, S_AUTOPICKUPFADE8, 0},
	{"AUTOPICKUPFADE8", 0, SPR_PIKA, 14, 1, NULL, 0, 0, S_AUTOPICKUPFADE1, 0},

	// Explode Ring Pickup
	{"EXPLODEPICKUP", 0, SPR_PIKE, FF_ANIMATE|FF_GLOBALANIM, -1, NULL, 15, 1, S_EXPLODEPICKUP, 0},

	{"EXPLODEPICKUPFADE1", 0, SPR_PIKE,  0, 1, NULL, 0, 0, S_EXPLODEPICKUPFADE2, 0},
	{"EXPLODEPICKUPFADE2", 0, SPR_PIKE,  2, 1, NULL, 0, 0, S_EXPLODEPICKUPFADE3, 0},
	{"EXPLODEPICKUPFADE3", 0, SPR_PIKE,  4, 1, NULL, 0, 0, S_EXPLODEPICKUPFADE4, 0},
	{"EXPLODEPICKUPFADE4", 0, SPR_PIKE,  6, 1, NULL, 0, 0, S_EXPLODEPICKUPFADE5, 0},
	{"EXPLODEPICKUPFADE5", 0, SPR_PIKE,  8, 1, NULL, 0, 0, S_EXPLODEPICKUPFADE6, 0},
	{"EXPLODEPICKUPFADE6", 0, SPR_PIKE, 10, 1, NULL, 0, 0, S_EXPLODEPICKUPFADE7, 0},
	{"EXPLODEPICKUPFADE7", 0, SPR_PIKE, 12, 1, NULL, 0, 0, S_EXPLODEPICKUPFADE8, 0},
	{"EXPLODEPICKUPFADE8", 0, SPR_PIKE, 14, 1, NULL, 0, 0, S_EXPLODEPICKUPFADE1, 0},

	// Scatter Ring Pickup
	{"SCATTERPICKUP", 0, SPR_PIKS,  FF_ANIMATE|FF_GLOBALANIM, -1, NULL, 15, 1, S_SCATTERPICKUP, 0},

	{"SCATTERPICKUPFADE1", 0, SPR_PIKS,  0, 1, NULL, 0, 0, S_SCATTERPICKUPFADE2, 0},
	{"SCATTERPICKUPFADE2", 0, SPR_PIKS,  2, 1, NULL, 0, 0, S_SCATTERPICKUPFADE3, 0},
	{"SCATTERPICKUPFADE3", 0, SPR_PIKS,  4, 1, NULL, 0, 0, S_SCATTERPICKUPFADE4, 0},
	{"SCATTERPICKUPFADE4", 0, SPR_PIKS,  6, 1, NULL, 0, 0, S_SCATTERPICKUPFADE5, 0},
	{"SCATTERPICKUPFADE5", 0, SPR_PIKS,  8, 1, NULL, 0, 0, S_SCATTERPICKUPFADE6, 0},
	{"SCATTERPICKUPFADE6", 0, SPR_PIKS, 10, 1, NULL, 0, 0, S_SCATTERPICKUPFADE7, 0},
	{"SCATTERPICKUPFADE7", 0, SPR_PIKS, 12, 1, NULL, 0, 0, S_SCATTERPICKUPFADE8, 0},
	{"SCATTERPICKUPFADE8", 0, SPR_PIKS, 14, 1, NULL, 0, 0, S_SCATTERPICKUPFADE1, 0},

	// Grenade Ring Pickup
	{"GRENADEPICKUP", 0, SPR_PIKG,  FF_ANIMATE|FF_GLOBALANIM, -1, NULL, 15, 1, S_GRENADEPICKUP, 0},

	{"GRENADEPICKUPFADE1", 0, SPR_PIKG,  0, 1, NULL, 0, 0, S_GRENADEPICKUPFADE2, 0},
	{"GRENADEPICKUPFADE2", 0, SPR_PIKG,  2, 1, NULL, 0, 0, S_GRENADEPICKUPFADE3, 0},
	{"GRENADEPICKUPFADE3", 0, SPR_PIKG,  4, 1, NULL, 0, 0, S_GRENADEPICKUPFADE4, 0},
	{"GRENADEPICKUPFADE4", 0, SPR_PIKG,  6, 1, NULL, 0, 0, S_GRENADEPICKUPFADE5, 0},
	{"GRENADEPICKUPFADE5", 0, SPR_PIKG,  8, 1, NULL, 0, 0, S_GRENADEPICKUPFADE6, 0},
	{"GRENADEPICKUPFADE6", 0, SPR_PIKG, 10, 1, NULL, 0, 0, S_GRENADEPICKUPFADE7, 0},
	{"GRENADEPICKUPFADE7", 0, SPR_PIKG, 12, 1, NULL, 0, 0, S_GRENADEPICKUPFADE8, 0},
	{"GRENADEPICKUPFADE8", 0, SPR_PIKG, 14, 1, NULL, 0, 0, S_GRENADEPICKUPFADE1, 0},

	// Thrown Weapon Rings
	{"THROWNBOUNCE1", 0, SPR_RNGB, FF_FULLBRIGHT   , 1, A_ThrownRing, 0, 0, S_THROWNBOUNCE2, 0},
	{"THROWNBOUNCE2", 0, SPR_RNGB, FF_FULLBRIGHT| 5, 1, A_ThrownRing, 0, 0, S_THROWNBOUNCE3, 0},
	{"THROWNBOUNCE3", 0, SPR_RNGB, FF_FULLBRIGHT|10, 1, A_ThrownRing, 0, 0, S_THROWNBOUNCE4, 0},
	{"THROWNBOUNCE4", 0, SPR_RNGB, FF_FULLBRIGHT|15, 1, A_ThrownRing, 0, 0, S_THROWNBOUNCE5, 0},
	{"THROWNBOUNCE5", 0, SPR_RNGB, FF_FULLBRIGHT|20, 1, A_ThrownRing, 0, 0, S_THROWNBOUNCE6, 0},
	{"THROWNBOUNCE6", 0, SPR_RNGB, FF_FULLBRIGHT|25, 1, A_ThrownRing, 0, 0, S_THROWNBOUNCE7, 0},
	{"THROWNBOUNCE7", 0, SPR_RNGB, FF_FULLBRIGHT|30, 1, A_ThrownRing, 0, 0, S_THROWNBOUNCE1, 0},

	{"THROWNINFINITY1", 0, SPR_RNGI, FF_FULLBRIGHT   , 1, A_ThrownRing, 0, 0, S_THROWNINFINITY2, 0},
	{"THROWNINFINITY2", 0, SPR_RNGI, FF_FULLBRIGHT| 5, 1, A_ThrownRing, 0, 0, S_THROWNINFINITY3, 0},
	{"THROWNINFINITY3", 0, SPR_RNGI, FF_FULLBRIGHT|10, 1, A_ThrownRing, 0, 0, S_THROWNINFINITY4, 0},
	{"THROWNINFINITY4", 0, SPR_RNGI, FF_FULLBRIGHT|15, 1, A_ThrownRing, 0, 0, S_THROWNINFINITY5, 0},
	{"THROWNINFINITY5", 0, SPR_RNGI, FF_FULLBRIGHT|20, 1, A_ThrownRing, 0, 0, S_THROWNINFINITY6, 0},
	{"THROWNINFINITY6", 0, SPR_RNGI, FF_FULLBRIGHT|25, 1, A_ThrownRing, 0, 0, S_THROWNINFINITY7, 0},
	{"THROWNINFINITY7", 0, SPR_RNGI, FF_FULLBRIGHT|30, 1, A_ThrownRing, 0, 0, S_THROWNINFINITY1, 0},

	{"THROWNAUTOMATIC1", 0, SPR_TAUT, FF_FULLBRIGHT  , 1, A_ThrownRing, 0, 0, S_THROWNAUTOMATIC2, 0},
	{"THROWNAUTOMATIC2", 0, SPR_TAUT, FF_FULLBRIGHT|1, 1, A_ThrownRing, 0, 0, S_THROWNAUTOMATIC3, 0},
	{"THROWNAUTOMATIC3", 0, SPR_TAUT, FF_FULLBRIGHT|2, 1, A_ThrownRing, 0, 0, S_THROWNAUTOMATIC4, 0},
	{"THROWNAUTOMATIC4", 0, SPR_TAUT, FF_FULLBRIGHT|3, 1, A_ThrownRing, 0, 0, S_THROWNAUTOMATIC5, 0},
	{"THROWNAUTOMATIC5", 0, SPR_TAUT, FF_FULLBRIGHT|4, 1, A_ThrownRing, 0, 0, S_THROWNAUTOMATIC6, 0},
	{"THROWNAUTOMATIC6", 0, SPR_TAUT, FF_FULLBRIGHT|5, 1, A_ThrownRing, 0, 0, S_THROWNAUTOMATIC7, 0},
	{"THROWNAUTOMATIC7", 0, SPR_TAUT, FF_FULLBRIGHT|6, 1, A_ThrownRing, 0, 0, S_THROWNAUTOMATIC1, 0},

	{"THROWNEXPLOSION1", 0, SPR_RNGE, FF_FULLBRIGHT   , 1, A_ThrownRing, 0, 0, S_THROWNEXPLOSION2, 0},
	{"THROWNEXPLOSION2", 0, SPR_RNGE, FF_FULLBRIGHT| 5, 1, A_ThrownRing, 0, 0, S_THROWNEXPLOSION3, 0},
	{"THROWNEXPLOSION3", 0, SPR_RNGE, FF_FULLBRIGHT|10, 1, A_ThrownRing, 0, 0, S_THROWNEXPLOSION4, 0},
	{"THROWNEXPLOSION4", 0, SPR_RNGE, FF_FULLBRIGHT|15, 1, A_ThrownRing, 0, 0, S_THROWNEXPLOSION5, 0},
	{"THROWNEXPLOSION5", 0, SPR_RNGE, FF_FULLBRIGHT|20, 1, A_ThrownRing, 0, 0, S_THROWNEXPLOSION6, 0},
	{"THROWNEXPLOSION6", 0, SPR_RNGE, FF_FULLBRIGHT|25, 1, A_ThrownRing, 0, 0, S_THROWNEXPLOSION7, 0},
	{"THROWNEXPLOSION7", 0, SPR_RNGE, FF_FULLBRIGHT|30, 1, A_ThrownRing, 0, 0, S_THROWNEXPLOSION1, 0},

	{"THROWNGRENADE1", 0, SPR_TGRE, FF_FULLBRIGHT   , 1, A_ThrownRing, 0, 0, S_THROWNGRENADE2, 0},
	{"THROWNGRENADE2", 0, SPR_TGRE, FF_FULLBRIGHT| 1, 1, A_ThrownRing, 0, 0, S_THROWNGRENADE3, 0},
	{"THROWNGRENADE3", 0, SPR_TGRE, FF_FULLBRIGHT| 2, 1, A_ThrownRing, 0, 0, S_THROWNGRENADE4, 0},
	{"THROWNGRENADE4", 0, SPR_TGRE, FF_FULLBRIGHT| 3, 1, A_ThrownRing, 0, 0, S_THROWNGRENADE5, 0},
	{"THROWNGRENADE5", 0, SPR_TGRE, FF_FULLBRIGHT| 4, 1, A_ThrownRing, 0, 0, S_THROWNGRENADE6, 0},
	{"THROWNGRENADE6", 0, SPR_TGRE, FF_FULLBRIGHT| 5, 1, A_ThrownRing, 0, 0, S_THROWNGRENADE7, 0},
	{"THROWNGRENADE7", 0, SPR_TGRE, FF_FULLBRIGHT| 6, 1, A_ThrownRing, 0, 0, S_THROWNGRENADE8, 0},
	{"THROWNGRENADE8", 0, SPR_TGRE, FF_FULLBRIGHT| 7, 1, A_ThrownRing, 0, 0, S_THROWNGRENADE9, 0},
	{"THROWNGRENADE9", 0, SPR_TGRE, FF_FULLBRIGHT| 8, 1, A_ThrownRing, 0, 0, S_THROWNGRENADE10, 0},
	{"THROWNGRENADE10", 0, SPR_TGRE, FF_FULLBRIGHT| 9, 1, A_ThrownRing, 0, 0, S_THROWNGRENADE11, 0},
	{"THROWNGRENADE11", 0, SPR_TGRE, FF_FULLBRIGHT|10, 1, A_ThrownRing, 0, 0, S_THROWNGRENADE12, 0},
	{"THROWNGRENADE12", 0, SPR_TGRE, FF_FULLBRIGHT|11, 1, A_ThrownRing, 0, 0, S_THROWNGRENADE13, 0},
	{"THROWNGRENADE13", 0, SPR_TGRE, FF_FULLBRIGHT|12, 1, A_ThrownRing, 0, 0, S_THROWNGRENADE14, 0},
	{"THROWNGRENADE14", 0, SPR_TGRE, FF_FULLBRIGHT|13, 1, A_ThrownRing, 0, 0, S_THROWNGRENADE15, 0},
	{"THROWNGRENADE15", 0, SPR_TGRE, FF_FULLBRIGHT|14, 1, A_ThrownRing, 0, 0, S_THROWNGRENADE16, 0},
	{"THROWNGRENADE16", 0, SPR_TGRE, FF_FULLBRIGHT|15, 1, A_ThrownRing, 0, 0, S_THROWNGRENADE17, 0},
	{"THROWNGRENADE17", 0, SPR_TGRE, FF_FULLBRIGHT|16, 1, A_ThrownRing, 0, 0, S_THROWNGRENADE18, 0},
	{"THROWNGRENADE18", 0, SPR_TGRE, FF_FULLBRIGHT|17, 1, A_ThrownRing, 0, 0, S_THROWNGRENADE1, 0},

	{"THROWNSCATTER", 0, SPR_TSCR, FF_FULLBRIGHT, 1, A_ThrownRing, 0, 0, S_THROWNSCATTER, 0},

	{"RINGEXPLODE", 0, SPR_NULL, 0, 1, A_RingExplode, 0, 0, S_XPLD1, 0},

	// Coin
	{"COIN1", 0, SPR_COIN, FF_FULLBRIGHT,   5, NULL, 0, 0, S_COIN2, 0},
	{"COIN2", 0, SPR_COIN, FF_FULLBRIGHT|1, 5, NULL, 0, 0, S_COIN3, 0},
	{"COIN3", 0, SPR_COIN, FF_FULLBRIGHT|2, 5, NULL, 0, 0, S_COIN1, 0},

	// Coin Sparkle
	{"COINSPARKLE1", 0, SPR_CPRK, FF_FULLBRIGHT,   5, NULL, 0, 0, S_COINSPARKLE2, 0},
	{"COINSPARKLE2", 0, SPR_CPRK, FF_FULLBRIGHT|1, 5, NULL, 0, 0, S_COINSPARKLE3, 0},
	{"COINSPARKLE3", 0, SPR_CPRK, FF_FULLBRIGHT|2, 5, NULL, 0, 0, S_COINSPARKLE4, 0},
	{"COINSPARKLE4", 0, SPR_CPRK, FF_FULLBRIGHT|3, 5, NULL, 0, 0, S_NULL, 0},        

	// Goomba
	{"GOOMBA1", 0, SPR_GOOM, 0, 6, A_Look, 0, 0, S_GOOMBA1B, 0},
	{"GOOMBA1B", 0, SPR_GOOM, 1, 6, A_Look, 0, 0, S_GOOMBA1, 0}, 
	{"GOOMBA2", 0, SPR_GOOM, 0, 3, A_Chase, 0, 0, S_GOOMBA3, 0},
	{"GOOMBA3", 0, SPR_GOOM, 0, 3, A_Chase, 0, 0, S_GOOMBA4, 0},
	{"GOOMBA4", 0, SPR_GOOM, 1, 3, A_Chase, 0, 0, S_GOOMBA5, 0},
	{"GOOMBA5", 0, SPR_GOOM, 1, 3, A_Chase, 0, 0, S_GOOMBA6, 0},
	{"GOOMBA6", 0, SPR_GOOM, 0, 3, A_Chase, 0, 0, S_GOOMBA7, 0},
	{"GOOMBA7", 0, SPR_GOOM, 0, 3, A_Chase, 0, 0, S_GOOMBA8, 0},
	{"GOOMBA8", 0, SPR_GOOM, 1, 3, A_Chase, 0, 0, S_GOOMBA9, 0},
	{"GOOMBA9", 0, SPR_GOOM, 1, 3, A_Chase, 0, 0, S_GOOMBA2, 0},
	{"GOOMBA_DEAD", 0, SPR_GOOM, 2, 16, A_Scream, 0, 0, S_NULL, 0}, 

	// Blue Goomba
	{"BLUEGOOMBA1", 0, SPR_BGOM, 0, 6, A_Look, 0, 0, S_BLUEGOOMBA1B, 0},
	{"BLUEGOOMBA1B", 0, SPR_BGOM, 1, 6, A_Look, 0, 0, S_BLUEGOOMBA1, 0}, 
	{"BLUEGOOMBA2", 0, SPR_BGOM, 0, 3, A_Chase, 0, 0, S_BLUEGOOMBA3, 0},
	{"BLUEGOOMBA3", 0, SPR_BGOM, 0, 3, A_Chase, 0, 0, S_BLUEGOOMBA4, 0},
	{"BLUEGOOMBA4", 0, SPR_BGOM, 1, 3, A_Chase, 0, 0, S_BLUEGOOMBA5, 0},
	{"BLUEGOOMBA5", 0, SPR_BGOM, 1, 3, A_Chase, 0, 0, S_BLUEGOOMBA6, 0},
	{"BLUEGOOMBA6", 0, SPR_BGOM, 0, 3, A_Chase, 0, 0, S_BLUEGOOMBA7, 0},
	{"BLUEGOOMBA7", 0, SPR_BGOM, 0, 3, A_Chase, 0, 0, S_BLUEGOOMBA8, 0},
	{"BLUEGOOMBA8", 0, SPR_BGOM, 1, 3, A_Chase, 0, 0, S_BLUEGOOMBA9, 0},
	{"BLUEGOOMBA9", 0, SPR_BGOM, 1, 3, A_Chase, 0, 0, S_BLUEGOOMBA2, 0},
	{"BLUEGOOMBA_DEAD", 0, SPR_BGOM, 2, 16, A_Scream, 0, 0, S_NULL, 0},

	// Fire Flower
	{"FIREFLOWER1", 0, SPR_FFWR, 0, 3, NULL, 0, 0, S_FIREFLOWER2, 0},
	{"FIREFLOWER2", 0, SPR_FFWR, 1, 3, NULL, 0, 0, S_FIREFLOWER3, 0},
	{"FIREFLOWER3", 0, SPR_FFWR, 2, 3, NULL, 0, 0, S_FIREFLOWER4, 0},
	{"FIREFLOWER4", 0, SPR_FFWR, 3, 3, NULL, 0, 0, S_FIREFLOWER1, 0},

	// Thrown Mario Fireball
	{"FIREBALL", 0, SPR_FBLL, FF_FULLBRIGHT,   1, A_SpawnObjectRelative, 0, MT_FIREBALLTRAIL, S_FIREBALL, 0},
	{"FIREBALLTRAIL1", 0, SPR_FBLL, 1|FF_FULLBRIGHT|FF_TRANS50, 1, A_SetScale, FRACUNIT*3/4, 0, S_FIREBALLTRAIL2, 0},
	{"FIREBALLTRAIL2", 0, SPR_FBLL, 1|FF_FULLBRIGHT|FF_TRANS50, 8, A_SetScale, FRACUNIT/6, 1, S_NULL, 0},

	// Turtle Shell
	{"SHELL", 0, SPR_SHLL, 0, -1, NULL, 0, 0, S_NULL, 0},

	// Puma (Mario fireball)
	{"PUMA_START1", 0, SPR_PUMA, FF_FULLBRIGHT|2, 1, A_FishJump, 0, MT_PUMATRAIL, S_PUMA_START2, 0},
	{"PUMA_START2", 0, SPR_PUMA, FF_FULLBRIGHT|2, 1, A_PlaySound, sfx_s3k70, 1 + (1<<16), S_PUMA_UP1, 0},
	{"PUMA_UP1", 0, SPR_PUMA, FF_FULLBRIGHT  , 2, A_FishJump, 0, MT_PUMATRAIL, S_PUMA_UP2, 0},
	{"PUMA_UP2", 0, SPR_PUMA, FF_FULLBRIGHT|1, 2, A_FishJump, 0, MT_PUMATRAIL, S_PUMA_UP3, 0},
	{"PUMA_UP3", 0, SPR_PUMA, FF_FULLBRIGHT|2, 2, A_FishJump, 0, MT_PUMATRAIL, S_PUMA_UP1, 0},
	{"PUMA_DOWN1", 0, SPR_PUMA, FF_FULLBRIGHT|3, 2, A_FishJump, 0, MT_PUMATRAIL, S_PUMA_DOWN2, 0},
	{"PUMA_DOWN2", 0, SPR_PUMA, FF_FULLBRIGHT|4, 2, A_FishJump, 0, MT_PUMATRAIL, S_PUMA_DOWN3, 0},
	{"PUMA_DOWN3", 0, SPR_PUMA, FF_FULLBRIGHT|5, 2, A_FishJump, 0, MT_PUMATRAIL, S_PUMA_DOWN1, 0},

	{"PUMATRAIL1", 0, SPR_PUMA, FF_FULLBRIGHT|FF_TRANS20|6, 4,       NULL,        0, 0, S_PUMATRAIL2, 0},
	{"PUMATRAIL2", 0, SPR_PUMA, FF_FULLBRIGHT|FF_TRANS40|6, 5, A_SetScale, FRACUNIT, 1, S_PUMATRAIL3, 0},
	{"PUMATRAIL3", 0, SPR_PUMA, FF_FULLBRIGHT|FF_TRANS50|7, 4,       NULL,        0, 0, S_PUMATRAIL4, 0},
	{"PUMATRAIL4", 0, SPR_PUMA, FF_FULLBRIGHT|FF_TRANS60|8, 3,       NULL,        0, 0, S_NULL, 0},

	// Hammer
	{"HAMMER", 0, SPR_HAMM, FF_ANIMATE, -1, NULL, 3, 3, S_NULL, 0},

	// Koopa
	{"KOOPA1", 0, SPR_KOOP, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"KOOPA2", 0, SPR_KOOP, 1, 24, NULL, 0, 0, S_KOOPA1, 0},

	{"KOOPAFLAME1", 0, SPR_BFLM, 0, 3,NULL, 0, 0, S_KOOPAFLAME2, 0},
	{"KOOPAFLAME2", 0, SPR_BFLM, 1, 3,NULL, 0, 0, S_KOOPAFLAME3, 0},
	{"KOOPAFLAME3", 0, SPR_BFLM, 2, 3,NULL, 0, 0, S_KOOPAFLAME1, 0},

	// Axe
	{"AXE1", 0, SPR_MAXE, 0, 3, NULL, 0, 0, S_AXE2, 0},
	{"AXE2", 0, SPR_MAXE, 1, 3, NULL, 0, 0, S_AXE3, 0},
	{"AXE3", 0, SPR_MAXE, 2, 3, NULL, 0, 0, S_AXE1, 0},

	{"MARIOBUSH1", 0, SPR_MUS1, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"MARIOBUSH2", 0, SPR_MUS2, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"TOAD", 0, SPR_TOAD, 0, -1, NULL, 0, 0, S_NULL, 0},

	// Nights Drone
	{"NIGHTSDRONE_MAN1", 0, SPR_NDRN, 0, -1, NULL, 0, 0, S_NIGHTSDRONE_MAN2, 0},
	{"NIGHTSDRONE_MAN2", 0, SPR_NDRN, 0, -1, NULL, 0, 0, S_NIGHTSDRONE_MAN1, 0},

	// Sparkling point (RETURN TO THE GOAL, etc)
	{"NIGHTSDRONE_SPARKLING1", 0, SPR_IVSP, 0, 1, A_GhostMe, 0, 0, S_NIGHTSDRONE_SPARKLING2, 0},
	{"NIGHTSDRONE_SPARKLING2", 0, SPR_IVSP, 2, 1, A_GhostMe, 0, 0, S_NIGHTSDRONE_SPARKLING3, 0},
	{"NIGHTSDRONE_SPARKLING3", 0, SPR_IVSP, 4, 1, A_GhostMe, 0, 0, S_NIGHTSDRONE_SPARKLING4, 0},
	{"NIGHTSDRONE_SPARKLING4", 0, SPR_IVSP, 6, 1, A_GhostMe, 0, 0, S_NIGHTSDRONE_SPARKLING5, 0},
	{"NIGHTSDRONE_SPARKLING5", 0, SPR_IVSP, 8, 1, A_GhostMe, 0, 0, S_NIGHTSDRONE_SPARKLING6, 0},
	{"NIGHTSDRONE_SPARKLING6", 0, SPR_IVSP, 10, 1, A_GhostMe, 0, 0, S_NIGHTSDRONE_SPARKLING7, 0},
	{"NIGHTSDRONE_SPARKLING7", 0, SPR_IVSP, 12, 1, A_GhostMe, 0, 0, S_NIGHTSDRONE_SPARKLING8, 0},
	{"NIGHTSDRONE_SPARKLING8", 0, SPR_IVSP, 14, 1, A_GhostMe, 0, 0, S_NIGHTSDRONE_SPARKLING9, 0},
	{"NIGHTSDRONE_SPARKLING9", 0, SPR_IVSP, 16, 1, A_GhostMe, 0, 0, S_NIGHTSDRONE_SPARKLING10, 0},
	{"NIGHTSDRONE_SPARKLING10", 0, SPR_IVSP, 18, 1, A_GhostMe, 0, 0, S_NIGHTSDRONE_SPARKLING11, 0},
	{"NIGHTSDRONE_SPARKLING11", 0, SPR_IVSP, 20, 1, A_GhostMe, 0, 0, S_NIGHTSDRONE_SPARKLING12, 0},
	{"NIGHTSDRONE_SPARKLING12", 0, SPR_IVSP, 22, 1, A_GhostMe, 0, 0, S_NIGHTSDRONE_SPARKLING13, 0},
	{"NIGHTSDRONE_SPARKLING13", 0, SPR_IVSP, 24, 1, A_GhostMe, 0, 0, S_NIGHTSDRONE_SPARKLING14, 0},
	{"NIGHTSDRONE_SPARKLING14", 0, SPR_IVSP, 26, 1, A_GhostMe, 0, 0, S_NIGHTSDRONE_SPARKLING15, 0},
	{"NIGHTSDRONE_SPARKLING15", 0, SPR_IVSP, 28, 1, A_GhostMe, 0, 0, S_NIGHTSDRONE_SPARKLING16, 0},
	{"NIGHTSDRONE_SPARKLING16", 0, SPR_IVSP, 30, 1, A_GhostMe, 0, 0, S_NIGHTSDRONE_SPARKLING1, 0},

	// NiGHTS GOAL banner (inside the sparkles!)
	{"NIGHTSDRONE_GOAL1", 0, SPR_GOAL, 0, 4, NULL, 0, 0, S_NIGHTSDRONE_GOAL2, 0},
	{"NIGHTSDRONE_GOAL2", 0, SPR_GOAL, 1, 4, NULL, 0, 0, S_NIGHTSDRONE_GOAL3, 0},
	{"NIGHTSDRONE_GOAL3", 0, SPR_GOAL, 2, 4, NULL, 0, 0, S_NIGHTSDRONE_GOAL4, 0},
	{"NIGHTSDRONE_GOAL4", 0, SPR_GOAL, 3, 4, NULL, 0, 0, S_NIGHTSDRONE_GOAL1, 0},

	// Nights Sparkle
	{"NIGHTSPARKLE1", 0, SPR_NSPK, FF_FULLBRIGHT, 140, NULL, 0, 0, S_NIGHTSPARKLE2, 0},
	{"NIGHTSPARKLE2", 0, SPR_NSPK, FF_FULLBRIGHT|1, 7, NULL, 0, 0, S_NIGHTSPARKLE3, 0},
	{"NIGHTSPARKLE3", 0, SPR_NSPK, FF_FULLBRIGHT|2, 7, NULL, 0, 0, S_NIGHTSPARKLE4, 0},
	{"NIGHTSPARKLE4", 0, SPR_NSPK, FF_FULLBRIGHT|3, 7, NULL, 0, 0, S_NULL, 0},

	// Red Sparkle
	{"NIGHTSPARKLESUPER1", 0, SPR_NSPK, FF_FULLBRIGHT|4, 140, NULL, 0, 0, S_NIGHTSPARKLESUPER2, 0},
	{"NIGHTSPARKLESUPER2", 0, SPR_NSPK, FF_FULLBRIGHT|5, 7, NULL, 0, 0, S_NIGHTSPARKLESUPER3, 0},
	{"NIGHTSPARKLESUPER3", 0, SPR_NSPK, FF_FULLBRIGHT|6, 7, NULL, 0, 0, S_NIGHTSPARKLESUPER4, 0},
	{"NIGHTSPARKLESUPER4", 0, SPR_NSPK, FF_FULLBRIGHT|7, 7, NULL, 0, 0, S_NULL, 0},

	// Paraloop helper -- THIS IS WHAT DETERMINES THE TIMER NOW
	{"NIGHTSLOOPHELPER", 0, SPR_NULL, 0, 160, NULL, 0, 0, S_NULL, 0},

	// NiGHTS bumper
	{"NIGHTSBUMPER1", 0, SPR_NBMP, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"NIGHTSBUMPER2", 0, SPR_NBMP, 1, -1, NULL, 0, 0, S_NULL, 0},
	{"NIGHTSBUMPER3", 0, SPR_NBMP, 2, -1, NULL, 0, 0, S_NULL, 0},
	{"NIGHTSBUMPER4", 0, SPR_NBMP, 3, -1, NULL, 0, 0, S_NULL, 0},
	{"NIGHTSBUMPER5", 0, SPR_NBMP, 4, -1, NULL, 0, 0, S_NULL, 0},
	{"NIGHTSBUMPER6", 0, SPR_NBMP, 5, -1, NULL, 0, 0, S_NULL, 0},
	{"NIGHTSBUMPER7", 0, SPR_NBMP, 6, -1, NULL, 0, 0, S_NULL, 0},
	{"NIGHTSBUMPER8", 0, SPR_NBMP, 7, -1, NULL, 0, 0, S_NULL, 0},
	{"NIGHTSBUMPER9", 0, SPR_NBMP, 8, -1, NULL, 0, 0, S_NULL, 0},
	{"NIGHTSBUMPER10", 0, SPR_NBMP, 9, -1, NULL, 0, 0, S_NULL, 0},
	{"NIGHTSBUMPER11", 0, SPR_NBMP, 10, -1, NULL, 0, 0, S_NULL, 0},
	{"NIGHTSBUMPER12", 0, SPR_NBMP, 11, -1, NULL, 0, 0, S_NULL, 0},

	{"HOOP", 0, SPR_HOOP, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"HOOP_XMASA", 0, SPR_HOOP, 1, -1, NULL, 0, 0, S_NULL, 0},
	{"HOOP_XMASB", 0, SPR_HOOP, 2, -1, NULL, 0, 0, S_NULL, 0},

	{"NIGHTSCORE10", 0, SPR_NSCR, FF_FULLBRIGHT,    -1, NULL, 0, 0, S_NULL, 0},
	{"NIGHTSCORE20", 0, SPR_NSCR, FF_FULLBRIGHT|1,  -1, NULL, 0, 0, S_NULL, 0},
	{"NIGHTSCORE30", 0, SPR_NSCR, FF_FULLBRIGHT|2,  -1, NULL, 0, 0, S_NULL, 0},
	{"NIGHTSCORE40", 0, SPR_NSCR, FF_FULLBRIGHT|3,  -1, NULL, 0, 0, S_NULL, 0},
	{"NIGHTSCORE50", 0, SPR_NSCR, FF_FULLBRIGHT|4,  -1, NULL, 0, 0, S_NULL, 0},
	{"NIGHTSCORE60", 0, SPR_NSCR, FF_FULLBRIGHT|5,  -1, NULL, 0, 0, S_NULL, 0},
	{"NIGHTSCORE70", 0, SPR_NSCR, FF_FULLBRIGHT|6,  -1, NULL, 0, 0, S_NULL, 0},
	{"NIGHTSCORE80", 0, SPR_NSCR, FF_FULLBRIGHT|7,  -1, NULL, 0, 0, S_NULL, 0},
	{"NIGHTSCORE90", 0, SPR_NSCR, FF_FULLBRIGHT|8,  -1, NULL, 0, 0, S_NULL, 0},
	{"NIGHTSCORE100", 0, SPR_NSCR, FF_FULLBRIGHT|9,  -1, NULL, 0, 0, S_NULL, 0},
	{"NIGHTSCORE10_2", 0, SPR_NSCR, FF_FULLBRIGHT|10, -1, NULL, 0, 0, S_NULL, 0},
	{"NIGHTSCORE20_2", 0, SPR_NSCR, FF_FULLBRIGHT|11, -1, NULL, 0, 0, S_NULL, 0},
	{"NIGHTSCORE30_2", 0, SPR_NSCR, FF_FULLBRIGHT|12, -1, NULL, 0, 0, S_NULL, 0},
	{"NIGHTSCORE40_2", 0, SPR_NSCR, FF_FULLBRIGHT|13, -1, NULL, 0, 0, S_NULL, 0},
	{"NIGHTSCORE50_2", 0, SPR_NSCR, FF_FULLBRIGHT|14, -1, NULL, 0, 0, S_NULL, 0},
	{"NIGHTSCORE60_2", 0, SPR_NSCR, FF_FULLBRIGHT|15, -1, NULL, 0, 0, S_NULL, 0},
	{"NIGHTSCORE70_2", 0, SPR_NSCR, FF_FULLBRIGHT|16, -1, NULL, 0, 0, S_NULL, 0},
	{"NIGHTSCORE80_2", 0, SPR_NSCR, FF_FULLBRIGHT|17, -1, NULL, 0, 0, S_NULL, 0},
	{"NIGHTSCORE90_2", 0, SPR_NSCR, FF_FULLBRIGHT|18, -1, NULL, 0, 0, S_NULL, 0},
	{"NIGHTSCORE100_2", 0, SPR_NSCR, FF_FULLBRIGHT|19, -1, NULL, 0, 0, S_NULL, 0},

	// NiGHTS Paraloop Powerups
	{"NIGHTSSUPERLOOP", 0, SPR_NPRU, 0, -1, NULL, 0, 0, S_NULL, 0},
	{"NIGHTSDRILLREFILL", 0, SPR_NPRU, 1, -1, NULL, 0, 0, S_NULL, 0},
	{"NIGHTSHELPER", 0, SPR_NPRU, 2, -1, NULL, 0, 0, S_NULL, 0},
	{"NIGHTSEXTRATIME", 0, SPR_NPRU, 3, -1, NULL, 0, 0, S_NULL, 0},
	{"NIGHTSLINKFREEZE", 0, SPR_NPRU, 4, -1, NULL, 0, 0, S_NULL, 0},

	{"EGGCAPSULE", 0, SPR_CAPS, 0, -1, NULL, 0, 0, S_NULL, 0},

	// Orbiting Chaos Emeralds/Ideya for NiGHTS
	{"ORBITEM1", 0, SPR_CEMG, FF_FULLBRIGHT,   1, A_OrbitNights, ANG2*2, 0, S_ORBITEM1, 0},
	{"ORBITEM2", 0, SPR_CEMG, FF_FULLBRIGHT|1, 1, A_OrbitNights, ANG2*2, 0, S_ORBITEM2, 0},
	{"ORBITEM3", 0, SPR_CEMG, FF_FULLBRIGHT|2, 1, A_OrbitNights, ANG2*2, 0, S_ORBITEM3, 0},
	{"ORBITEM4", 0, SPR_CEMG, FF_FULLBRIGHT|3, 1, A_OrbitNights, ANG2*2, 0, S_ORBITEM4, 0},
	{"ORBITEM5", 0, SPR_CEMG, FF_FULLBRIGHT|4, 1, A_OrbitNights, ANG2*2, 0, S_ORBITEM5, 0},
	{"ORBITEM6", 0, SPR_CEMG, FF_FULLBRIGHT|5, 1, A_OrbitNights, ANG2*2, 0, S_ORBITEM6, 0},
	{"ORBITEM7", 0, SPR_CEMG, FF_FULLBRIGHT|6, 1, A_OrbitNights, ANG2*2, 0, S_ORBITEM7, 0},
	{"ORBITEM8", 0, SPR_CEMG, FF_FULLBRIGHT|7, 1, A_OrbitNights, ANG2*2, 0, S_ORBITEM8, 0},
	{"ORBIDYA1", 0, SPR_IDYA, FF_TRANS20|FF_FULLBRIGHT,   1, A_OrbitNights, ANG2*2, 0, S_ORBIDYA1, 0},
	{"ORBIDYA2", 0, SPR_IDYA, FF_TRANS20|FF_FULLBRIGHT|1, 1, A_OrbitNights, ANG2*2, 0, S_ORBIDYA2, 0},
	{"ORBIDYA3", 0, SPR_IDYA, FF_TRANS20|FF_FULLBRIGHT|2, 1, A_OrbitNights, ANG2*2, 0, S_ORBIDYA3, 0},
	{"ORBIDYA4", 0, SPR_IDYA, FF_TRANS20|FF_FULLBRIGHT|3, 1, A_OrbitNights, ANG2*2, 0, S_ORBIDYA4, 0},
	{"ORBIDYA5", 0, SPR_IDYA, FF_TRANS20|FF_FULLBRIGHT|4, 1, A_OrbitNights, ANG2*2, 0, S_ORBIDYA5, 0},

	// Flicky helper for NiGHTS
	{"NIGHTOPIANHELPER1", 0, SPR_FL01, 1, 1, A_OrbitNights, ANG2*2, 180 | 0x10000, S_NIGHTOPIANHELPER2, 0},
	{"NIGHTOPIANHELPER2", 0, SPR_FL01, 1, 1, A_OrbitNights, ANG2*2, 180 | 0x10000, S_NIGHTOPIANHELPER3, 0},
	{"NIGHTOPIANHELPER3", 0, SPR_FL01, 1, 1, A_OrbitNights, ANG2*2, 180 | 0x10000, S_NIGHTOPIANHELPER4, 0},
	{"NIGHTOPIANHELPER4", 0, SPR_FL01, 2, 1, A_OrbitNights, ANG2*2, 180 | 0x10000, S_NIGHTOPIANHELPER5, 0},
	{"NIGHTOPIANHELPER5", 0, SPR_FL01, 2, 1, A_OrbitNights, ANG2*2, 180 | 0x10000, S_NIGHTOPIANHELPER6, 0},
	{"NIGHTOPIANHELPER6", 0, SPR_FL01, 2, 1, A_OrbitNights, ANG2*2, 180 | 0x10000, S_NIGHTOPIANHELPER7, 0},
	{"NIGHTOPIANHELPER7", 0, SPR_FL01, 3, 1, A_OrbitNights, ANG2*2, 180 | 0x10000, S_NIGHTOPIANHELPER8, 0},
	{"NIGHTOPIANHELPER8", 0, SPR_FL01, 3, 1, A_OrbitNights, ANG2*2, 180 | 0x10000, S_NIGHTOPIANHELPER9, 0},
	{"NIGHTOPIANHELPER9", 0, SPR_FL01, 3, 1, A_OrbitNights, ANG2*2, 180 | 0x10000, S_NIGHTOPIANHELPER1, 0},

	// Nightopian
	{"PIAN_LOOK1", 0, SPR_NTPN, 0, 2, A_Look, 1, 1, S_PIAN_LOOK2, 0},
	{"PIAN_LOOK2", 0, SPR_NTPN, 1, 2, A_Look, 1, 1, S_PIAN_LOOK3, 0},
	{"PIAN_LOOK3", 0, SPR_NTPN, 2, 2, A_Look, 1, 1, S_PIAN_LOOK1, 0},
	{"PIAN_FLY1", 0, SPR_NTPN, 0, 2, A_JetgThink, 0, 0, S_PIAN_FLY2, 0},
	{"PIAN_FLY2", 0, SPR_NTPN, 1, 2, NULL, 0, 0, S_PIAN_FLY3, 0},
	{"PIAN_FLY3", 0, SPR_NTPN, 2, 2, NULL, 0, 0, S_PIAN_FLY1, 0},
	{"PIAN_SING", 0, SPR_NTPN, 3|FF_ANIMATE, 24, NULL, 2, 2, S_PIAN_FLY1, 0},

	// Shleep
	{"SHLEEP1", 0, SPR_SHLP, 0, 15, NULL, 0, 0, S_SHLEEP2, 0},
	{"SHLEEP2", 0, SPR_SHLP, 1, 15, NULL, 0, 0, S_SHLEEP3, 0},
	{"SHLEEP3", 0, SPR_SHLP, 2, 15, NULL, 0, 0, S_SHLEEP4, 0},
	{"SHLEEP4", 0, SPR_SHLP, 1, 15, NULL, 0, 0, S_SHLEEP1, 0},
	{"SHLEEPBOUNCE1", 0, SPR_SHLP, 3, 1, A_Scream,  0, 0, S_SHLEEPBOUNCE2, 0},
	{"SHLEEPBOUNCE2", 0, SPR_SHLP, 3, 1, A_ZThrust, 9, 0, S_SHLEEPBOUNCE3, 0},
	{"SHLEEPBOUNCE3", 0, SPR_SHLP, 3, 400, A_SetObjectFlags, MF_SLIDEME|MF_ENEMY|MF_BOUNCE|MF_NOCLIP|MF_NOCLIPHEIGHT, 0, S_NULL, 0},

	// Secret badniks and hazards, shhhh
	{"PENGUINATOR_LOOK", 0, SPR_PENG, 0, 2, A_Look,  0, 0, S_PENGUINATOR_LOOK, 0},
	{"PENGUINATOR_WADDLE1", 0, SPR_PENG, 0, 2, A_Chase, 0, 0, S_PENGUINATOR_WADDLE2, 0},
	{"PENGUINATOR_WADDLE2", 0, SPR_PENG, 1, 2, A_Chase, 0, 0, S_PENGUINATOR_WADDLE3, 0},
	{"PENGUINATOR_WADDLE3", 0, SPR_PENG, 0, 2, A_Chase, 0, 0, S_PENGUINATOR_WADDLE4, 0},
	{"PENGUINATOR_WADDLE4", 0, SPR_PENG, 2, 2, A_Chase, 0, 0, S_PENGUINATOR_WADDLE1, 0},
	{"PENGUINATOR_SLIDE1", 0, SPR_PENG, 0,  0, A_FaceTarget,      0,  0, S_PENGUINATOR_SLIDE2, 0},
	{"PENGUINATOR_SLIDE2", 0, SPR_PENG, 3,  5, A_BunnyHop,        4, 10, S_PENGUINATOR_SLIDE3, 0},
	{"PENGUINATOR_SLIDE3", 0, SPR_PENG, 4, 90, A_PlayAttackSound, 0,  0, S_PENGUINATOR_SLIDE4, 0},
	{"PENGUINATOR_SLIDE4", 0, SPR_PENG, 3,  5, A_Thrust,          0,  1, S_PENGUINATOR_SLIDE5, 0},
	{"PENGUINATOR_SLIDE5", 0, SPR_PENG, 0,  5, A_FaceTarget,      0,  0, S_PENGUINATOR_LOOK, 0},

	{"POPHAT_LOOK", 0, SPR_POPH, 0,  2, A_Look,  (2048<<16)|1,           0, S_POPHAT_LOOK, 0},
	{"POPHAT_SHOOT1", 0, SPR_POPH, 1,  0, A_MultiShotDist, (MT_SPINDUST<<16)|4, 24, S_POPHAT_SHOOT2, 0},
	{"POPHAT_SHOOT2", 0, SPR_POPH, 1,  2, A_LobShot, MT_POPSHOT, (70<<16)|60, S_POPHAT_SHOOT3, 0},
	{"POPHAT_SHOOT3", 0, SPR_POPH, 2,  1, NULL,               0,           0, S_POPHAT_SHOOT4, 0},
	{"POPHAT_SHOOT4", 0, SPR_POPH, 0, 57, NULL,               0,           0, S_POPHAT_LOOK, 0},
	{"POPSHOT", 0, SPR_POPH, 3,  3, A_SpawnObjectRelative, 0, MT_POPSHOT_TRAIL, S_POPSHOT, 0},
	{"POPSHOT_TRAIL", 0, SPR_NULL, 0,  2, NULL,                  0, 0,                S_SPINDUST1, 0},

	{"HIVEELEMENTAL_LOOK", 0, SPR_HIVE, 0,  5, A_Look, 1, 1, S_HIVEELEMENTAL_LOOK, 0},
	{"HIVEELEMENTAL_PREPARE1", 0, SPR_HIVE, 0, 14, A_PlaySound, sfx_s3k76, 1, S_HIVEELEMENTAL_PREPARE2, 0},
	{"HIVEELEMENTAL_PREPARE2", 0, SPR_HIVE, 0,  6, A_PlaySound, sfx_s3k8c, 1, S_HIVEELEMENTAL_SHOOT1, 0},
	{"HIVEELEMENTAL_SHOOT1", 0, SPR_HIVE, 1,  4, A_WhoCaresIfYourSonIsABee, (MT_BUMBLEBORE<<16)|4, (1<<16)|32, S_HIVEELEMENTAL_SHOOT2, 0},
	{"HIVEELEMENTAL_SHOOT2", 0, SPR_HIVE, 2,  2, NULL, 0, 0, S_HIVEELEMENTAL_DORMANT, 0},
	{"HIVEELEMENTAL_DORMANT", 0, SPR_HIVE, 0,  5, A_ParentTriesToSleep, S_HIVEELEMENTAL_PREPARE1, 0, S_HIVEELEMENTAL_DORMANT, 0},
	{"HIVEELEMENTAL_PAIN", 0, SPR_HIVE, 3, 35, A_Pain, 0, 0, S_HIVEELEMENTAL_LOOK, 0},
	{"HIVEELEMENTAL_DIE1", 0, SPR_HIVE, 3,  2, A_BossScream, 1, 0, S_HIVEELEMENTAL_DIE2, 0},
	{"HIVEELEMENTAL_DIE2", 0, SPR_NULL, 0,  2, A_BossScream, 1, 0, S_HIVEELEMENTAL_DIE3, 0},
	{"HIVEELEMENTAL_DIE3", 0, SPR_NULL, 0,  0, A_Repeat, 7, S_HIVEELEMENTAL_DIE1, S_XPLD_FLICKY, 0},

	{"BUMBLEBORE_SPAWN", 0, SPR_BUMB, 1, 10, NULL, 0, 0, S_BUMBLEBORE_LOOK1, 0},
	{"BUMBLEBORE_LOOK1", 0, SPR_BUMB, 0,  4, A_Look, 1, 1, S_BUMBLEBORE_LOOK2, 0},
	{"BUMBLEBORE_LOOK2", 0, SPR_BUMB, 1,  4, A_Look, 1, 1, S_BUMBLEBORE_LOOK1, 0},
	{"BUMBLEBORE_FLY1", 0, SPR_BUMB, 0,  4, A_JetbThink, 0, 0, S_BUMBLEBORE_FLY2, 0},
	{"BUMBLEBORE_FLY2", 0, SPR_BUMB, 1,  4, A_JetbThink, 0, 0, S_BUMBLEBORE_FLY1, 0},
	{"BUMBLEBORE_RAISE", 0, SPR_BUMB, 2|FF_FULLBRIGHT,  12, A_ZThrust,  4, (1<<16)|1, S_BUMBLEBORE_FALL1, 0},
	{"BUMBLEBORE_FALL1", 0, SPR_BUMB, 2|FF_FULLBRIGHT,   0, A_ZThrust, -8, (1<<16)|1, S_BUMBLEBORE_FALL2, 0},
	{"BUMBLEBORE_FALL2", 0, SPR_BUMB, 2|FF_FULLBRIGHT, 300, NULL,       0,         0, S_BUMBLEBORE_DIE, 0},
	{"BUMBLEBORE_STUCK1", 0, SPR_BUMB, 4, 3, A_MultiShotDist, (MT_DUST<<16)|6, -40, S_BUMBLEBORE_STUCK2, 0},
	{"BUMBLEBORE_STUCK2", 0, SPR_BUMB, 5, 120, NULL, 0, 0, S_BUMBLEBORE_DIE, 0},
	{"BUMBLEBORE_DIE", 0, SPR_BUMB, 5, 0, A_CryingToMomma, 0, 0, S_XPLD1, 0},

	{"BUGGLEIDLE", 0, SPR_BBUZ,          0, -1, NULL, 0, 0, S_NULL, 0},
	{"BUGGLEFLY", 0, SPR_BBUZ, FF_ANIMATE, -1, NULL, 1, 2, S_NULL, 0},

	{"SMASHSPIKE_FLOAT", 0, SPR_FMCE, 0, 20, NULL, 0, 0, S_SMASHSPIKE_EASE1, 0},
	{"SMASHSPIKE_EASE1", 0, SPR_FMCE, 0,  4, A_ZThrust,  4, (1<<16)|1, S_SMASHSPIKE_EASE2, 0},
	{"SMASHSPIKE_EASE2", 0, SPR_FMCE, 0,  4, A_ZThrust,  0, (1<<16)|1, S_SMASHSPIKE_FALL, 0},
	{"SMASHSPIKE_FALL", 0, SPR_FMCE, 0,  2, A_ZThrust, -6,         1, S_SMASHSPIKE_FALL, 0},
	{"SMASHSPIKE_STOMP1", 0, SPR_FMCE, 1,  2, A_MultiShotDist, (MT_DUST<<16)|10, -48, S_SMASHSPIKE_STOMP2, 0},
	{"SMASHSPIKE_STOMP2", 0, SPR_FMCE, 2, 14, NULL, 0, 0, S_SMASHSPIKE_RISE1, 0},
	{"SMASHSPIKE_RISE1", 0, SPR_FMCE, 1,  2, NULL, 0, 0, S_SMASHSPIKE_RISE2, 0},
	{"SMASHSPIKE_RISE2", 0, SPR_FMCE, 0,  2, A_ZThrust, 6, (1<<16)|1, S_SMASHSPIKE_RISE2, 0},

	{"CACO_LOOK", 0, SPR_CACO, 0,  5, A_Look, (1100<<16)|1, 0, S_CACO_LOOK, 0},
	{"CACO_WAKE1", 0, SPR_CACO, 1,  0, A_MultiShotDist, (MT_DUST<<16)|7, -48, S_CACO_WAKE2, 0},
	{"CACO_WAKE2", 0, SPR_CACO, 1, 10, A_ZThrust, 4, (1<<16)|1, S_CACO_WAKE3, 0},
	{"CACO_WAKE3", 0, SPR_CACO, 2,  8, A_ZThrust, 2, (1<<16)|1, S_CACO_WAKE4, 0},
	{"CACO_WAKE4", 0, SPR_CACO, 2,  4, A_ZThrust, 0, (1<<16)|1, S_CACO_ROAR, 0},
	{"CACO_ROAR", 0, SPR_CACO, 2, 10, A_PlayActiveSound, 0, 0, S_CACO_CHASE, 0},
	{"CACO_CHASE", 0, SPR_CACO, 2,  5, A_JetChase, 0, 0, S_CACO_CHASE_REPEAT, 0},
	{"CACO_CHASE_REPEAT", 0, SPR_CACO, 2,  0, A_Repeat, 5, S_CACO_CHASE, S_CACO_RANDOM, 0},
	{"CACO_RANDOM", 0, SPR_CACO, 2,  0, A_RandomState, S_CACO_PREPARE_SOUND, S_CACO_CHASE, S_CACO_RANDOM, 0},
	{"CACO_PREPARE_SOUND", 0, SPR_CACO, 2,  8, A_PlaySound, sfx_s3k95, 1, S_CACO_PREPARE1, 0},
	{"CACO_PREPARE1", 0, SPR_CACO, 3,               8, NULL, 0, 0, S_CACO_PREPARE2, 0},
	{"CACO_PREPARE2", 0, SPR_CACO, 4|FF_FULLBRIGHT, 8, NULL, 0, 0, S_CACO_PREPARE3, 0},
	{"CACO_PREPARE3", 0, SPR_CACO, 5|FF_FULLBRIGHT, 8, NULL, 0, 0, S_CACO_SHOOT_SOUND, 0},
	{"CACO_SHOOT_SOUND", 0, SPR_CACO, 4|FF_FULLBRIGHT, 0, A_PlaySound, sfx_s3k4e, 1, S_CACO_SHOOT1, 0},
	{"CACO_SHOOT1", 0, SPR_CACO, 4|FF_FULLBRIGHT, 0, A_SpawnParticleRelative, 0, S_CACOFIRE_EXPLODE1, S_CACO_SHOOT2, 0},
	{"CACO_SHOOT2", 0, SPR_CACO, 4|FF_FULLBRIGHT, 6, A_FireShot, MT_CACOFIRE, -24, S_CACO_CLOSE, 0},
	{"CACO_CLOSE", 0, SPR_CACO, 3,              15, NULL, 0, 0, S_CACO_CHASE, 0},
	{"CACO_DIE_FLAGS", 0, SPR_CACO, 10, 0, A_SetObjectFlags, MF_NOBLOCKMAP, 0, S_CACO_DIE_GIB1, 0},
	{"CACO_DIE_GIB1", 0, SPR_CACO, 10, 0, A_NapalmScatter, (7<<16)|MT_CACOSHARD, (30<<16)|20, S_CACO_DIE_GIB2, 0},
	{"CACO_DIE_GIB2", 0, SPR_CACO, 10, 0, A_NapalmScatter, (10<<16)|MT_CACOSHARD, (24<<16)|32, S_CACO_DIE_SCREAM, 0},
	{"CACO_DIE_SCREAM", 0, SPR_CACO, 10, 0, A_Scream, 0, 0, S_CACO_DIE_SHATTER, 0},
	{"CACO_DIE_SHATTER", 0, SPR_CACO, 10, 0, A_PlaySound, sfx_pumpkn, 1, S_CACO_DIE_FALL, 0},
	{"CACO_DIE_FALL", 0, SPR_CACO, 10, 250, A_FlickySpawn, (1<<16), 0, S_NULL, 0},

	{"CACOSHARD_RANDOMIZE", 0, SPR_CACO, 6, 0, A_RandomState, S_CACOSHARD1_1, S_CACOSHARD2_1, S_NULL, 0},
	{"CACOSHARD1_1", 0, SPR_CACO, 6, 3, NULL, 0, 0, S_CACOSHARD1_2, 0},
	{"CACOSHARD1_2", 0, SPR_CACO, 7, 3, NULL, 0, 0, S_CACOSHARD1_1, 0},
	{"CACOSHARD2_1", 0, SPR_CACO, 8, 3, NULL, 0, 0, S_CACOSHARD2_2, 0},
	{"CACOSHARD2_2", 0, SPR_CACO, 9, 3, NULL, 0, 0, S_CACOSHARD2_1, 0},
	{"CACOFIRE1", 0, SPR_BAL2,   FF_FULLBRIGHT, 2, A_GhostMe, 0, 0, S_CACOFIRE2, 0},
	{"CACOFIRE2", 0, SPR_BAL2, 1|FF_FULLBRIGHT, 2, A_GhostMe, 0, 0, S_CACOFIRE3, 0},
	{"CACOFIRE3", 0, SPR_BAL2,   FF_FULLBRIGHT, 0, A_PlayActiveSound, 0, 0, S_CACOFIRE1, 0},
	{"CACOFIRE_EXPLODE1", 0, SPR_BAL2, 2|FF_FULLBRIGHT, 2, NULL, 0, 0, S_CACOFIRE_EXPLODE2, 0},
	{"CACOFIRE_EXPLODE2", 0, SPR_BAL2, 3|FF_FULLBRIGHT, 2, NULL, 0, 0, S_CACOFIRE_EXPLODE3, 0},
	{"CACOFIRE_EXPLODE3", 0, SPR_BAL2, 4|FF_FULLBRIGHT, 2, NULL, 0, 0, S_CACOFIRE_EXPLODE4, 0},
	{"CACOFIRE_EXPLODE4", 0, SPR_BAL2, 5|FF_FULLBRIGHT, 2, NULL, 0, 0, S_NULL, 0},

	{"SPINBOBERT_MOVE_FLIPUP", 0, SPR_SBOB, 1, 10, A_ZThrust, -2, (1<<16)|1, S_SPINBOBERT_MOVE_UP, 0},
	{"SPINBOBERT_MOVE_UP", 0, SPR_SBOB, 0, 45, A_ZThrust,  4, (1<<16)|1, S_SPINBOBERT_MOVE_FLIPDOWN, 0},
	{"SPINBOBERT_MOVE_FLIPDOWN", 0, SPR_SBOB, 1, 10, A_ZThrust,  2, (1<<16)|1, S_SPINBOBERT_MOVE_DOWN, 0},
	{"SPINBOBERT_MOVE_DOWN", 0, SPR_SBOB, 2, 45, A_ZThrust, -4, (1<<16)|1, S_SPINBOBERT_MOVE_FLIPUP, 0},
	{"SPINBOBERT_FIRE_MOVE", 0, SPR_SBSK, FF_FULLBRIGHT, 1, A_RotateSpikeBall,       0,                        0, S_SPINBOBERT_FIRE_GHOST, 0},
	{"SPINBOBERT_FIRE_GHOST", 0, SPR_SBSK, FF_FULLBRIGHT, 0, A_SpawnParticleRelative, 0, S_SPINBOBERT_FIRE_TRAIL1, S_SPINBOBERT_FIRE_MOVE, 0},
	{"SPINBOBERT_FIRE_TRAIL1", 0, SPR_SBFL, 2|FF_FULLBRIGHT, 2, NULL, 0, 0, S_SPINBOBERT_FIRE_TRAIL2, 0},
	{"SPINBOBERT_FIRE_TRAIL2", 0, SPR_SBFL, 1|FF_FULLBRIGHT, 2, NULL, 0, 0, S_SPINBOBERT_FIRE_TRAIL3, 0},
	{"SPINBOBERT_FIRE_TRAIL3", 0, SPR_SBFL,   FF_FULLBRIGHT, 2, NULL, 0, 0, S_NULL, 0},

	{"HANGSTER_LOOK", 0, SPR_HBAT, 0,  5, A_Look, (900<<16)|1, 0, S_HANGSTER_LOOK, 0},
	{"HANGSTER_SWOOP1", 0, SPR_HBAT, 1,  0, A_MultiShotDist, (MT_DUST<<16)|10, -34, S_HANGSTER_SWOOP2, 0},
	{"HANGSTER_SWOOP2", 0, SPR_HBAT, 1,  2, A_ZThrust, -8, (1<<16)|1, S_HANGSTER_SWOOP2, 0},
	{"HANGSTER_ARC1", 0, SPR_HBAT, 1,  6, A_ZThrust, -5, (1<<16), S_HANGSTER_ARC2, 0},
	{"HANGSTER_ARC2", 0, SPR_HBAT, 1,  5, A_ZThrust, -2, (1<<16), S_HANGSTER_ARC3, 0},
	{"HANGSTER_ARC3", 0, SPR_HBAT, 1,  1, A_ZThrust,  0, (1<<16), S_HANGSTER_FLY1, 0},
	{"HANGSTER_FLY1", 0, SPR_HBAT, 1,  4, A_Thrust, 6, 1, S_HANGSTER_FLY2, 0},
	{"HANGSTER_FLY2", 0, SPR_HBAT, 2,  1, A_PlaySound, sfx_s3k52, 1, S_HANGSTER_FLY3, 0},
	{"HANGSTER_FLY3", 0, SPR_HBAT, 3,  4, A_Thrust, 6, 1, S_HANGSTER_FLY4, 0},
	{"HANGSTER_FLY4", 0, SPR_HBAT, 2,  1, A_Thrust, 6, 1, S_HANGSTER_FLYREPEAT, 0},
	{"HANGSTER_FLYREPEAT", 0, SPR_HBAT, 2,  0, A_Repeat, 12, S_HANGSTER_FLY1, S_HANGSTER_ARCUP1, 0},
	{"HANGSTER_ARCUP1", 0, SPR_HBAT, 1,  5, A_ZThrust,  2, (1<<16), S_HANGSTER_ARCUP2, 0},
	{"HANGSTER_ARCUP2", 0, SPR_HBAT, 1,  6, A_ZThrust,  5, (1<<16), S_HANGSTER_ARCUP3, 0},
	{"HANGSTER_ARCUP3", 0, SPR_HBAT, 1,  1, A_ZThrust,  0, (1<<16), S_HANGSTER_RETURN1, 0},
	{"HANGSTER_RETURN1", 0, SPR_HBAT, 1,  1, A_ZThrust,  8, (1<<16), S_HANGSTER_RETURN2, 0},
	{"HANGSTER_RETURN2", 0, SPR_HBAT, 3,  1, NULL, 0, 0, S_HANGSTER_RETURN1, 0},
	{"HANGSTER_RETURN3", 0, SPR_HBAT, 0, 15, NULL, 0, 0, S_HANGSTER_LOOK, 0},

	{"CRUMBLE1", 0, SPR_NULL, 0,  35, NULL, 0, 0, S_CRUMBLE2, 0},
	{"CRUMBLE2", 0, SPR_NULL, 0, 105, A_Scream, 0, 0, S_NULL, 0},

	// Spark
	{"SPRK1", 0, SPR_NULL, 0, 1, A_ModuloToState, 2, S_SPRK2, S_SPRK3, 0},
	{"SPRK2", 0, SPR_SPRK, FF_TRANS20|FF_ANIMATE|0, 18, NULL, 8, 2, S_NULL, 0},
	{"SPRK3", 0, SPR_SPRK, FF_TRANS20|FF_ANIMATE|9, 18, NULL, 8, 2, S_NULL, 0},

	// Robot Explosion
	{"XPLD_FLICKY", 0, SPR_BOM1, 0, 0, A_FlickySpawn,  0, 0, S_XPLD1, 0},
	{"XPLD1", 0, SPR_BOM1, 0, 2, A_ShadowScream, 0, 0, S_XPLD2, 0},
	{"XPLD2", 0, SPR_BOM1, 1, 2, NULL,           0, 0, S_XPLD3, 0},
	{"XPLD3", 0, SPR_BOM1, 2, 3, NULL,           0, 0, S_XPLD4, 0},
	{"XPLD4", 0, SPR_BOM1, 3, 3, NULL,           0, 0, S_XPLD5, 0},
	{"XPLD5", 0, SPR_BOM1, 4, 4, NULL,           0, 0, S_XPLD6, 0},
	{"XPLD6", 0, SPR_BOM1, 5, 4, NULL,           0, 0, S_NULL, 0},

	{"XPLD_EGGTRAP", 0, SPR_BOM1, FF_ANIMATE,   21, NULL,          5, 4, S_INVISIBLE, 0},

	// Underwater Explosion
	{"WPLD1", 0, SPR_BOM4, 0, 3, A_ShadowScream, 0, 0, S_WPLD2, 0},
	{"WPLD2", 0, SPR_BOM4, 1, 3, NULL,           0, 0, S_WPLD3, 0},
	{"WPLD3", 0, SPR_BOM4, 2, 3, NULL,           0, 0, S_WPLD4, 0},
	{"WPLD4", 0, SPR_BOM4, 3, 3, NULL,           0, 0, S_WPLD5, 0},
	{"WPLD5", 0, SPR_BOM4, 4, 3, NULL,           0, 0, S_WPLD6, 0},
	{"WPLD6", 0, SPR_BOM4, 5, 3, NULL,           0, 0, S_NULL, 0},

	{"DUST1", 0, SPR_DUST,   FF_TRANS40, 4, NULL, 0, 0, S_DUST2, 0},
	{"DUST2", 0, SPR_DUST, 1|FF_TRANS50, 5, NULL, 0, 0, S_DUST3, 0},
	{"DUST3", 0, SPR_DUST, 2|FF_TRANS60, 3, NULL, 0, 0, S_DUST4, 0},
	{"DUST4", 0, SPR_DUST, 3|FF_TRANS70, 2, NULL, 0, 0, S_NULL, 0},

	{"ROCKSPAWN", 0, SPR_NULL, 0, 1, A_RockSpawn, 0, 0, S_ROCKSPAWN, 0},

	{"ROCKCRUMBLEA", 0, SPR_ROIA, FF_ANIMATE|FF_RANDOMANIM, -1, NULL, 4, 2, S_NULL, 0},
	{"ROCKCRUMBLEB", 0, SPR_ROIB, FF_ANIMATE|FF_RANDOMANIM, -1, NULL, 7, 2, S_NULL, 0},
	{"ROCKCRUMBLEC", 0, SPR_ROIC, FF_ANIMATE|FF_RANDOMANIM, -1, NULL, 7, 2, S_NULL, 0},
	{"ROCKCRUMBLED", 0, SPR_ROID, FF_ANIMATE|FF_RANDOMANIM, -1, NULL, 7, 2, S_NULL, 0},
	{"ROCKCRUMBLEE", 0, SPR_ROIE, FF_ANIMATE|FF_RANDOMANIM, -1, NULL, 7, 2, S_NULL, 0},
	{"ROCKCRUMBLEF", 0, SPR_ROIF, FF_ANIMATE|FF_RANDOMANIM, -1, NULL, 7, 2, S_NULL, 0},
	{"ROCKCRUMBLEG", 0, SPR_ROIG, FF_ANIMATE|FF_RANDOMANIM, -1, NULL, 4, 2, S_NULL, 0},
	{"ROCKCRUMBLEH", 0, SPR_ROIH, FF_ANIMATE|FF_RANDOMANIM, -1, NULL, 4, 2, S_NULL, 0},
	{"ROCKCRUMBLEI", 0, SPR_ROII, FF_ANIMATE|FF_RANDOMANIM, -1, NULL, 7, 2, S_NULL, 0},
	{"ROCKCRUMBLEJ", 0, SPR_ROIJ, FF_ANIMATE|FF_RANDOMANIM, -1, NULL, 4, 2, S_NULL, 0},
	{"ROCKCRUMBLEK", 0, SPR_ROIK, FF_ANIMATE|FF_RANDOMANIM, -1, NULL, 4, 2, S_NULL, 0},
	{"ROCKCRUMBLEL", 0, SPR_ROIL, FF_ANIMATE|FF_RANDOMANIM, -1, NULL, 7, 2, S_NULL, 0},
	{"ROCKCRUMBLEM", 0, SPR_ROIM, FF_ANIMATE|FF_RANDOMANIM, -1, NULL, 7, 2, S_NULL, 0},
	{"ROCKCRUMBLEN", 0, SPR_ROIN, FF_ANIMATE|FF_RANDOMANIM, -1, NULL, 7, 2, S_NULL, 0},
	{"ROCKCRUMBLEO", 0, SPR_ROIO, FF_ANIMATE|FF_RANDOMANIM, -1, NULL, 7, 2, S_NULL, 0},
	{"ROCKCRUMBLEP", 0, SPR_ROIP, FF_ANIMATE|FF_RANDOMANIM, -1, NULL, 7, 2, S_NULL, 0},

	{"GFZDEBRIS", 0, SPR_GFZD, FF_ANIMATE|FF_RANDOMANIM, -1, NULL, 31, 1, S_NULL, 0},
	{"BRICKDEBRIS", 0, SPR_BRIC, FF_ANIMATE, -1, A_DebrisRandom, 7, 2, S_NULL, 0},
	{"WOODDEBRIS", 0, SPR_WDDB, FF_ANIMATE, -1, A_DebrisRandom, 7, 2, S_NULL, 0},
	{"REDBRICKDEBRIS", 0, SPR_BRIR, FF_ANIMATE|FF_RANDOMANIM, -1, NULL, 31, 1, S_NULL, 0},
	{"BLUEBRICKDEBRIS", 0, SPR_BRIB, FF_ANIMATE|FF_RANDOMANIM, -1, NULL, 31, 1, S_NULL, 0},
	{"YELLOWBRICKDEBRIS", 0, SPR_BRIY, FF_ANIMATE|FF_RANDOMANIM, -1, NULL, 31, 1, S_NULL, 0},

	{"NAMECHECK", 0, SPR_NULL, 0, 1, NULL, 0, 0, S_NULL, 0},

	{"OLDK_STND", 0, SPR_OLDK, FF_ANIMATE, -1, NULL, 1, 16, S_NULL, 0},
	{"OLDK_DIE0", 0, SPR_OLDK, 2, 0, A_ForceWin, 0, 0, S_OLDK_DIE1, 0},
	{"OLDK_DIE1", 0, SPR_OLDK, 2, 0, A_Scream, 0, 0, S_OLDK_DIE2, 0},
	{"OLDK_DIE2", 0, SPR_OLDK, 2, -1, A_ZThrust, 14, 1|(1<<16), S_NULL, 0},

};

state_t **states;
UINT32 numstates;

static const mobjinfo_t startmobjinfo[] =
{
	{
		"MT_NULL",
		-1,             // doomednum
		S_NULL,         // spawnstate
		0,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		0,              // radius
		0,              // height
		0,              // display offset
		0,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOSECTOR|MF_NOCLIP|MF_NOCLIPHEIGHT|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_UNKNOWN",
		-1,             // doomednum
		S_UNKNOWN,      // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		1*FRACUNIT,     // radius
		1*FRACUNIT,     // height
		0,              // display offset
		0,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOCLIPHEIGHT|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_THOK",
		-1,             // doomednum
		S_THOK,         // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		32*FRACUNIT,    // radius
		64*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOCLIPHEIGHT|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_PLAYER",
		-1,             // doomednum
		S_PLAY_STND,    // spawnstate
		1,              // spawnhealth
		S_PLAY_WALK,    // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_thok,       // attacksound
		S_PLAY_PAIN,    // painstate
		MT_THOK,        // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_PLAY_ROLL,    // missilestate
		S_PLAY_DEAD,    // deathstate
		S_PLAY_DRWN,    // xdeathstate
		sfx_None,       // deathsound
		1,              // speed
		16*FRACUNIT,    // radius
		48*FRACUNIT,    // height
		0,              // display offset
		1000,           // mass
		MT_THOK,        // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SHOOTABLE, // flags
		(statenum_t)MT_NULL// raisestate
	},

	{
		"MT_TAILSOVERLAY",
		-1,             // doomednum
		S_INVISIBLE,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		16*FRACUNIT,    // radius
		48*FRACUNIT,    // height
		2,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOCLIPHEIGHT|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_METALJETFUME",
		-1,             // doomednum
		S_INVISIBLE,    // spawnstate
		1000,           // spawnhealth
		S_JETFUMEFLASH, // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		8*FRACUNIT,     // radius
		16*FRACUNIT,    // height
		2,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOCLIPHEIGHT|MF_NOGRAVITY|MF_SCENERY, // flags
		S_JETFUME1      // raisestate
	},

	{
		"MT_BLUECRAWLA",
		100,            // doomednum
		S_POSS_STND,    // spawnstate
		1,              // spawnhealth
		S_POSS_RUN1,    // seestate
		sfx_None,       // seesound
		32,             // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		200,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_XPLD_FLICKY,  // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		3,              // speed
		24*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_ENEMY|MF_SPECIAL|MF_SHOOTABLE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_REDCRAWLA",
		101,            // doomednum
		S_SPOS_STND,    // spawnstate
		1,              // spawnhealth
		S_SPOS_RUN1,    // seestate
		sfx_None,       // seesound
		32,             // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		170,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_XPLD_FLICKY,  // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		3,              // speed
		24*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_ENEMY|MF_SPECIAL|MF_SHOOTABLE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_GFZFISH",
		102,            // doomednum
		S_FISH2,        // spawnstate
		1,              // spawnhealth
		S_FISH1,        // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_FISH3,        // meleestate
		S_NULL,         // missilestate
		S_XPLD_FLICKY,  // deathstate
		S_FISH4,        // xdeathstate
		sfx_pop,        // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		28*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		1,              // damage
		sfx_None,       // activesound
		MF_ENEMY|MF_SPECIAL|MF_SHOOTABLE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_GOLDBUZZ",
		103,            // doomednum
		S_BUZZLOOK1,    // spawnstate
		1,              // spawnhealth
		S_BUZZFLY1,     // seestate
		sfx_None,       // seesound
		2,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		3072,           // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_XPLD_FLICKY,  // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		4*FRACUNIT,     // speed
		28*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SLIDEME|MF_ENEMY|MF_SPECIAL|MF_SHOOTABLE|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_REDBUZZ",
		104,            // doomednum
		S_RBUZZLOOK1,   // spawnstate
		1,              // spawnhealth
		S_RBUZZFLY1,    // seestate
		sfx_None,       // seesound
		2,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		3072,           // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_XPLD_FLICKY,  // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		8*FRACUNIT,     // speed
		28*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SLIDEME|MF_ENEMY|MF_SPECIAL|MF_SHOOTABLE|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_JETTBOMBER",
		105,            // doomednum
		S_JETBLOOK1,    // spawnstate
		1,              // spawnhealth
		S_JETBZOOM1,    // seestate
		sfx_None,       // seesound
		32,             // reactiontime
		sfx_s3k51,      // attacksound
		S_NULL,         // painstate
		200,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_XPLD_FLICKY,  // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		1*FRACUNIT,     // speed
		20*FRACUNIT,    // radius
		50*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SLIDEME|MF_ENEMY|MF_SPECIAL|MF_SHOOTABLE|MF_NOGRAVITY, // flags
		(statenum_t)MT_MINE// raisestate
	},

	{
		"MT_JETTGUNNER",
		106,            // doomednum
		S_JETGLOOK1,    // spawnstate
		1,              // spawnhealth
		S_JETGZOOM1,    // seestate
		sfx_None,       // seesound
		5,              // reactiontime
		sfx_s3k4d,      // attacksound
		S_NULL,         // painstate
		3072,           // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_JETGSHOOT1,   // missilestate
		S_XPLD_FLICKY,  // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		1*FRACUNIT,     // speed
		20*FRACUNIT,    // radius
		48*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SLIDEME|MF_ENEMY|MF_SPECIAL|MF_SHOOTABLE|MF_NOGRAVITY, // flags
		(statenum_t)MT_JETTBULLET// raisestate
	},

	{
		"MT_CRAWLACOMMANDER",
		107,            // doomednum
		S_CCOMMAND1,    // spawnstate
		2,              // spawnhealth
		S_CCOMMAND3,    // seestate
		sfx_None,       // seesound
		2*TICRATE,      // reactiontime
		sfx_s3k60,      // attacksound
		S_CCOMMAND3,    // painstate
		200,            // painchance
		sfx_dmpain,     // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_XPLD_FLICKY,  // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		3,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_s3k5d,      // activesound
		MF_SLIDEME|MF_ENEMY|MF_SPECIAL|MF_SHOOTABLE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_DETON",
		108,            // doomednum
		S_DETON1,       // spawnstate
		1,              // spawnhealth
		S_DETON2,       // seestate
		sfx_s3k86,      // seesound -- sfx_kc57 for a self-propelled deton...
		1,              // reactiontime
		sfx_deton,      // attacksound
		S_NULL,         // painstate
		3072,           // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_XPLD_FLICKY,  // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		1*FRACUNIT,     // speed
		20*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		0,              // mass
		1,              // damage
		sfx_None,       // activesound
		MF_ENEMY|MF_SHOOTABLE|MF_NOGRAVITY|MF_MISSILE, // flags
		(statenum_t)ANG15// raisestate: largest angle to turn in one tic (here, 15 degrees)
	},

	{
		"MT_SKIM",
		109,            // doomednum
		S_SKIM1,        // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_s3k51,      // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_SKIM3,        // meleestate
		S_NULL,         // missilestate
		S_XPLD_FLICKY,  // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		8,              // speed
		16*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_ENEMY|MF_SPECIAL|MF_NOGRAVITY|MF_SHOOTABLE, // flags
		(statenum_t)MT_MINE// raisestate
	},

	{
		"MT_TURRET",
		110,            // doomednum
		S_TURRET,       // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_trfire,     // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_fizzle,     // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_TURRETSHOCK1, // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		MT_TURRETLASER, // mass
		1,              // damage
		sfx_trpowr,     // activesound
		MF_NOBLOCKMAP,  // flags
		S_NULL          // raisestate
	},

	{
		"MT_POPUPTURRET",
		111,            // doomednum
		S_TURRETLOOK,   // spawnstate
		1,              // spawnhealth
		S_TURRETSEE,    // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_trfire,     // attacksound
		S_NULL,         // painstate
		1024,           // painchance
		sfx_s3k64,      // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_XPLD_FLICKY,  // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		0,              // speed
		12*FRACUNIT,    // radius
		64*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_ENEMY|MF_SPECIAL|MF_SHOOTABLE, // flags
		(statenum_t)MT_JETTBULLET// raisestate
	},

	{
		"MT_SPINCUSHION",
		112,            // doomednum
		S_SPINCUSHION_LOOK, // spawnstate
		1,              // spawnhealth
		S_SPINCUSHION_CHASE1, // seestate
		sfx_None,       // seesound
		3*TICRATE,      // reactiontime
		sfx_s3kd8s,     // attacksound
		S_NULL,         // painstate
		5*TICRATE,      // painchance
		sfx_shrpsp,     // painsound
		S_SPINCUSHION_STOP1, // meleestate
		S_SPINCUSHION_AIM1, // missilestate
		S_XPLD_FLICKY,  // deathstate
		S_SPINCUSHION_STOP3, // xdeathstate
		sfx_pop,        // deathsound
		2,              // speed
		16*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		DMG_SPIKE,      // mass
		0,              // damage
		sfx_s3kaa,      // activesound
		MF_ENEMY|MF_SPECIAL|MF_SHOOTABLE|MF_BOUNCE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CRUSHSTACEAN",
		126,            // doomednum
		S_CRUSHSTACEAN_ROAM1, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		32,             // reactiontime
		sfx_s3k6b,      // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_CRUSHSTACEAN_PUNCH1, // missilestate
		S_XPLD_FLICKY,  // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		8,              // speed
		24*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		0,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_ENEMY|MF_SPECIAL|MF_SHOOTABLE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CRUSHCLAW",
		-1,             // doomednum
		S_CRUSHCLAW_AIM, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		16,             // reactiontime
		sfx_s3k6b,      // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_CRUSHCLAW_OUT,// missilestate
		S_XPLD1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		600,            // speed
		22*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		(sfx_s3k49<<8), // mass
		0,              // damage
		sfx_s3kd2l,     // activesound
		MF_PAIN|MF_NOGRAVITY|MF_NOCLIPHEIGHT, // flags
		(statenum_t)MT_CRUSHCHAIN// raisestate
	},

	{
		"MT_CRUSHCHAIN",
		-1,             // doomednum
		S_CRUSHCHAIN,   // spawnstate
		0,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		0,              // radius
		0,              // height
		0,              // display offset
		0,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SCENERY|MF_NOBLOCKMAP|MF_NOCLIP|MF_NOCLIPHEIGHT|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BANPYURA",
		138,            // doomednum
		S_BANPYURA_ROAM1, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		32,             // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_XPLD_FLICKY,  // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		8,              // speed
		24*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		0,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_ENEMY|MF_SPECIAL|MF_SHOOTABLE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BANPSPRING",
		-1,             // doomednum
		S_CDIAG1,       // spawnstate
		1,              // spawnhealth
		S_CDIAG2,       // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_cdfm08,     // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_XPLD1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		300,            // speed
		22*FRACUNIT,    // radius
		22*FRACUNIT,    // height
		0,              // display offset
		11*FRACUNIT,    // mass
		11*FRACUNIT,    // damage
		sfx_None,       // activesound
		MF_SPRING|MF_NOGRAVITY, // flags
		S_CDIAG2        // raisestate
	},

	{
		"MT_JETJAW",
		113,            // doomednum
		S_JETJAW_ROAM1, // spawnstate
		1,              // spawnhealth
		S_JETJAW_CHOMP1,// seestate
		sfx_None,       // seesound
		4*TICRATE,      // reactiontime
		sfx_s1ab,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_XPLD_FLICKY,  // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		8,              // speed
		12*FRACUNIT,    // radius
		20*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SLIDEME|MF_FLOAT|MF_ENEMY|MF_SPECIAL|MF_SHOOTABLE|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SNAILER",
		114,            // doomednum
		S_SNAILER1,     // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		2,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_SNAILER_FLICKY, // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		FRACUNIT,       // speed
		24*FRACUNIT,    // radius
		48*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SLIDEME|MF_ENEMY|MF_SPECIAL|MF_SHOOTABLE|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_VULTURE",
		115,            // doomednum
		S_VULTURE_STND, // spawnstate
		1,              // spawnhealth
		S_VULTURE_DRIFT,// seestate
		sfx_None,       // seesound
		TICRATE/2,      // reactiontime
		sfx_s3k60,      // attacksound
		S_VULTURE_STUNNED, // painstate
		S_NULL,         // painchance
		sfx_s3k96,      // painsound
		S_NULL,         // meleestate
		S_VULTURE_ZOOM1,// missilestate
		S_XPLD_FLICKY,  // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		5,              // speed
		12*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		TICRATE,        // mass
		0,              // damage
		sfx_jet,        // activesound
		MF_ENEMY|MF_SPECIAL|MF_SHOOTABLE|MF_NOGRAVITY|MF_SLIDEME, // flags
		S_NULL          // raisestate
	},

	{
		"MT_POINTY",
		116,            // doomednum
		S_POINTY1,      // spawnstate
		1,              // spawnhealth
		S_POINTY1,      // seestate
		sfx_None,       // seesound
		6,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		4,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_XPLD_FLICKY,  // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		5*FRACUNIT,     // speed
		4*FRACUNIT,     // radius
		8*FRACUNIT,     // height
		0,              // display offset
		MT_POINTYBALL,  // mass
		128,            // damage
		sfx_None,       // activesound
		MF_SLIDEME|MF_ENEMY|MF_SPECIAL|MF_SHOOTABLE|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_POINTYBALL",
		-1,             // doomednum
		S_POINTYBALL1,  // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		4*FRACUNIT,     // speed
		4*FRACUNIT,     // radius
		8*FRACUNIT,     // height
		0,              // display offset
		DMG_SPIKE,      // mass
		1,              // damage
		sfx_None,       // activesound
		MF_PAIN|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_ROBOHOOD",
		117,              // doomednum
		S_ROBOHOOD_LOOK,  // spawnstate
		1,                // spawnhealth
		S_ROBOHOOD_STAND, // seestate
		sfx_None,         // seesound
		TICRATE,          // reactiontime
		sfx_ngjump,       // attacksound
		S_NULL,           // painstate
		0,                // painchance
		sfx_None,         // painsound
		S_ROBOHOOD_JUMP3, // meleestate
		S_ROBOHOOD_FIRE1, // missilestate
		S_XPLD_FLICKY,    // deathstate
		S_NULL,           // xdeathstate
		sfx_pop,          // deathsound
		3,                // speed
		24*FRACUNIT,      // radius
		32*FRACUNIT,      // height
		0,                // display offset
		100,              // mass
		0,                // damage
		sfx_s3k4a,        // activesound
		MF_ENEMY|MF_SPECIAL|MF_SHOOTABLE, // flags
		S_ROBOHOOD_JUMP1  // raisestate
	},

	{
		"MT_FACESTABBER",
		118,            // doomednum
		S_FACESTABBER_STND1, // spawnstate
		2,              // spawnhealth
		S_FACESTABBER_STND1, // seestate
		sfx_None,       // seesound
		70,             // reactiontime
		sfx_zoom,       // attacksound
		S_FACESTABBER_PAIN, // painstate
		0,              // painchance
		sfx_dmpain,     // painsound
		S_FACESTABBER_CHARGE1, // meleestate
		S_FACESTABBER_CHARGE1, // missilestate
		S_FACESTABBER_DIE1, // deathstate
		S_NULL,         // xdeathstate
		sfx_s3kb4,      // deathsound
		3,              // speed
		32*FRACUNIT,    // radius
		72*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_s3kc5s,      // activesound
		MF_ENEMY|MF_SPECIAL|MF_SHOOTABLE|MF_SLIDEME, // flags
		S_NULL          // raisestate
	},

	{
		"MT_FACESTABBERSPEAR",
		-1,              // doomednum
		S_FACESTABBERSPEAR, // spawnstate
		1,               // spawnhealth
		S_NULL,          // seestate
		sfx_None,        // seesound
		35,              // reactiontime
		sfx_None,        // attacksound
		S_NULL,          // painstate
		0,               // painchance
		sfx_None,        // painsound
		S_NULL,          // meleestate
		S_NULL,          // missilestate
		S_NULL,          // deathstate
		S_NULL,          // xdeathstate
		sfx_None,        // deathsound
		0,               // speed
		32*FRACUNIT,     // radius
		72*FRACUNIT,     // height
		0,               // display offset
		DMG_SPIKE,       // mass
		0,               // damage
		sfx_None,        // activesound
		MF_PAIN|MF_NOGRAVITY|MF_NOCLIPHEIGHT, // flags
		S_NULL           // raisestate
	},

	{
		"MT_EGGGUARD",
		119,             // doomednum
		S_EGGGUARD_STND, // spawnstate
		1,               // spawnhealth
		S_EGGGUARD_WALK1,// seestate
		sfx_None,        // seesound
		35,              // reactiontime
		sfx_None,        // attacksound
		S_EGGGUARD_MAD1, // painstate
		0,               // painchance
		sfx_None,        // painsound
		S_EGGGUARD_RUN1, // meleestate
		S_NULL,          // missilestate
		S_XPLD_FLICKY,   // deathstate
		S_NULL,          // xdeathstate
		sfx_pop,         // deathsound
		6,               // speed
		16*FRACUNIT,     // radius
		48*FRACUNIT,     // height
		0,               // display offset
		100,             // mass
		0,               // damage
		sfx_None,        // activesound
		MF_ENEMY,        // flags
		S_NULL           // raisestate
	},

	{
		"MT_EGGSHIELD",
		-1,              // doomednum
		S_EGGSHIELD,     // spawnstate
		1,               // spawnhealth
		S_EGGSHIELD,     // seestate
		sfx_None,        // seesound
		35,              // reactiontime
		sfx_s3k7b,       // attacksound
		S_NULL,          // painstate
		0,               // painchance
		sfx_s3k7b,       // painsound
		S_NULL,          // meleestate
		S_NULL,          // missilestate
		S_EGGSHIELDBREAK,// deathstate
		S_NULL,          // xdeathstate
		sfx_wbreak,      // deathsound
		3,               // speed
		24*FRACUNIT,     // radius
		128*FRACUNIT,    // height
		0,               // display offset
		100,             // mass
		0,               // damage
		sfx_None,        // activesound
		MF_SPECIAL|MF_NOGRAVITY, // flags
		S_NULL           // raisestate
	},

	{
		"MT_GSNAPPER",
		120,            // doomednum
		S_SNAPPER_SPAWN,// spawnstate
		1,              // spawnhealth
		S_GSNAPPER1,    // seestate
		sfx_None,       // seesound
		10,             // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		200,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_SNAPPER_XPLD, // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		4,              // speed
		24*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_s3k7e,      // activesound
		MF_ENEMY|MF_SPECIAL|MF_SHOOTABLE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SNAPPER_LEG",
		-1,             // doomednum
		S_SNAPPER_LEG,  // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		6*FRACUNIT,     // radius
		12*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SCENERY|MF_PAIN|MF_NOCLIP|MF_NOCLIPHEIGHT|MF_NOBLOCKMAP|MF_NOGRAVITY, // flags
		S_SNAPPER_LEGRAISE // raisestate
	},

	{
		"MT_SNAPPER_HEAD",
		-1,             // doomednum
		S_SNAPPER_HEAD, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		6*FRACUNIT,     // radius
		12*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_PAIN|MF_NOCLIP|MF_NOCLIPHEIGHT|MF_NOBLOCKMAP|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_MINUS",
		121,            // doomednum
		S_MINUS_INIT,   // spawnstate
		1,              // spawnhealth
		S_MINUS_DIGGING1,// seestate
		sfx_None,       // seesound
		32,             // reactiontime
		sfx_s3kccs,     // attacksound
		S_NULL,         // painstate
		200,            // painchance
		sfx_None,       // painsound
		S_MINUS_BURST0, // meleestate
		S_MINUS_POPUP,  // missilestate
		S_XPLD_FLICKY,  // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		17,             // speed
		24*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_s3kd3s,     // activesound
		MF_ENEMY|MF_NOCLIPTHING, // flags
		S_MINUS_BURST1  // raisestate
	},

	{
		"MT_MINUSDIRT",
		-1,             // doomednum
		S_MINUSDIRT1,   // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		8*FRACUNIT,     // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIPTHING, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SPRINGSHELL",
		122,            // doomednum
		S_SSHELL_STND,  // spawnstate
		1,              // spawnhealth
		S_SSHELL_RUN1,  // seestate
		sfx_None,       // seesound
		32,             // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_spring,     // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_XPLD_FLICKY,  // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		6,              // speed
		24*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		15*FRACUNIT,    // mass
		0,              // damage
		sfx_None,       // activesound
		MF_ENEMY|MF_SPECIAL|MF_SHOOTABLE, // flags
		S_SSHELL_SPRING1// raisestate
	},

	{
		"MT_YELLOWSHELL",
		125,            // doomednum
		S_YSHELL_STND,  // spawnstate
		1,              // spawnhealth
		S_YSHELL_RUN1,  // seestate
		sfx_None,       // seesound
		32,             // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_spring,     // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_XPLD_FLICKY,  // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		6,              // speed
		24*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		20*FRACUNIT,    // mass
		0,              // damage
		sfx_None,       // activesound
		MF_ENEMY|MF_SPECIAL|MF_SHOOTABLE, // flags
		S_YSHELL_SPRING1// raisestate
	},

	{
		"MT_UNIDUS",
		123,            // doomednum
		S_UNIDUS_STND,  // spawnstate
		1,              // spawnhealth
		S_UNIDUS_RUN,   // seestate
		sfx_None,       // seesound
		32,             // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		MT_UNIBALL,     // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_XPLD_FLICKY,  // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		2,              // speed
		18*FRACUNIT,    // radius
		36*FRACUNIT,    // height
		0,              // display offset
		4*FRACUNIT,     // mass
		5,              // damage
		sfx_None,       // activesound
		MF_ENEMY|MF_SPECIAL|MF_SHOOTABLE|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_UNIBALL",
		-1,             // doomednum
		S_UNIDUS_BALL,  // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		1,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		20*FRACUNIT,    // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		2*FRACUNIT,     // speed
		13*FRACUNIT,    // radius
		26*FRACUNIT,    // height
		0,              // display offset
		DMG_SPIKE,      // mass
		8*FRACUNIT,     // damage
		sfx_None,       // activesound
		MF_PAIN|MF_NOGRAVITY|MF_NOCLIP|MF_NOCLIPHEIGHT|MF_NOCLIPTHING, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CANARIVORE",
		134,            // doomednum
		S_CANARIVORE_LOOK,  // spawnstate
		1,              // spawnhealth
		S_CANARIVORE_AWAKEN1,   // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_XPLD_FLICKY,  // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		0,              // speed
		12*FRACUNIT,    // radius
		80*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SPECIAL|MF_SHOOTABLE|MF_ENEMY|MF_SPAWNCEILING|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CANARIVORE_GAS",
		-1,             // doomednum
		S_CANARIVOREGAS_1,  // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_s3k5d,      // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SPECIAL,     // flags
		S_NULL          // raisestate
	},

	{
		"MT_PYREFLY",
		136,            // doomednum
		S_PYREFLY_FLY,  // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_PYREFLY_BURN, // meleestate
		S_NULL,         // missilestate
		S_XPLD_FLICKY,  // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		1,              // speed
		24*FRACUNIT,    // radius
		34*FRACUNIT,    // height
		0,              // display offset
		DMG_FIRE,       // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOGRAVITY|MF_SPECIAL|MF_SHOOTABLE|MF_ENEMY|MF_SLIDEME, // flags
		S_NULL          // raisestate
	},

	{
		"MT_PYREFLY_FIRE",
		-1,             // doomednum
		S_PYREFIRE1,    // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		24*FRACUNIT,    // radius
		34*FRACUNIT,    // height
		1,              // display offset
		DMG_FIRE,       // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOGRAVITY|MF_NOBLOCKMAP|MF_NOCLIPHEIGHT|MF_FIRE|MF_PAIN, // flags
		S_NULL          // raisestate
	},

	{
		"MT_PTERABYTESPAWNER",
		135,            // doomednum
		S_PTERABYTESPAWNER, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		16*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOGRAVITY|MF_NOCLIPTHING|MF_NOBLOCKMAP|MF_RUNSPAWNFUNC|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_PTERABYTEWAYPOINT",
		-1,             // doomednum
		S_PTERABYTEWAYPOINT, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		4*FRACUNIT,     // speed
		24*FRACUNIT,    // radius
		48*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOGRAVITY|MF_NOCLIPTHING|MF_NOBLOCKMAP|MF_RUNSPAWNFUNC|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_PTERABYTE",
		-1,             // doomednum
		S_PTERABYTE_FLY1, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_pscree,     // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_XPLD_FLICKY,  // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		4*FRACUNIT,     // speed
		24*FRACUNIT,    // radius
		48*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SPECIAL|MF_SHOOTABLE|MF_ENEMY|MF_NOGRAVITY|MF_SLIDEME, // flags
		S_NULL          // raisestate
	},

	{
		"MT_DRAGONBOMBER",
		137,            // doomednum
		S_DRAGONBOMBER, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		6,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_XPLD_FLICKY,  // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		10*FRACUNIT,    // speed
		28*FRACUNIT,    // radius
		48*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SPECIAL|MF_SHOOTABLE|MF_ENEMY|MF_NOGRAVITY|MF_SLIDEME|MF_RUNSPAWNFUNC, // flags
		S_NULL          // raisestate
	},

	{
		"MT_DRAGONWING",
		-1,             // doomednum
		S_DRAGONWING1,  // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_XPLD_FLICKY,  // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		0,              // speed
		12*FRACUNIT,    // radius
		12*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOGRAVITY|MF_SCENERY|MF_NOBLOCKMAP|MF_NOCLIP, // flags
		S_NULL          // raisestate
	},

	{
		"MT_DRAGONTAIL",
		-1,             // doomednum
		S_DRAGONTAIL_LOADED, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		MT_DRAGONMINE,  // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_XPLD1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		20*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_tink,       // activesound
		MF_NOGRAVITY|MF_SLIDEME|MF_PAIN, // flags
		S_DRAGONTAIL_EMPTY // raisestate
	},

	{
		"MT_DRAGONMINE",
		-1,             // doomednum
		S_DRAGONMINE,   // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_s3k76,      // seesound
		0,              // reactiontime
		sfx_s3k89,      // attacksound
		S_NULL,         // painstate
		6,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_TNTBARREL_EXPL1, // deathstate
		S_NULL,         // xdeathstate
		sfx_s3k6e,      // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_s3k5d,      // activesound
		MF_SPECIAL|MF_SHOOTABLE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BOSSEXPLODE",
		-1,             // doomednum
		S_BOSSEXPLODE,  // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		1,              // speed
		8*FRACUNIT,     // radius
		16*FRACUNIT,    // height
		0,              // display offset
		4,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOGRAVITY|MF_NOCLIPHEIGHT, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SONIC3KBOSSEXPLODE",
		-1,                      // doomednum
		S_SONIC3KBOSSEXPLOSION1, // spawnstate
		1000,                    // spawnhealth
		S_NULL,                  // seestate
		sfx_None,                // seesound
		8,                       // reactiontime
		sfx_None,                // attacksound
		S_NULL,                  // painstate
		0,                       // painchance
		sfx_None,                // painsound
		S_NULL,                  // meleestate
		S_NULL,                  // missilestate
		S_NULL,                  // deathstate
		S_NULL,                  // xdeathstate
		sfx_None,                // deathsound
		1,                       // speed
		8*FRACUNIT,              // radius
		16*FRACUNIT,             // height
		0,                       // display offset
		4,                       // mass
		0,                       // damage
		sfx_None,                // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOGRAVITY|MF_NOCLIPHEIGHT, // flags
		S_NULL                   // raisestate
	},

	{
		"MT_BOSSFLYPOINT",
		290,            // doomednum
		S_INVISIBLE,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		1,              // speed
		2*FRACUNIT,     // radius
		4*FRACUNIT,     // height
		0,              // display offset
		4,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOSECTOR|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_EGGTRAP",
		291,            // doomednum
		S_INVISIBLE,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_pop,        // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_INVISIBLE,    // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		1,              // speed
		8*FRACUNIT,     // radius
		16*FRACUNIT,    // height
		0,              // display offset
		4,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOSECTOR, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BOSS3WAYPOINT",
		292,            // doomednum
		S_INVISIBLE,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		1,              // speed
		2*FRACUNIT,     // radius
		4*FRACUNIT,     // height
		0,              // display offset
		4,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOSECTOR|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BOSS9GATHERPOINT",
		293,            // doomednum
		S_INVISIBLE,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		1,              // speed
		2*FRACUNIT,     // radius
		4*FRACUNIT,     // height
		0,              // display offset
		4,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOSECTOR|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BOSSJUNK",
		-1,             // doomednum
		S_BOSSEGLZ1,    // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		64*FRACUNIT,    // height
		2,              // display offset
		100,            // mass
		1,              // damage
		sfx_None,       // activesound
		MF_SCENERY|MF_NOBLOCKMAP|MF_NOCLIPHEIGHT, // flags
		S_NULL          // raisestate
	},

	{
		"MT_EGGMOBILE",
		200,               // doomednum
		S_EGGMOBILE_STND,  // spawnstate
		8,                 // spawnhealth
		S_EGGMOBILE_STND,  // seestate
		sfx_None,          // seesound
		45,                // reactiontime
		sfx_None,          // attacksound
		S_EGGMOBILE_PAIN,  // painstate
		MT_THOK,           // painchance
		sfx_dmpain,        // painsound
		S_EGGMOBILE_LATK1, // meleestate
		S_EGGMOBILE_RATK1, // missilestate
		S_EGGMOBILE_DIE1,  // deathstate
		S_EGGMOBILE_FLEE1, // xdeathstate
		sfx_s3kb4,         // deathsound
		4,                 // speed
		36*FRACUNIT,       // radius
		84*FRACUNIT,       // height
		0,                 // display offset
		sfx_None,          // mass
		3,                 // damage
		sfx_telept,        // activesound
		MF_SPECIAL|MF_SHOOTABLE|MF_FLOAT|MF_NOGRAVITY|MF_BOSS, // flags
		S_EGGMOBILE_PANIC1 // raisestate
	},

	{
		"MT_JETFUME1",
		-1,             // doomednum
		S_JETFUME1,     // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		1,              // speed
		8*FRACUNIT,     // radius
		16*FRACUNIT,    // height
		0,              // display offset
		4,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOCLIP|MF_NOCLIPHEIGHT, // flags
		S_NULL          // raisestate
	},

	{
		"MT_EGGMOBILE_BALL",
		-1,             // doomednum
		S_EGGMOBILE_BALL,// spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_cannon,     // seesound
		1,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		40*FRACUNIT,    // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		4*FRACUNIT,     // speed
		13*FRACUNIT,    // radius
		26*FRACUNIT,    // height
		0,              // display offset
		0,              // mass
		8*FRACUNIT,     // damage
		sfx_None,       // activesound
		MF_PAIN|MF_NOGRAVITY|MF_NOCLIP|MF_NOCLIPHEIGHT|MF_NOCLIPTHING, // flags
		S_NULL          // raisestate
	},

	{
		"MT_EGGMOBILE_TARGET",
		-1,             // doomednum
		S_EGGMOBILE_TARGET, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		0,              // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		2*FRACUNIT,     // speed
		0,              // radius
		0,              // height
		0,              // display offset
		0,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOCLIP|MF_NOCLIPHEIGHT|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_EGGMOBILE_FIRE",
		-1,             // doomednum
		S_LASERFLAME1,  // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_s3kc2s,     // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_s3k8d,      // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		24*FRACUNIT,    // radius
		84*FRACUNIT,    // height
		0,              // display offset
		DMG_FIRE,       // mass
		1,              // damage
		sfx_None,       // activesound
		MF_NOGRAVITY|MF_FIRE|MF_PAIN, // flags
		S_NULL          // raisestate
	},

	{
		"MT_EGGMOBILE2",
		201,               // doomednum
		S_EGGMOBILE2_STND, // spawnstate
		8,                 // spawnhealth
		S_NULL,            // seestate
		0,                 // seesound
		-666,              // reactiontime
		sfx_gspray,        // attacksound
		S_EGGMOBILE2_PAIN, // painstate
		MT_GOOP,           // painchance
		sfx_dmpain,        // painsound
		S_EGGMOBILE2_PAIN2, // meleestate
		(statenum_t)MT_EGGMOBILE2_POGO, // missilestate
		S_EGGMOBILE2_DIE1, // deathstate
		S_EGGMOBILE2_FLEE1,// xdeathstate
		sfx_s3kb4,         // deathsound
		2*FRACUNIT,        // speed
		36*FRACUNIT,       // radius
		84*FRACUNIT,       // height
		0,                 // display offset
		0,                 // mass
		3,                 // damage
		sfx_pogo,          // activesound
		MF_SPECIAL|MF_SHOOTABLE|MF_NOGRAVITY|MF_BOSS, // flags
		S_EGGMOBILE2_POGO1 // raisestate
	},

	{
		"MT_EGGMOBILE2_POGO",
		-1,             // doomednum
		S_INVISIBLE,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		15*FRACUNIT,    // radius
		28*FRACUNIT,    // height
		0,              // display offset
		0,              // mass
		0,              // damage
		sfx_spring,     // activesound
		MF_SPECIAL|MF_NOGRAVITY|MF_NOCLIP|MF_NOCLIPHEIGHT, // flags
		S_EGGMOBILE2_POGO5 // raisestate
	},

	{
		"MT_GOOP",
		-1,             // doomednum
		S_GOOP1,        // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_ghit,       // painsound
		S_GOOP3,        // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		1,              // speed
		4*FRACUNIT,     // radius
		4*FRACUNIT,     // height
		0,              // display offset
		DMG_WATER,      // mass
		0,              // damage
		sfx_None,       // activesound
		MF_PAIN,        // flags
		S_NULL          // raisestate
	},

	{
		"MT_GOOPTRAIL",
		-1,             // doomednum
		S_GOOPTRAIL,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		3,              // speed
		4*FRACUNIT,     // radius
		4*FRACUNIT,     // height
		0,              // display offset
		4,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOCLIPHEIGHT|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_EGGMOBILE3",
		202,                // doomednum
		S_EGGMOBILE3_STND,  // spawnstate
		8,                  // spawnhealth
		S_NULL,             // seestate
		sfx_None,           // seesound
		0,                  // reactiontime
		sfx_None,           // attacksound
		S_EGGMOBILE3_PAIN,  // painstate
		MT_NULL,            // painchance
		sfx_dmpain,         // painsound
		S_NULL,             // meleestate
		S_EGGMOBILE3_SHOCK, // missilestate
		S_EGGMOBILE3_DIE1,  // deathstate
		S_EGGMOBILE3_FLEE1, // xdeathstate
		sfx_s3kb4,          // deathsound
		8*FRACUNIT,         // speed
		36*FRACUNIT,        // radius
		116*FRACUNIT,       // height
		0,                  // display offset
		MT_FAKEMOBILE,      // mass
		3,                  // damage
		sfx_telept,         // activesound
		MF_SPECIAL|MF_SHOOTABLE|MF_NOGRAVITY|MF_BOSS|MF_NOCLIPHEIGHT, // flags
		S_EGGMOBILE3_ROFL   // raisestate
	},

	{
		"MT_FAKEMOBILE",
		-1,                 // doomednum
		S_FAKEMOBILE_INIT,  // spawnstate
		1000,               // spawnhealth
		S_NULL,             // seestate
		sfx_None,           // seesound
		0,                  // reactiontime
		sfx_None,           // attacksound
		S_NULL,             // painstate
		MT_NULL,            // painchance
		sfx_s3k7b,          // painsound
		S_NULL,             // meleestate
		S_FAKEMOBILE_ATK1,  // missilestate
		S_FAKEMOBILE_DIE1,  // deathstate
		S_NULL,             // xdeathstate
		sfx_mswarp,         // deathsound
		8*FRACUNIT,         // speed
		36*FRACUNIT,        // radius
		116*FRACUNIT,       // height
		0,                  // display offset
		0,                  // mass
		3,                  // damage
		sfx_None,           // activesound
		MF_SPECIAL|MF_NOGRAVITY|MF_RUNSPAWNFUNC|MF_NOCLIPHEIGHT, // flags
		S_NULL              // raisestate
	},

	{
		"MT_SHOCKWAVE",
		-1,             // doomednum
		S_SHOCKWAVE1,   // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_s3k5e,      // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		8*TICRATE,      // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_SPRK1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		12*FRACUNIT,    // speed
		48*FRACUNIT,    // radius
		8*FRACUNIT,     // height
		0,              // display offset
		DMG_ELECTRIC|(sfx_buzz2<<8), // mass
		3,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_MISSILE|MF_PAIN|MF_NOGRAVITY|MF_PAPERCOLLISION, // flags
		S_NULL          // raisestate
	},

	{
		"MT_EGGMOBILE4",
		203,               // doomednum
		S_EGGMOBILE4_STND, // spawnstate
		8,                 // spawnhealth
		S_NULL,            // seestate
		sfx_None,          // seesound
		0,                 // reactiontime
		sfx_None,          // attacksound
		S_EGGMOBILE4_PAIN1,// painstate
		0,                 // painchance
		sfx_dmpain,        // painsound
		S_EGGMOBILE4_LATK1,// meleestate
		S_EGGMOBILE4_RATK1,// missilestate
		S_EGGMOBILE4_DIE1, // deathstate
		S_EGGMOBILE4_FLEE1,// xdeathstate
		sfx_s3kb4,         // deathsound
		0,                 // speed
		36*FRACUNIT,       // radius
		84*FRACUNIT,       // height
		0,                 // display offset
		0,                 // mass
		3,                 // damage
		sfx_None,          // activesound
		MF_SPECIAL|MF_SHOOTABLE|MF_NOGRAVITY|MF_BOSS|MF_NOCLIPHEIGHT, // flags
		S_EGGMOBILE4_RAISE1// raisestate
	},

	{
		"MT_EGGMOBILE4_MACE",
		-1,             // doomednum
		S_EGGMOBILE4_MACE, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_EGGMOBILE4_MACE_DIE1, // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		48*FRACUNIT,    // speed
		34*FRACUNIT,    // radius
		68*FRACUNIT,    // height
		0,              // display offset
		DMG_SPIKE,      // mass
		1,              // damage
		sfx_mswing,     // activesound
		MF_PAIN|MF_NOCLIP|MF_NOCLIPHEIGHT|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_JETFLAME",
		-1,             // doomednum
		S_JETFLAME,     // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		1,              // speed
		20*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		DMG_FIRE,       // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOCLIPHEIGHT|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_EGGROBO1",
		1127,           // doomednum
		S_EGGROBO1_STND,// spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_s3ka0,      // seesound
		8,              // reactiontime
		sfx_bsnipe,     // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_EGGROBO1_BSLAP1, // meleestate
		S_NULL,         // missilestate
		S_EGGROBO1_PISSED, // deathstate
		S_NULL,         // xdeathstate
		sfx_s3ka0,      // deathsound
		12*FRACUNIT,    // speed
		20*FRACUNIT,    // radius
		72*FRACUNIT,    // height
		0,              // display offset
		0,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SPECIAL|MF_NOGRAVITY|MF_NOCLIPHEIGHT, // flags
		S_NULL          // raisestate
	},

	{
		"MT_EGGROBOJET",
		-1,             // doomednum
		S_EGGROBOJET,   // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		1,              // speed
		10*FRACUNIT,    // radius
		28*FRACUNIT,    // height
		0,              // display offset
		0,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOCLIPHEIGHT|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_FANG",
		204,               // doomednum
		S_FANG_SETUP,      // spawnstate
		8,                 // spawnhealth
		S_FANG_PATHINGSTART1, // seestate
		sfx_None,          // seesound
		0,                 // reactiontime
		sfx_skid,          // attacksound
		S_FANG_PAIN1,      // painstate
		0,                 // painchance
		sfx_s3k5d,         // painsound
		S_NULL,            // meleestate
		S_NULL,            // missilestate
		S_FANG_DIE1,       // deathstate
		S_FANG_KO,         // xdeathstate
		sfx_s3k90,         // deathsound
		0,                 // speed
		24*FRACUNIT,       // radius
		60*FRACUNIT,       // height
		0,                 // display offset
		0,                 // mass
		3,                 // damage
		sfx_boingf,        // activesound
		MF_RUNSPAWNFUNC|MF_SPECIAL|MF_BOSS|MF_SHOOTABLE|MF_GRENADEBOUNCE|MF_NOCLIPTHING, // flags -- MF_NOCLIPTHING will be removed after intro event ends
		S_NULL             // raisestate
	},

	{
		"MT_BROKENROBOT",
		-1,             // doomednum
		S_BROKENROBOTRANDOM, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_ambint,     // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		255,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		16*FRACUNIT,    // height
		0,              // display offset
		1000,           // mass
		0,              // damage
		sfx_crumbl,     // activesound
		MF_RUNSPAWNFUNC|MF_NOBLOCKMAP|MF_NOCLIPTHING|MF_SCENERY|MF_NOCLIPHEIGHT,  // flags
		S_NULL          // raisestate
	},

	{
		"MT_VWREF",
		-1,             // doomednum
		S_VWREF,         // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		3,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		42*FRACUNIT,    // radius
		12*FRACUNIT,    // height
		1,              // display offset
		1000,           // mass
		8,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOCLIP|MF_NOCLIPHEIGHT|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_VWREB",
		-1,             // doomednum
		S_VWREB,         // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		3,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		42*FRACUNIT,    // radius
		12*FRACUNIT,    // height
		-1,             // display offset
		1000,           // mass
		8,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOCLIP|MF_NOCLIPHEIGHT|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_PROJECTORLIGHT",
		-1,             // doomednum
		S_PROJECTORLIGHT1, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		3,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		42*FRACUNIT,    // radius
		52*FRACUNIT,    // height
		-1,             // display offset
		1000,           // mass
		8,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOCLIP|MF_NOCLIPHEIGHT|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_FBOMB",
		-1,                // doomednum
		S_FBOMB1,          // spawnstate
		1,                 // spawnhealth
		S_NULL,            // seestate
		sfx_s3k51,         // seesound
		0,                 // reactiontime
		sfx_None,          // attacksound
		S_NULL,            // painstate
		0,                 // painchance
		sfx_None,          // painsound
		S_NULL,            // meleestate
		S_NULL,            // missilestate
		S_FBOMB_EXPL1,     // deathstate
		S_NULL,            // xdeathstate
		sfx_s3k4e,         // deathsound
		20*FRACUNIT,       // speed
		24*FRACUNIT,       // radius
		48*FRACUNIT,       // height
		0,                 // display offset
		0,                 // mass
		0,                 // damage
		sfx_None,          // activesound
		MF_NOBLOCKMAP|MF_MISSILE, // flags
		S_NULL             // raisestate
	},

	{
		"MT_TNTDUST",
		-1,                // doomednum
		S_TNTDUST_1,       // spawnstate
		1,                 // spawnhealth
		S_NULL,            // seestate
		sfx_None,          // seesound
		0,                 // reactiontime
		sfx_None,          // attacksound
		S_NULL,            // painstate
		0,                 // painchance
		sfx_None,          // painsound
		S_NULL,            // meleestate
		S_NULL,            // missilestate
		S_NULL,            // deathstate
		S_NULL,            // xdeathstate
		sfx_None,          // deathsound
		20*FRACUNIT,       // speed
		16*FRACUNIT,       // radius
		32*FRACUNIT,       // height
		0,                 // display offset
		100,               // mass
		0,                 // damage
		sfx_None,          // activesound
		MF_NOGRAVITY|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL             // raisestate
	},
	{
		"MT_FSGNA",
		-1,                // doomednum
		S_FSGNA,           // spawnstate
		1,                 // spawnhealth
		S_NULL,            // seestate
		sfx_None,          // seesound
		0,                 // reactiontime
		sfx_None,          // attacksound
		S_NULL,            // painstate
		0,                 // painchance
		sfx_None,          // painsound
		S_NULL,            // meleestate
		S_NULL,            // missilestate
		S_NULL,            // deathstate
		S_NULL,            // xdeathstate
		sfx_mspogo,        // deathsound
		0,                 // speed
		124*FRACUNIT,      // radius
		124*FRACUNIT,      // height
		0,                 // display offset
		0,                 // mass
		0,                 // damage
		sfx_None,          // activesound
		MF_NOGRAVITY|MF_NOCLIP|MF_NOCLIPHEIGHT|MF_SCENERY, // flags
		S_NULL             // raisestate
	},

	{
		"MT_FSGNB",
		-1,                // doomednum
		S_FSGNB,           // spawnstate
		1,                 // spawnhealth
		S_NULL,            // seestate
		sfx_None,          // seesound
		0,                 // reactiontime
		sfx_None,          // attacksound
		S_NULL,            // painstate
		0,                 // painchance
		sfx_None,          // painsound
		S_NULL,            // meleestate
		S_NULL,            // missilestate
		S_FSGNC,           // deathstate
		S_FSGND,           // xdeathstate
		sfx_None,          // deathsound
		0,                 // speed
		74*FRACUNIT,       // radius
		320*FRACUNIT,      // height
		0,                 // display offset
		0,                 // mass
		0,                 // damage
		sfx_None,          // activesound
		MF_NOGRAVITY|MF_NOCLIP|MF_NOCLIPHEIGHT|MF_SCENERY|MF_SOLID, // flags
		S_NULL             // raisestate
	},

	{
		"MT_FANGWAYPOINT",
		294,               // doomednum
		S_INVISIBLE,       // spawnstate
		1000,              // spawnhealth
		S_NULL,            // seestate
		sfx_None,          // seesound
		0,                 // reactiontime
		sfx_None,          // attacksound
		S_NULL,            // painstate
		0,                 // painchance
		sfx_None,          // painsound
		S_NULL,            // meleestate
		S_NULL,            // missilestate
		S_NULL,            // deathstate
		S_NULL,            // xdeathstate
		sfx_None,          // deathsound
		0,                 // speed
		FRACUNIT,          // radius
		FRACUNIT,          // height
		0,                 // display offset
		0,                 // mass
		0,                 // damage
		sfx_None,          // activesound
		MF_NOGRAVITY|MF_NOBLOCKMAP|MF_SCENERY, // flags
		S_NULL             // raisestate
	},

	{
		"MT_BLACKEGGMAN",
		206,               // doomednum
		S_BLACKEGG_STND,   // spawnstate
		8,                 // spawnhealth
		S_BLACKEGG_WALK1,  // seestate
		sfx_None,          // seesound
		8*TICRATE,         // reactiontime
		sfx_None,          // attacksound
		S_BLACKEGG_PAIN1,  // painstate
		0,                 // painchance
		sfx_None,          // painsound
		S_BLACKEGG_HITFACE1, // meleestate
		S_BLACKEGG_MISSILE1, // missilestate
		S_BLACKEGG_DIE1,   // deathstate
		S_BLACKEGG_GOOP,   // xdeathstate
		sfx_None,          // deathsound
		1,                 // speed
		48*FRACUNIT,       // radius
		160*FRACUNIT,      // height
		0,                 // display offset
		0,                 // mass
		3,                 // damage
		sfx_None,          // activesound
		MF_SPECIAL|MF_BOSS,// flags
		S_BLACKEGG_JUMP1   // raisestate
	},

	{
		"MT_BLACKEGGMAN_HELPER",
		-1,                // doomednum
		S_BLACKEGG_HELPER, // spawnstate
		8,                 // spawnhealth
		S_NULL,            // seestate
		sfx_None,          // seesound
		0,                 // reactiontime
		sfx_None,          // attacksound
		S_NULL,            // painstate
		0,                 // painchance
		sfx_None,          // painsound
		S_NULL,            // meleestate
		S_NULL,            // missilestate
		S_NULL,            // deathstate
		S_NULL,            // xdeathstate
		sfx_None,          // deathsound
		1,                 // speed
		48*FRACUNIT,       // radius
		32*FRACUNIT,       // height
		0,                 // display offset
		0,                 // mass
		1,                 // damage
		sfx_None,          // activesound
		MF_SOLID|MF_NOGRAVITY,          // flags
		S_NULL             // raisestate
	},

	{
		"MT_BLACKEGGMAN_GOOPFIRE",
		-1,             // doomednum
		S_BLACKEGG_GOOP1, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_BLACKEGG_GOOP3, // deathstate
		S_NULL,         // xdeathstate
		sfx_ghit,       // deathsound
		30*FRACUNIT,    // speed
		11*FRACUNIT,    // radius
		8*FRACUNIT,     // height
		100,            // display offset
		0,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_MISSILE|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BLACKEGGMAN_MISSILE",
		-1,             // doomednum
		S_BLACKEGG_MISSILE, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_BOSSEXPLODE,  // deathstate
		S_NULL,         // xdeathstate
		sfx_bexpld,     // deathsound
		10*FRACUNIT,    // speed
		24*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		0,              // mass
		1,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_MISSILE|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CYBRAKDEMON",
		209,                // doomednum
		S_CYBRAKDEMON_IDLE, // spawnstate
		12,                 // spawnhealth
		S_CYBRAKDEMON_WALK1,// seestate
		sfx_None,           // seesound
		15,                 // reactiontime
		sfx_None,           // attacksound
		S_CYBRAKDEMON_PAIN1,// painstate
		0,                  // painchance
		sfx_behurt,         // painsound
		S_CYBRAKDEMON_CHOOSE_ATTACK2, // meleestate
		S_CYBRAKDEMON_CHOOSE_ATTACK1, // missilestate
		S_CYBRAKDEMON_DIE1, // deathstate
		S_NULL,             // xdeathstate
		sfx_s3kb4,          // deathsound
		40,                 // speed
		48*FRACUNIT,        // radius
		160*FRACUNIT,       // height
		0,                  // display offset
		100,                // mass
		1,                  // damage
		sfx_bewar1,         // activesound
		MF_SPECIAL|MF_BOSS|MF_SHOOTABLE, // flags
		S_NULL              // raisestate
	},

	{
		"MT_CYBRAKDEMON_ELECTRIC_BARRIER",
		-1,             // doomednum
		S_CYBRAKDEMONELECTRICBARRIER_INIT1, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_s3k79,      // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_CYBRAKDEMONELECTRICBARRIER_DIE1, // deathstate
		S_NULL,         // xdeathstate
		sfx_fizzle,     // deathsound
		10*FRACUNIT,    // speed
		24*FRACUNIT,    // radius
		80*FRACUNIT,    // height
		0,              // display offset
		DMG_ELECTRIC,   // mass
		1,              // damage
		sfx_beelec,     // activesound
		MF_PAIN|MF_FIRE|MF_NOGRAVITY|MF_PUSHABLE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CYBRAKDEMON_MISSILE",
		-1,             // doomednum
		S_CYBRAKDEMONMISSILE, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_brakrl,     // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_CYBRAKDEMONMISSILE_EXPLODE1, // deathstate
		S_NULL,         // xdeathstate
		sfx_brakrx,     // deathsound
		40*FRACUNIT,    // speed
		11*FRACUNIT,    // radius
		8*FRACUNIT,     // height
		0,              // display offset
		0,              // mass
		32*FRACUNIT,    // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_MISSILE|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CYBRAKDEMON_FLAMESHOT",
		-1,             // doomednum
		S_CYBRAKDEMONFLAMESHOT_FLY1, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_s3kc2s,     // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_CYBRAKDEMONFLAMESHOT_DIE, // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		20*FRACUNIT,    // speed
		24*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		DMG_FIRE,       // mass
		1,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_MISSILE|MF_PAIN|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CYBRAKDEMON_FLAMEREST",
		-1,             // doomednum
		S_CYBRAKDEMONFLAMEREST, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_s3kc2s,     // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		MT_NULL,        // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL, // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		20*FRACUNIT,    // speed
		24*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		DMG_FIRE,       // mass
		1,              // damage
		sfx_None,       // activesound
		MF_PAIN|MF_FIRE|MF_RUNSPAWNFUNC, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CYBRAKDEMON_TARGET_RETICULE",
		-1,             // doomednum
		S_CYBRAKDEMONTARGETRETICULE1, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_BOSSEXPLODE,  // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		10*FRACUNIT,    // speed
		32*FRACUNIT,    // radius
		64*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		1,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOGRAVITY|MF_RUNSPAWNFUNC, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CYBRAKDEMON_TARGET_DOT",
		-1,             // doomednum
		S_CYBRAKDEMONTARGETDOT, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_BOSSEXPLODE,  // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		10*FRACUNIT,    // speed
		32*FRACUNIT,    // radius
		64*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		1,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOCLIPHEIGHT, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CYBRAKDEMON_NAPALM_BOMB_LARGE",
		-1,             // doomednum
		S_CYBRAKDEMONNAPALMBOMBLARGE_FLY1, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_s3k81,      // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		20*TICRATE,     // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_CYBRAKDEMONNAPALMBOMBLARGE_DIE1, // deathstate
		S_NULL,         // xdeathstate
		sfx_s3k4e,      // deathsound
		10*FRACUNIT,    // speed
		24*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		0,              // mass
		48*FRACUNIT,    // damage
		sfx_s3k5d,      // activesound
		MF_NOBLOCKMAP|MF_MISSILE|MF_BOUNCE|MF_GRENADEBOUNCE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CYBRAKDEMON_NAPALM_BOMB_SMALL",
		-1,             // doomednum
		S_CYBRAKDEMONNAPALMBOMBSMALL, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_CYBRAKDEMONNAPALMBOMBSMALL_DIE1, // deathstate
		S_NULL,         // xdeathstate
		sfx_s3k70,      // deathsound
		10*FRACUNIT,    // speed
		24*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		0,              // mass
		32*FRACUNIT,    // damage
		sfx_s3k99,       // activesound
		MF_NOBLOCKMAP|MF_MISSILE|MF_BOUNCE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CYBRAKDEMON_NAPALM_FLAMES",
		-1,             // doomednum
		S_CYBRAKDEMONNAPALMFLAME_FLY1, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_CYBRAKDEMONNAPALMFLAME_DIE, // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		10*FRACUNIT,    // speed
		24*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		0,              // mass
		1,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_MISSILE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CYBRAKDEMON_VILE_EXPLOSION",
		-1,             // doomednum
		S_CYBRAKDEMONVILEEXPLOSION1, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_s3kb4,      // deathsound
		1*FRACUNIT,     // speed
		8*FRACUNIT,     // radius
		8*FRACUNIT,     // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},


	{
		"MT_METALSONIC_RACE",
		207,                // doomednum
		S_METALSONIC_RACE,  // spawnstate
		8,                  // spawnhealth
		S_NULL,             // seestate
		sfx_None,           // seesound
		0,                  // reactiontime
		sfx_None,           // attacksound
		S_NULL,             // painstate
		0,                  // painchance
		sfx_None,           // painsound
		S_NULL,             // meleestate
		S_NULL,             // missilestate
		S_PLAY_DEAD,        // deathstate
		S_NULL,             // xdeathstate
		sfx_None,           // deathsound
		0,                  // speed
		16*FRACUNIT,        // radius
		48*FRACUNIT,        // height
		0,                  // display offset
		0,                  // mass
		0,                  // damage
		sfx_None,           // activesound
		MF_NOGRAVITY|MF_NOCLIPHEIGHT, // flags
		S_NULL              // raisestate
	},

	{
		"MT_METALSONIC_BATTLE",
		208,                // doomednum
		S_METALSONIC_FLOAT, // spawnstate
		8,                  // spawnhealth
		S_METALSONIC_DASH,  // seestate
		sfx_s3k54,          // seesound
		0,                  // reactiontime
		sfx_bechrg,         // attacksound
		S_METALSONIC_PAIN,  // painstate
		S_METALSONIC_VECTOR,// painchance
		sfx_dmpain,         // painsound
		S_METALSONIC_BADBOUNCE, // meleestate
		S_METALSONIC_SHOOT, // missilestate
		S_METALSONIC_DEATH1,// deathstate
		S_METALSONIC_FLEE1, // xdeathstate
		sfx_s3kb4,          // deathsound
		MT_ENERGYBALL,      // speed
		16*FRACUNIT,        // radius
		48*FRACUNIT,        // height
		0,                  // display offset
		0,                  // mass
		3,                  // damage
		sfx_mswarp,         // activesound
		MF_NOGRAVITY|MF_BOSS|MF_SLIDEME, // flags
		S_METALSONIC_RAISE  // raisestate
	},

	{
		"MT_MSSHIELD_FRONT",
		-1,             // doomednum
		S_MSSHIELD_F1,  // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		32*FRACUNIT,    // radius
		52*FRACUNIT,    // height
		1,              // display offset
		0,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOCLIPHEIGHT|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_MSGATHER",
		-1,             // doomednum
		S_JETFUME1,     // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		24*FRACUNIT,    // speed
		6*FRACUNIT,     // radius
		12*FRACUNIT,    // height
		0,              // display offset
		0,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOCLIPHEIGHT|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_RING",
		300,            // doomednum
		S_RING,         // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		MT_FLINGRING,   // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_SPRK1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_itemup,     // deathsound
		38*FRACUNIT,    // speed
		16*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SLIDEME|MF_SPECIAL|MF_NOGRAVITY|MF_NOCLIPHEIGHT, // flags
		S_NULL          // raisestate
	},

	{
		"MT_FLINGRING",
		-1,             // doomednum
		S_RING,         // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		MT_FLINGRING,   // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		MT_RING,        // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_SPRK1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_itemup,     // deathsound
		38*FRACUNIT,    // speed
		15*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SLIDEME|MF_SPECIAL, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BLUESPHERE",
		1706,           // doomednum
		S_BLUESPHERE,   // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		MT_FLINGBLUESPHERE,  // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_BLUESPHERESPARK, // deathstate
		S_NULL,         // xdeathstate
		sfx_s3k65,      // deathsound
		38*FRACUNIT,    // speed
		16*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SLIDEME|MF_SPECIAL|MF_NOGRAVITY|MF_NOCLIPHEIGHT, // flags
		S_BLUESPHEREBONUS // raisestate
	},

	{
		"MT_FLINGBLUESPHERE",
		-1,             // doomednum
		S_BLUESPHERE,         // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		MT_FLINGBLUESPHERE,   // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		MT_BLUESPHERE,        // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_BLUESPHERESPARK, // deathstate
		S_NULL,         // xdeathstate
		sfx_s3k65,     // deathsound
		38*FRACUNIT,    // speed
		16*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SLIDEME|MF_SPECIAL, // flags
		S_BLUESPHEREBONUS // raisestate
	},

	{
		"MT_BOMBSPHERE",
		520,            // doomednum
		S_BOMBSPHERE1,  // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		MT_NULL,        // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_SONIC3KBOSSEXPLOSION1, // deathstate
		S_NULL,         // xdeathstate
		sfx_cybdth,     // deathsound
		38*FRACUNIT,    // speed
		16*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SLIDEME|MF_SPECIAL|MF_NOGRAVITY|MF_NOCLIPHEIGHT, // flags
		S_NULL          // raisestate
	},

	{
		"MT_REDTEAMRING",
		308,            // doomednum
		S_TEAMRING,     // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		MT_FLINGRING,   // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_SPRK1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_itemup,     // deathsound
		38*FRACUNIT,    // speed
		16*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SLIDEME|MF_SPECIAL|MF_NOGRAVITY|MF_NOCLIPHEIGHT, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BLUETEAMRING",
		309,            // doomednum
		S_TEAMRING,     // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		MT_FLINGRING,   // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_SPRK1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_itemup,     // deathsound
		38*FRACUNIT,    // speed
		16*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SLIDEME|MF_SPECIAL|MF_NOGRAVITY|MF_NOCLIPHEIGHT, // flags
		S_NULL          // raisestate
	},

	{
		"MT_TOKEN",
		312,            // doomednum
		S_TOKEN,         // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_SPRK1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,     // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		1,              // damage
		sfx_None,       // activesound
		MF_SPECIAL|MF_NOGRAVITY|MF_NOCLIPHEIGHT, // flags
		S_NULL          // raisestate
	},

	{
		"MT_REDFLAG",
		310,            // doomednum
		S_REDFLAG,      // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_lvpass,     // deathsound
		8,              // speed
		24*FRACUNIT,    // radius
		64*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SPECIAL,     // flags
		S_NULL          // raisestate
	},

	{
		"MT_BLUEFLAG",
		311,            // doomednum
		S_BLUEFLAG,     // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_lvpass,     // deathsound
		8,              // speed
		24*FRACUNIT,    // radius
		64*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SPECIAL,     // flags
		S_NULL          // raisestate
	},

	{
		"MT_EMBLEM",
		322,            // doomednum
		S_EMBLEM1,      // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_SPRK1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_ncitem,     // deathsound
		1,              // speed
		16*FRACUNIT,     // radius
		30*FRACUNIT,    // height
		0,              // display offset
		4,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SPECIAL|MF_NOGRAVITY|MF_NOCLIPHEIGHT, // flags
		S_NULL          // raisestate
	},

	{
		"MT_EMERALD1",
		313,            // doomednum
		S_CEMG1,        // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_SPRK1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_cgot,       // deathsound
		EMERALD1,       // speed
		16*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOGRAVITY|MF_SPECIAL, // flags
		S_NULL          // raisestate
	},
	{
		"MT_EMERALD2",
		314,            // doomednum
		S_CEMG2,        // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_SPRK1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_cgot,       // deathsound
		EMERALD2,       // speed
		16*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOGRAVITY|MF_SPECIAL, // flags
		S_NULL          // raisestate
	},
	{
		"MT_EMERALD3",
		315,            // doomednum
		S_CEMG3,        // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_SPRK1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_cgot,       // deathsound
		EMERALD3,       // speed
		16*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOGRAVITY|MF_SPECIAL, // flags
		S_NULL          // raisestate
	},
	{
		"MT_EMERALD4",
		316,            // doomednum
		S_CEMG4,        // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_SPRK1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_cgot,       // deathsound
		EMERALD4,       // speed
		16*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOGRAVITY|MF_SPECIAL, // flags
		S_NULL          // raisestate
	},
	{
		"MT_EMERALD5",
		317,            // doomednum
		S_CEMG5,        // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_SPRK1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_cgot,       // deathsound
		EMERALD5,       // speed
		16*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOGRAVITY|MF_SPECIAL, // flags
		S_NULL          // raisestate
	},
	{
		"MT_EMERALD6",
		318,            // doomednum
		S_CEMG6,        // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_SPRK1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_cgot,       // deathsound
		EMERALD6,       // speed
		16*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOGRAVITY|MF_SPECIAL, // flags
		S_NULL          // raisestate
	},
	{
		"MT_EMERALD7",
		319,            // doomednum
		S_CEMG7,        // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_SPRK1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_cgot,       // deathsound
		EMERALD7,       // speed
		16*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOGRAVITY|MF_SPECIAL, // flags
		S_NULL          // raisestate
	},

	{
		"MT_EMERHUNT",
		320,            // doomednum
		S_SHRD1,        // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_SPRK1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_cgot,       // deathsound
		8,              // speed
		12*FRACUNIT,    // radius
		42*FRACUNIT,    // height
		0,              // display offset
		4,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SPECIAL|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_EMERALDSPAWN",
		321,            // doomednum
		S_INVISIBLE,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8,              // radius
		8,              // height
		0,              // display offset
		10,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOSECTOR,  // flags
		S_NULL          // raisestate
	},

	{
		"MT_FLINGEMERALD",
		-1,             // doomednum
		S_CEMG1,        // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_SPRK1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_cgot,       // deathsound
		60*FRACUNIT,    // speed
		16*FRACUNIT,    // radius
		48*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SLIDEME|MF_SPECIAL, // flags
		S_NULL          // raisestate
	},

	{
		"MT_FAN",
		540,            // doomednum
		S_FAN,          // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		8*FRACUNIT,     // height
		0,              // display offset
		5*FRACUNIT,     // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SOLID,       // flags
		S_NULL          // raisestate
	},

	{
		"MT_STEAM",
		541,            // doomednum
		S_STEAM1,       // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_steam2,     // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_steam1,     // deathsound
		0,              // speed
		32*FRACUNIT,    // radius
		16*FRACUNIT,    // height
		0,              // display offset
		20*FRACUNIT,    // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SPECIAL,     // flags
		S_NULL          // raisestate
	},

	{
		"MT_BUMPER",
		542,            // doomednum
		S_BUMPER,       // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		5,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		-1,             // painchance
		sfx_s3kaa,      // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		32*FRACUNIT,    // radius
		64*FRACUNIT,    // height
		0,              // display offset
		16*FRACUNIT,    // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SPRING|MF_NOGRAVITY, // flags
		S_BUMPERHIT     // raisestate
	},

	{
		"MT_BALLOON",
		543,            // doomednum
		S_BALLOON,      // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		2,              // painchance
		sfx_s3k77,      // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_BALLOONPOP2,  // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		32*FRACUNIT,    // radius
		64*FRACUNIT,    // height
		0,              // display offset
		20*FRACUNIT,    // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SPRING|MF_NOGRAVITY, // flags
		S_BALLOONPOP1   // raisestate
	},

	{
		"MT_YELLOWSPRING",
		550,            // doomednum
		S_YELLOWSPRING, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_spring,     // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		20*FRACUNIT,    // radius
		16*FRACUNIT,    // height
		0,              // display offset
		20*FRACUNIT,    // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SPRING, // flags
		S_YELLOWSPRING2 // raisestate
	},

	{
		"MT_REDSPRING",
		551,            // doomednum
		S_REDSPRING,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_spring,     // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		20*FRACUNIT,    // radius
		16*FRACUNIT,    // height
		0,              // display offset
		32*FRACUNIT,    // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SPRING, // flags
		S_REDSPRING2    // raisestate
	},

	{
		"MT_BLUESPRING",
		552,            // doomednum
		S_BLUESPRING,   // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_spring,     // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		20*FRACUNIT,    // radius
		16*FRACUNIT,    // height
		0,              // display offset
		11*FRACUNIT,    // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SPRING, // flags
		S_BLUESPRING2   // raisestate
	},

	{
		"MT_YELLOWDIAG",
		555,            // doomednum
		S_YDIAG1,       // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_spring,     // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		16*FRACUNIT,    // height
		0,              // display offset
		20*FRACUNIT,    // mass
		20*FRACUNIT,    // damage
		sfx_None,       // activesound
		MF_SPRING, // flags
		S_YDIAG2        // raisestate
	},

	{
		"MT_REDDIAG",
		556,            // doomednum
		S_RDIAG1,       // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_spring,     // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		16*FRACUNIT,    // height
		0,              // display offset
		32*FRACUNIT,    // mass
		32*FRACUNIT,    // damage
		sfx_None,       // activesound
		MF_SPRING, // flags
		S_RDIAG2        // raisestate
	},

	{
		"MT_BLUEDIAG",
		557,            // doomednum
		S_BDIAG1,       // spawnstate
		1,              // spawnhealth
		S_BDIAG2,       // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_spring,     // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		16*FRACUNIT,    // height
		0,              // display offset
		11*FRACUNIT,    // mass
		11*FRACUNIT,    // damage
		sfx_None,       // activesound
		MF_SPRING, // flags
		S_BDIAG2        // raisestate
	},

	{
		"MT_YELLOWHORIZ",
		558,            // doomednum
		S_YHORIZ1,      // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_spring,     // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		0,              // mass
		36*FRACUNIT,    // damage
		sfx_None,       // activesound
		MF_SPRING|MF_NOGRAVITY, // flags
		S_YHORIZ2       // raisestate
	},

	{
		"MT_REDHORIZ",
		559,            // doomednum
		S_RHORIZ1,      // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_spring,     // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		0,              // mass
		72*FRACUNIT,    // damage
		sfx_None,       // activesound
		MF_SPRING|MF_NOGRAVITY, // flags
		S_RHORIZ2       // raisestate
	},

	{
		"MT_BLUEHORIZ",
		560,            // doomednum
		S_BHORIZ1,      // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_spring,     // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		0,              // mass
		11*FRACUNIT,    // damage
		sfx_None,       // activesound
		MF_SPRING|MF_NOGRAVITY, // flags
		S_BHORIZ2       // raisestate
	},

	{
		"MT_BOOSTERSEG",
		-1,             // doomednum
		S_INVISIBLE,    // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		28*FRACUNIT,    // radius
		16*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOCLIPHEIGHT|MF_NOCLIP,  // flags
		S_NULL          // raisestate
	},

	{
		"MT_BOOSTERROLLER",
		-1,             // doomednum
		S_INVISIBLE,    // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		14*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOCLIPHEIGHT|MF_NOCLIP,    // flags
		S_NULL          // raisestate
	},

	{
		"MT_YELLOWBOOSTER",
		544,            // doomednum
		S_INVISIBLE,    // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		3,              // painchance
		sfx_cdfm62,     // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		28*FRACUNIT,    // radius
		FRACUNIT,       // height
		0,              // display offset
		0,              // mass
		36*FRACUNIT,    // damage
		sfx_None,       // activesound
		MF_SPRING|MF_NOGRAVITY, // flags
		S_BOOSTERSOUND  // raisestate
	},

	{
		"MT_REDBOOSTER",
		545,            // doomednum
		S_INVISIBLE,    // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		3,              // painchance
		sfx_cdfm62,     // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		28*FRACUNIT,    // radius
		FRACUNIT,       // height
		0,              // display offset
		0,              // mass
		72*FRACUNIT,    // damage
		sfx_None,       // activesound
		MF_SPRING|MF_NOGRAVITY, // flags
		S_BOOSTERSOUND  // raisestate
	},

	{
		"MT_BUBBLES",
		500,            // doomednum
		S_BUBBLES1,     // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		8*FRACUNIT,     // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY|MF_RUNSPAWNFUNC, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SIGN",
		501,            // doomednum
		S_SIGN,         // spawnstate
		1000,           // spawnhealth
		S_PLAY_SIGN,    // seestate
		sfx_lvpass,     // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_SIGNPLAYER,   // painstate
		MT_SPARK,       // painchance
		sfx_s3kb8,      // painsound
		S_EGGMANSIGN,   // meleestate
		S_CLEARSIGN,    // missilestate
		S_SIGNSTOP,     // deathstate
		S_NULL,         // xdeathstate
		sfx_s3k64,      // deathsound
		8,              // speed
		36*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOCLIP|MF_SCENERY|MF_BOUNCE|MF_RUNSPAWNFUNC, // flags
		S_SIGNBOARD     // raisestate
	},

	{
		"MT_SPIKEBALL",
		521,            // doomednum
		S_SPIKEBALL1,   // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		10*FRACUNIT,    // speed
		12*FRACUNIT,    // radius
		8*FRACUNIT,     // height
		0,              // display offset
		DMG_SPIKE,      // mass
		1,              // damage
		sfx_None,       // activesound
		MF_PAIN|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SPINFIRE",
		-1,             // doomednum
		S_SPINFIRE1,    // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		14*FRACUNIT,    // height
		0,              // display offset
		DMG_FIRE,       // mass
		1,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_MISSILE|MF_NOGRAVITY|MF_FIRE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SPIKE",
		523,            // doomednum
		S_SPIKE1,       // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_s3k64,      // painsound
		S_SPIKE4,       // meleestate
		S_NULL,         // missilestate
		S_SPIKED1,      // deathstate
		S_SPIKED2,      // xdeathstate
		sfx_mspogo,     // deathsound
		2*TICRATE,      // speed
		8*FRACUNIT,     // radius
		32*FRACUNIT,    // height
		0,              // display offset
		DMG_SPIKE,      // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_SCENERY|MF_NOCLIPHEIGHT,  // flags
		S_NULL          // raisestate
	},

	{
		"MT_WALLSPIKE",
		522,            // doomednum
		S_WALLSPIKE1,   // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_s3k64,      // painsound
		S_WALLSPIKE4,   // meleestate
		S_NULL,         // missilestate
		S_WALLSPIKED1,  // deathstate
		S_WALLSPIKED2,  // xdeathstate
		sfx_mspogo,     // deathsound
		2*TICRATE,      // speed
		16*FRACUNIT,    // radius
		14*FRACUNIT,    // height
		0,              // display offset
		DMG_SPIKE,      // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOGRAVITY|MF_SCENERY|MF_NOCLIPHEIGHT|MF_PAPERCOLLISION,  // flags
		S_NULL          // raisestate
	},

	{
		"MT_WALLSPIKEBASE",
		-1,            // doomednum
		S_WALLSPIKEBASE, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		7*FRACUNIT,     // radius
		14*FRACUNIT,    // height
		0,              // display offset
		4,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOCLIP|MF_NOCLIPTHING,  // flags
		S_NULL          // raisestate
	},

	{
		"MT_STARPOST",
		502,            // doomednum
		S_STARPOST_IDLE, // spawnstate
		1,              // spawnhealth
		S_STARPOST_FLASH, // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_STARPOST_STARTSPIN, // painstate
		0,              // painchance
		sfx_strpst,     // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		64*FRACUNIT,    // radius
		128*FRACUNIT,   // height
		0,              // display offset
		4,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SPECIAL,     // flags
		S_NULL          // raisestate
	},

	{
		"MT_BIGMINE",
		1012,           // doomednum
		S_BIGMINE_IDLE, // spawnstate
		1,              // spawnhealth
		S_BIGMINE_ALERT1, // seestate
		sfx_s3k5c,      // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_s3k86,      // painsound
		S_BIGMINE_SET1, // meleestate
		S_NULL,         // missilestate
		S_BIGMINE_SET2, // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		2*FRACUNIT,     // speed
		28*FRACUNIT,    // radius
		56*FRACUNIT,    // height
		0,              // display offset
		MT_UWEXPLODE,   // mass
		0,              // damage
		sfx_s3k9e,      // activesound
		MF_SPECIAL|MF_NOGRAVITY|MF_SHOOTABLE|MF_ENEMY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BLASTEXECUTOR",
		756,            // doomednum
		S_INVISIBLE,    // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		32*FRACUNIT,    // radius
		16*FRACUNIT,    // height
		0,              // display offset
		4,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SHOOTABLE|MF_NOGRAVITY|MF_NOCLIPTHING, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CANNONLAUNCHER",
		1123,           // doomednum
		S_CANNONLAUNCHER1, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		2*TICRATE,      // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		TICRATE,        // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_XPLD1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		2*FRACUNIT,     // radius
		4*FRACUNIT,     // height
		0,              // display offset
		0,              // mass
		1,              // damage
		sfx_pop,        // activesound
		MF_NOGRAVITY|MF_NOSECTOR|MF_NOBLOCKMAP, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BOXSPARKLE",
		-1,             // doomednum
		S_BOXSPARKLE1,  // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		3*FRACUNIT,     // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOGRAVITY|MF_SCENERY|MF_NOBLOCKMAP|MF_NOCLIPHEIGHT, // flags
		S_NULL          // raisestate
	},

	{
		"MT_RING_BOX",
		400,            // doomednum
		S_RING_BOX,     // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_RING_BOX,     // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_BOX_POP1,     // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		1,              // speed
		18*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		MT_RING_ICON,   // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SHOOTABLE|MF_MONITOR, // flags
		S_NULL          // raisestate
	},

	{
		"MT_PITY_BOX",
		401,            // doomednum
		S_PITY_BOX,     // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_PITY_BOX,     // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_BOX_POP1,     // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		1,              // speed
		18*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		MT_PITY_ICON,   // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SHOOTABLE|MF_MONITOR, // flags
		S_NULL          // raisestate
	},

	{
		"MT_ATTRACT_BOX",
		402,            // doomednum
		S_ATTRACT_BOX,  // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_ATTRACT_BOX,  // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_BOX_POP1,     // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		1,              // speed
		18*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		MT_ATTRACT_ICON,// damage
		sfx_None,       // activesound
		MF_SOLID|MF_SHOOTABLE|MF_MONITOR, // flags
		S_NULL          // raisestate
	},

	{
		"MT_FORCE_BOX",
		403,            // doomednum
		S_FORCE_BOX,    // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_FORCE_BOX,    // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_BOX_POP1,     // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		1,              // speed
		18*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		MT_FORCE_ICON,  // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SHOOTABLE|MF_MONITOR, // flags
		S_NULL          // raisestate
	},

	{
		"MT_ARMAGEDDON_BOX",
		404,            // doomednum
		S_ARMAGEDDON_BOX, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_ARMAGEDDON_BOX, // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_BOX_POP1,     // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		1,              // speed
		18*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		MT_ARMAGEDDON_ICON, // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SHOOTABLE|MF_MONITOR, // flags
		S_NULL          // raisestate
	},

	{
		"MT_WHIRLWIND_BOX",
		405,            // doomednum
		S_WHIRLWIND_BOX, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_WHIRLWIND_BOX, // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_BOX_POP1,     // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		1,              // speed
		18*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		MT_WHIRLWIND_ICON, // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SHOOTABLE|MF_MONITOR, // flags
		S_NULL          // raisestate
	},

	{
		"MT_ELEMENTAL_BOX",
		406,            // doomednum
		S_ELEMENTAL_BOX,     // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_ELEMENTAL_BOX,     // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_BOX_POP1,     // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		1,              // speed
		18*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		MT_ELEMENTAL_ICON, // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SHOOTABLE|MF_MONITOR, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SNEAKERS_BOX",
		407,            // doomednum
		S_SNEAKERS_BOX, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_SNEAKERS_BOX, // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_BOX_POP1,     // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		1,              // speed
		18*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		MT_SNEAKERS_ICON, // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SHOOTABLE|MF_MONITOR, // flags
		S_NULL          // raisestate
	},

	{
		"MT_INVULN_BOX",
		408,            // doomednum
		S_INVULN_BOX,   // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_INVULN_BOX,   // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_BOX_POP1,     // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		1,              // speed
		18*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		MT_INVULN_ICON, // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SHOOTABLE|MF_MONITOR, // flags
		S_NULL          // raisestate
	},

	{
		"MT_1UP_BOX",
		409,            // doomednum
		S_1UP_BOX,      // spawnstate
		1,              // spawnhealth
		S_PLAY_BOX1,    // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_1UP_BOX,      // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_BOX_POP1,     // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		1,              // speed
		18*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		MT_1UP_ICON,    // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SHOOTABLE|MF_MONITOR, // flags
		S_NULL          // raisestate
	},

	{
		"MT_EGGMAN_BOX",
		410,            // doomednum
		S_EGGMAN_BOX,   // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_EGGMAN_BOX,   // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_BOX_POP1,     // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		0,              // speed
		18*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		MT_EGGMAN_ICON, // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SHOOTABLE|MF_MONITOR, // flags
		S_NULL          // raisestate
	},

	{
		"MT_MIXUP_BOX",
		411,            // doomednum
		S_MIXUP_BOX,    // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_MIXUP_BOX,    // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_BOX_POP1,     // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		1,              // speed
		18*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		MT_MIXUP_ICON,  // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SHOOTABLE|MF_MONITOR, // flags
		S_NULL          // raisestate
	},

	{
		"MT_MYSTERY_BOX",
		-1, //412,      // doomednum
		S_MYSTERY_BOX,  // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_MYSTERY_BOX,  // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_BOX_POP1,     // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		0,              // speed
		18*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		MT_UNKNOWN,     // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SHOOTABLE|MF_MONITOR, // flags
		S_NULL          // raisestate
	},

	{
		"MT_GRAVITY_BOX",
		413,            // doomednum
		S_GRAVITY_BOX,  // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_GRAVITY_BOX,  // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_BOX_POP1,     // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		0,              // speed
		18*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		MT_GRAVITY_ICON, // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SHOOTABLE|MF_MONITOR, // flags
		S_NULL          // raisestate
	},

	{
		"MT_RECYCLER_BOX",
		416,            // doomednum
		S_RECYCLER_BOX, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_RECYCLER_BOX, // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_BOX_POP1,     // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		1,              // speed
		18*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		MT_RECYCLER_ICON, // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SHOOTABLE|MF_MONITOR, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SCORE1K_BOX",
		418,            // doomednum
		S_SCORE1K_BOX,  // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_SCORE1K_BOX,  // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_BOX_POP1,     // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		0,              // speed
		18*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		MT_SCORE1K_ICON, // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SHOOTABLE|MF_MONITOR, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SCORE10K_BOX",
		419,            // doomednum
		S_SCORE10K_BOX, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_SCORE10K_BOX, // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_BOX_POP1,     // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		0,              // speed
		18*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		MT_SCORE10K_ICON, // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SHOOTABLE|MF_MONITOR, // flags
		S_NULL          // raisestate
	},

	{
		"MT_FLAMEAURA_BOX",
		420,            // doomednum
		S_FLAMEAURA_BOX, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_FLAMEAURA_BOX, // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_BOX_POP1,     // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		1,              // speed
		18*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		MT_FLAMEAURA_ICON, // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SHOOTABLE|MF_MONITOR, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BUBBLEWRAP_BOX",
		421,            // doomednum
		S_BUBBLEWRAP_BOX, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_BUBBLEWRAP_BOX, // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_BOX_POP1,     // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		1,              // speed
		18*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		MT_BUBBLEWRAP_ICON,  // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SHOOTABLE|MF_MONITOR, // flags
		S_NULL          // raisestate
	},

	{
		"MT_THUNDERCOIN_BOX",
		422,            // doomednum
		S_THUNDERCOIN_BOX, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_THUNDERCOIN_BOX, // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_BOX_POP1,     // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		1,              // speed
		18*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		MT_THUNDERCOIN_ICON,  // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SHOOTABLE|MF_MONITOR, // flags
		S_NULL          // raisestate
	},

	{
		"MT_PITY_GOLDBOX",
		431,            // doomednum
		S_PITY_GOLDBOX, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_monton,     // attacksound
		S_PITY_GOLDBOX, // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_GOLDBOX_OFF1, // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		0,              // speed
		20*FRACUNIT,    // radius
		44*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		MT_PITY_ICON,   // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SHOOTABLE|MF_MONITOR|MF_GRENADEBOUNCE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_ATTRACT_GOLDBOX",
		432,            // doomednum
		S_ATTRACT_GOLDBOX, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_monton,     // attacksound
		S_ATTRACT_GOLDBOX, // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_GOLDBOX_OFF1, // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		0,              // speed
		20*FRACUNIT,    // radius
		44*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		MT_ATTRACT_ICON,// damage
		sfx_None,       // activesound
		MF_SOLID|MF_SHOOTABLE|MF_MONITOR|MF_GRENADEBOUNCE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_FORCE_GOLDBOX",
		433,            // doomednum
		S_FORCE_GOLDBOX, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_monton,     // attacksound
		S_FORCE_GOLDBOX, // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_GOLDBOX_OFF1, // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		0,              // speed
		20*FRACUNIT,    // radius
		44*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		MT_FORCE_ICON,  // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SHOOTABLE|MF_MONITOR|MF_GRENADEBOUNCE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_ARMAGEDDON_GOLDBOX",
		434,            // doomednum
		S_ARMAGEDDON_GOLDBOX, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_monton,     // attacksound
		S_ARMAGEDDON_GOLDBOX, // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_GOLDBOX_OFF1, // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		0,              // speed
		20*FRACUNIT,    // radius
		44*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		MT_ARMAGEDDON_ICON, // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SHOOTABLE|MF_MONITOR|MF_GRENADEBOUNCE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_WHIRLWIND_GOLDBOX",
		435,            // doomednum
		S_WHIRLWIND_GOLDBOX, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_monton,     // attacksound
		S_WHIRLWIND_GOLDBOX, // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_GOLDBOX_OFF1, // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		0,              // speed
		20*FRACUNIT,    // radius
		44*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		MT_WHIRLWIND_ICON, // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SHOOTABLE|MF_MONITOR|MF_GRENADEBOUNCE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_ELEMENTAL_GOLDBOX",
		436,            // doomednum
		S_ELEMENTAL_GOLDBOX, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_monton,     // attacksound
		S_ELEMENTAL_GOLDBOX, // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_GOLDBOX_OFF1, // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		0,              // speed
		20*FRACUNIT,    // radius
		44*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		MT_ELEMENTAL_ICON, // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SHOOTABLE|MF_MONITOR|MF_GRENADEBOUNCE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SNEAKERS_GOLDBOX",
		437,            // doomednum
		S_SNEAKERS_GOLDBOX, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_monton,     // attacksound
		S_SNEAKERS_GOLDBOX, // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_GOLDBOX_OFF1, // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		0,              // speed
		20*FRACUNIT,    // radius
		44*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		MT_SNEAKERS_ICON, // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SHOOTABLE|MF_MONITOR|MF_GRENADEBOUNCE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_INVULN_GOLDBOX",
		438,            // doomednum
		S_INVULN_GOLDBOX, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_monton,     // attacksound
		S_INVULN_GOLDBOX, // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_GOLDBOX_OFF1, // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		0,              // speed
		20*FRACUNIT,    // radius
		44*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		MT_INVULN_ICON, // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SHOOTABLE|MF_MONITOR|MF_GRENADEBOUNCE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_EGGMAN_GOLDBOX",
		440,            // doomednum
		S_EGGMAN_GOLDBOX, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_monton,     // attacksound
		S_EGGMAN_GOLDBOX, // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_GOLDBOX_OFF1, // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		0,              // speed
		20*FRACUNIT,    // radius
		44*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		MT_EGGMAN_ICON, // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SHOOTABLE|MF_MONITOR|MF_GRENADEBOUNCE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_GRAVITY_GOLDBOX",
		443,            // doomednum
		S_GRAVITY_GOLDBOX, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_monton,     // attacksound
		S_GRAVITY_GOLDBOX, // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_GOLDBOX_OFF1, // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		0,              // speed
		20*FRACUNIT,    // radius
		44*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		MT_GRAVITY_ICON, // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SHOOTABLE|MF_MONITOR|MF_GRENADEBOUNCE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_FLAMEAURA_GOLDBOX",
		450,            // doomednum
		S_FLAMEAURA_GOLDBOX, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_monton,     // attacksound
		S_FLAMEAURA_GOLDBOX, // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_GOLDBOX_OFF1, // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		0,              // speed
		20*FRACUNIT,    // radius
		44*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		MT_FLAMEAURA_ICON, // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SHOOTABLE|MF_MONITOR|MF_GRENADEBOUNCE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BUBBLEWRAP_GOLDBOX",
		451,            // doomednum
		S_BUBBLEWRAP_GOLDBOX, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_monton,     // attacksound
		S_BUBBLEWRAP_GOLDBOX, // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_GOLDBOX_OFF1, // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		0,              // speed
		20*FRACUNIT,    // radius
		44*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		MT_BUBBLEWRAP_ICON,  // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SHOOTABLE|MF_MONITOR|MF_GRENADEBOUNCE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_THUNDERCOIN_GOLDBOX",
		452,            // doomednum
		S_THUNDERCOIN_GOLDBOX, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_monton,     // attacksound
		S_THUNDERCOIN_GOLDBOX, // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_GOLDBOX_OFF1, // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		0,              // speed
		20*FRACUNIT,    // radius
		44*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		MT_THUNDERCOIN_ICON,  // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SHOOTABLE|MF_MONITOR|MF_GRENADEBOUNCE, // flags
		S_NULL          // raisestate
	},

	{  		
		"MT_RING_REDBOX",
		414,            // doomednum
		S_RING_REDBOX1, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_RING_REDBOX1, // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_REDBOX_POP1,  // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		0,              // speed
		18*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		MT_RING_ICON,   // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SHOOTABLE|MF_MONITOR, // flags
		S_NULL          // raisestate
	},

	{
		"MT_RING_BLUEBOX",
		415,            // doomednum
		S_RING_BLUEBOX1, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_RING_BLUEBOX1, // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_BLUEBOX_POP1, // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		0,              // speed
		18*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		MT_RING_ICON,   // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SHOOTABLE|MF_MONITOR, // flags
		S_NULL          // raisestate
	},

	{
		"MT_RING_ICON",
		-1,              // doomednum
		S_RING_ICON1,    // spawnstate
		1,               // spawnhealth
		S_NULL,          // seestate
		sfx_itemup,      // seesound
		10,              // reactiontime
		sfx_None,        // attacksound
		S_NULL,          // painstate
		0,               // painchance
		sfx_None,        // painsound
		S_NULL,          // meleestate
		S_NULL,          // missilestate
		S_NULL,          // deathstate
		S_NULL,          // xdeathstate
		sfx_None,        // deathsound
		2*FRACUNIT,      // speed
		8*FRACUNIT,      // radius
		14*FRACUNIT,     // height
		0,               // display offset
		100,             // mass
		62*FRACUNIT,     // damage
		sfx_None,        // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY|MF_NOGRAVITY|MF_BOXICON, // flags
		S_NULL           // raisestate
	},

	{
		"MT_PITY_ICON",
		-1,             // doomednum
		S_PITY_ICON1,   // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_shield,     // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		2*FRACUNIT,     // speed
		8*FRACUNIT,     // radius
		14*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		62*FRACUNIT,    // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY|MF_NOGRAVITY|MF_BOXICON, // flags
		S_NULL          // raisestate
	},

	{
		"MT_ATTRACT_ICON",
		-1,             // doomednum
		S_ATTRACT_ICON1, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_attrsg,     // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		2*FRACUNIT,     // speed
		8*FRACUNIT,     // radius
		14*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		62*FRACUNIT,    // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY|MF_NOGRAVITY|MF_BOXICON, // flags
		S_NULL          // raisestate
	},

	{
		"MT_FORCE_ICON",
		-1,             // doomednum
		S_FORCE_ICON1,  // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_forcsg,     // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		2*FRACUNIT,     // speed
		8*FRACUNIT,     // radius
		14*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		62*FRACUNIT,    // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY|MF_NOGRAVITY|MF_BOXICON, // flags
		S_NULL          // raisestate
	},

	{
		"MT_ARMAGEDDON_ICON",
		-1,             // doomednum
		S_ARMAGEDDON_ICON1, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_armasg,     // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		2*FRACUNIT,     // speed
		8*FRACUNIT,     // radius
		14*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		62*FRACUNIT,    // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY|MF_NOGRAVITY|MF_BOXICON, // flags
		S_NULL          // raisestate
	},

	{
		"MT_WHIRLWIND_ICON",
		-1,             // doomednum
		S_WHIRLWIND_ICON1, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_wirlsg,     // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		2*FRACUNIT,     // speed
		8*FRACUNIT,     // radius
		14*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		62*FRACUNIT,    // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY|MF_NOGRAVITY|MF_BOXICON, // flags
		S_NULL          // raisestate
	},

	{
		"MT_ELEMENTAL_ICON",
		-1,             // doomednum
		S_ELEMENTAL_ICON1, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_elemsg,      // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		2*FRACUNIT,     // speed
		8*FRACUNIT,     // radius
		14*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		62*FRACUNIT,    // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY|MF_NOGRAVITY|MF_BOXICON, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SNEAKERS_ICON",
		-1,             // doomednum
		S_SNEAKERS_ICON1, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		2*FRACUNIT,     // speed
		8*FRACUNIT,     // radius
		14*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		62*FRACUNIT,    // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY|MF_NOGRAVITY|MF_BOXICON, // flags
		S_NULL          // raisestate
	},

	{
		"MT_INVULN_ICON",
		-1,             // doomednum
		S_INVULN_ICON1, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		2*FRACUNIT,     // speed
		8*FRACUNIT,     // radius
		14*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		62*FRACUNIT,    // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY|MF_NOGRAVITY|MF_BOXICON, // flags
		S_NULL          // raisestate
	},

	{
		"MT_1UP_ICON",
		-1,             // doomednum
		S_1UP_ICON1,    // spawnstate
		1,              // spawnhealth
		S_PLAY_ICON1,   // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		2*FRACUNIT,     // speed
		8*FRACUNIT,     // radius
		14*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		62*FRACUNIT,    // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY|MF_NOGRAVITY|MF_BOXICON, // flags
		S_NULL          // raisestate
	},

	{
		"MT_EGGMAN_ICON",
		-1,             // doomednum
		S_EGGMAN_ICON1, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		2*FRACUNIT,     // speed
		8*FRACUNIT,     // radius
		14*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		62*FRACUNIT,    // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY|MF_NOGRAVITY|MF_BOXICON, // flags
		S_NULL          // raisestate
	},

	{
		"MT_MIXUP_ICON",
		-1,             // doomednum
		S_MIXUP_ICON1,  // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		2*FRACUNIT,     // speed
		8*FRACUNIT,     // radius
		14*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		62*FRACUNIT,    // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY|MF_NOGRAVITY|MF_BOXICON, // flags
		S_NULL          // raisestate
	},

	{
		"MT_GRAVITY_ICON",
		-1,             // doomednum
		S_GRAVITY_ICON1, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		20*TICRATE,     // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		2*FRACUNIT,     // speed
		8*FRACUNIT,     // radius
		14*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		62*FRACUNIT,    // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY|MF_NOGRAVITY|MF_BOXICON, // flags
		S_NULL          // raisestate
	},

	{
		"MT_RECYCLER_ICON",
		-1,             // doomednum
		S_RECYCLER_ICON1, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		2*FRACUNIT,     // speed
		8*FRACUNIT,     // radius
		14*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		62*FRACUNIT,    // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY|MF_NOGRAVITY|MF_BOXICON, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SCORE1K_ICON",
		-1,             // doomednum
		S_SCORE1K_ICON1, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_chchng,     // seesound
		1000,           // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		2*FRACUNIT,     // speed
		8*FRACUNIT,     // radius
		14*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		62*FRACUNIT,    // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY|MF_NOGRAVITY|MF_BOXICON, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SCORE10K_ICON",
		-1,             // doomednum
		S_SCORE10K_ICON1, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_chchng,     // seesound
		10000,          // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		2*FRACUNIT,     // speed
		8*FRACUNIT,     // radius
		14*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		62*FRACUNIT,    // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY|MF_NOGRAVITY|MF_BOXICON, // flags
		S_NULL          // raisestate
	},

	{
		"MT_FLAMEAURA_ICON",
		-1,             // doomednum
		S_FLAMEAURA_ICON1, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_s3k3e,      // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		2*FRACUNIT,     // speed
		8*FRACUNIT,     // radius
		14*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		62*FRACUNIT,    // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY|MF_NOGRAVITY|MF_BOXICON, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BUBBLEWRAP_ICON",
		-1,             // doomednum
		S_BUBBLEWRAP_ICON1, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_s3k3f,      // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		2*FRACUNIT,     // speed
		8*FRACUNIT,     // radius
		14*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		62*FRACUNIT,    // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY|MF_NOGRAVITY|MF_BOXICON, // flags
		S_NULL          // raisestate
	},

	{
		"MT_THUNDERCOIN_ICON",
		-1,             // doomednum
		S_THUNDERCOIN_ICON1, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_s3k41,      // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		2*FRACUNIT,     // speed
		8*FRACUNIT,     // radius
		14*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		62*FRACUNIT,    // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY|MF_NOGRAVITY|MF_BOXICON, // flags
		S_NULL          // raisestate
	},

	{
		"MT_ROCKET",
		-1,             // doomednum
		S_ROCKET,       // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_rlaunc,     // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		20*FRACUNIT,    // speed
		11*FRACUNIT,    // radius
		8*FRACUNIT,     // height
		0,              // display offset
		0,              // mass
		20,             // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_MISSILE|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_LASER",
		-1,             // doomednum
		S_LASER,        // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_rlaunc,     // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_LASERFLASH,   // meleestate
		S_LASER2,       // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		20*FRACUNIT,    // speed
		11*FRACUNIT,    // radius
		8*FRACUNIT,     // height
		0,              // display offset
		0,              // mass
		20,             // damage
		sfx_None,       // activesound
		MF_MISSILE|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_TORPEDO",
		-1,             // doomednum
		S_TORPEDO,      // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_rlaunc,     // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_XPLD1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_cybdth,     // deathsound
		20*FRACUNIT,    // speed
		11*FRACUNIT,    // radius
		8*FRACUNIT,     // height
		0,              // display offset
		0,              // mass
		20,             // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_MISSILE|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_TORPEDO2",
		-1,             // doomednum
		S_TORPEDO,      // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_XPLD1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_cybdth,     // deathsound
		20*FRACUNIT,    // speed
		11*FRACUNIT,    // radius
		8*FRACUNIT,     // height
		0,              // display offset
		0,              // mass
		20,             // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_MISSILE|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_ENERGYBALL",
		-1,             // doomednum
		S_ENERGYBALL1,  // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_bexpld,     // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		40*FRACUNIT,    // speed
		60*FRACUNIT,    // radius
		120*FRACUNIT,   // height
		0,              // display offset
		0,              // mass
		20,             // damage
		sfx_None,       // activesound
		MF_PAIN|MF_NOGRAVITY|MF_NOCLIPHEIGHT|MF_NOCLIP, // flags
		S_NULL          // raisestate
	},

	{
		"MT_MINE",
		-1,             // doomednum
		S_MINE1,        // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_XPLD1,        // deathstate
		S_XPLD1,        // xdeathstate
		sfx_cybdth,     // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		10*FRACUNIT,    // height
		0,              // display offset
		0,              // mass
		64*FRACUNIT,    // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_MISSILE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_JETTBULLET",
		-1,             // doomednum
		S_JETBULLET1,   // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		32,             // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		200,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_XPLD1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		20*FRACUNIT,    // speed
		4*FRACUNIT,     // radius
		8*FRACUNIT,     // height
		0,              // display offset
		0,              // mass
		1,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_MISSILE|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_TURRETLASER",
		-1,             // doomednum
		S_TURRETLASER,  // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_TURRETLASEREXPLODE1, // deathstate
		S_NULL,         // xdeathstate
		sfx_turhit,     // deathsound
		50*FRACUNIT,    // speed
		12*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		0,              // mass
		1,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_MISSILE|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CANNONBALL",
		-1,             // doomednum
		S_CANNONBALL1,  // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_cannon,     // seesound
		32,             // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		200,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_XPLD1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_cybdth,     // deathsound
		16*FRACUNIT,    // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		0,              // mass
		1,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_MISSILE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CANNONBALLDECOR",
		1124,           // doomednum
		S_CANNONBALL1,  // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		32,             // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		200,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_XPLD1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		16*FRACUNIT,    // speed
		20*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		1,              // damage
		sfx_None,       // activesound
		MF_SOLID|MF_PUSHABLE|MF_SLIDEME, // flags
		S_NULL          // raisestate
	},

	{
		"MT_ARROW",
		-1,             // doomednum
		S_ARROW,        // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_s3ka0,      // seesound
		32,             // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		200,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_ARROWBONK,    // deathstate
		S_NULL,         // xdeathstate
		sfx_s3k52,      // deathsound
		16*FRACUNIT,    // speed
		4*FRACUNIT,     // radius
		8*FRACUNIT,     // height
		0,              // display offset
		DMG_SPIKE,      // mass
		1,              // damage
		sfx_s3k51,      // activesound
		MF_NOBLOCKMAP|MF_MISSILE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_DEMONFIRE",
		-1,             // doomednum
		S_DEMONFIRE,    // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		16*FRACUNIT,    // speed
		8*FRACUNIT,     // radius
		8*FRACUNIT,     // height
		0,              // display offset
		0,              // mass
		1,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_MISSILE|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_LETTER",
		-1,             // doomednum
		S_LETTER,       // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		7*FRACUNIT,     // radius -- heaven
		13*FRACUNIT,    // height -- hell
		0,              // display offset
		0,              // mass
		1,              // damage
		sfx_None,       // activesound
		MF_SPECIAL|MF_NOCLIPHEIGHT|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_TUTORIALPLANT",
		799,            // doomednum
		S_NULL,         // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		32*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_TUTORIALLEAF",
		-1,            // doomednum
		S_TUTORIALLEAF1,   // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		32*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_TUTORIALFLOWER",
		-1,            // doomednum
		S_TUTORIALFLOWER1,   // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		32*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_TUTORIALFLOWERF",
		-1,            // doomednum
		S_TUTORIALFLOWERF1,   // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		32*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_GFZFLOWER1",
		800,            // doomednum
		S_GFZFLOWERA,   // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_GFZFLOWER2",
		801,            // doomednum
		S_GFZFLOWERB,  // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		96*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_GFZFLOWER3",
		802,            // doomednum
		S_GFZFLOWERC,  // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BLUEBERRYBUSH",
		803,            // doomednum
		S_BLUEBERRYBUSH, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BERRYBUSH",
		804,            // doomednum
		S_BERRYBUSH,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BUSH",
		805,            // doomednum
		S_BUSH,         // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_GFZTREE",
		806,            // doomednum
		S_GFZTREE,      // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		20*FRACUNIT,    // radius
		128*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_GFZBERRYTREE",
		807,            // doomednum
		S_GFZBERRYTREE, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		20*FRACUNIT,    // radius
		128*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_GFZCHERRYTREE",
		808,            // doomednum
		S_GFZCHERRYTREE, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		20*FRACUNIT,    // radius
		128*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CHECKERTREE",
		809,            // doomednum
		S_CHECKERTREE,  // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		20*FRACUNIT,    // radius
		200*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CHECKERSUNSETTREE",
		810,            // doomednum
		S_CHECKERSUNSETTREE, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		20*FRACUNIT,    // radius
		200*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_FHZTREE",
		2102,           // doomednum
		S_FHZTREE,      // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		20*FRACUNIT,    // radius
		200*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_FHZPINKTREE",
		2103,           // doomednum
		S_FHZPINKTREE,  // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		20*FRACUNIT,    // radius
		200*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_POLYGONTREE",
		811,            // doomednum
		S_POLYGONTREE,  // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		20*FRACUNIT,    // radius
		200*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BUSHTREE",
		812,            // doomednum
		S_BUSHTREE,     // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		20*FRACUNIT,    // radius
		200*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BUSHREDTREE",
		813,            // doomednum
		S_BUSHREDTREE,  // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		20*FRACUNIT,    // radius
		200*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SPRINGTREE",
		1600,           // doomednum
		S_SPRINGTREE,   // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_THZFLOWER1",
		900,            // doomednum
		S_THZFLOWERA,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		8*FRACUNIT,     // radius
		32*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_THZFLOWER2",
		902,            // doomednum
		S_THZFLOWERB,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		16*FRACUNIT,    // radius
		64*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_THZFLOWER3",
		903,            // doomednum
		S_THZFLOWERC,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		16*FRACUNIT,    // radius
		64*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_THZTREE",
		904,            // doomednum
		S_THZTREE,      // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		16*FRACUNIT,    // radius
		64*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_THZTREEBRANCH",
		-1,             // doomednum
		S_THZTREEBRANCH1, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		1*FRACUNIT,     // radius
		1*FRACUNIT,     // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_ALARM",
		901,            // doomednum
		S_ALARM1,       // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_alarm,      // deathsound
		1,              // speed
		8*FRACUNIT,     // radius
		16*FRACUNIT,    // height
		0,              // display offset
		4,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SPAWNCEILING|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_GARGOYLE",
		1000,           // doomednum
		S_GARGOYLE,     // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		21*FRACUNIT,    // speed
		16*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		1,              // damage
		sfx_statu2,     // activesound
		MF_SLIDEME|MF_SOLID|MF_PUSHABLE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BIGGARGOYLE",
		1009,           // doomednum
		S_BIGGARGOYLE,  // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		12*FRACUNIT,    // speed
		32*FRACUNIT,    // radius
		80*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		1,              // damage
		sfx_statu2,     // activesound
		MF_SLIDEME|MF_SOLID|MF_PUSHABLE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SEAWEED",
		1001,           // doomednum
		S_SEAWEED1,     // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		24*FRACUNIT,    // radius
		56*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_WATERDRIP",
		1002,           // doomednum
		S_DRIPA1,       // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		1*FRACUNIT,     // radius
		15*FRACUNIT,    // height
		0,              // display offset
		4,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SPAWNCEILING|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_WATERDROP",
		-1,             // doomednum
		S_DRIPB1,       // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_DRIPC1,       // deathstate
		S_NULL,         // xdeathstate
		sfx_wdrip1,     // deathsound
		0,              // speed
		2*FRACUNIT,     // radius
		8*FRACUNIT,     // height
		0,              // display offset
		8,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SPECIAL|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CORAL1",
		1003,           // doomednum
		S_CORAL1,       // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		29*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		4,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CORAL2",
		1004,           // doomednum
		S_CORAL2,       // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		30*FRACUNIT,    // radius
		53*FRACUNIT,    // height
		0,              // display offset
		4,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CORAL3",
		1005,           // doomednum
		S_CORAL3,       // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		28*FRACUNIT,    // radius
		41*FRACUNIT,    // height
		0,              // display offset
		4,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CORAL4",
		1014,           // doomednum
		S_CORAL4,       // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		56*FRACUNIT,    // radius
		112*FRACUNIT,   // height
		0,              // display offset
		4,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CORAL5",
		1015,           // doomednum
		S_CORAL5,       // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		56*FRACUNIT,    // radius
		112*FRACUNIT,   // height
		0,              // display offset
		4,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BLUECRYSTAL",
		1006,           // doomednum
		S_BLUECRYSTAL1, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		16*FRACUNIT,    // height
		0,              // display offset
		4,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_KELP",
		1007,           // doomednum
		S_KELP,         // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		292*FRACUNIT,   // height
		0,              // display offset
		4,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SCENERY|MF_NOBLOCKMAP, // flags
		S_NULL          // raisestate
	},

	{
		"MT_ANIMALGAETOP",
		1013,            // doomednum
		S_ANIMALGAETOP1, // spawnstate
		1000,            // spawnhealth
		S_NULL,          // seestate
		sfx_None,        // seesound
		8,               // reactiontime
		sfx_None,        // attacksound
		S_NULL,          // painstate
		0,               // painchance
		sfx_None,        // painsound
		S_NULL,          // meleestate
		S_NULL,          // missilestate
		S_NULL,          // deathstate
		S_NULL,          // xdeathstate
		sfx_None,        // deathsound
		0,               // speed
		48*FRACUNIT,     // radius
		120*FRACUNIT,    // height
		0,               // display offset
		4,               // mass
		0,               // damage
		sfx_None,        // activesound
		MF_NOCLIP|MF_NOBLOCKMAP|MF_NOGRAVITY|MF_RUNSPAWNFUNC, // flags
		S_NULL          // raisestate
	},

	{
		"MT_ANIMALGAESEG",
		-1,             // doomednum
		S_ANIMALGAESEG, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		48*FRACUNIT,    // radius
		120*FRACUNIT,   // height
		0,              // display offset
		4,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOCLIP|MF_NOBLOCKMAP|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_DSZSTALAGMITE",
		1008,           // doomednum
		S_DSZSTALAGMITE,// spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		116*FRACUNIT,   // height
		0,              // display offset
		4,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SCENERY|MF_SOLID, // flags
		S_NULL          // raisestate
	},

	{
		"MT_DSZ2STALAGMITE",
		1011,           // doomednum
		S_DSZ2STALAGMITE, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		116*FRACUNIT,   // height
		0,              // display offset
		4,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SCENERY|MF_SOLID, // flags
		S_NULL          // raisestate
	},

	{
		"MT_LIGHTBEAM",
		1010,           // doomednum
		S_LIGHTBEAM1,   // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		16*FRACUNIT,    // height
		0,              // display offset
		4,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SCENERY|MF_NOBLOCKMAP|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CHAIN",
		1100,           // doomednum
		S_CEZCHAIN,     // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		4*FRACUNIT,     // radius
		128*FRACUNIT,   // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SPAWNCEILING|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_FLAME",
		1101,           // doomednum
		S_FLAME,        // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		MT_FLAMEPARTICLE,  // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		32*FRACUNIT,    // height
		0,              // display offset
		DMG_FIRE,       // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOGRAVITY|MF_PAIN|MF_FIRE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_FLAMEPARTICLE",
		-1,             // doomednum
		S_FLAMEPARTICLE,// spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		FRACUNIT,       // radius
		FRACUNIT,       // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_EGGSTATUE",
		1102,           // doomednum
		S_EGGSTATUE1,   // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		32*FRACUNIT,    // radius
		240*FRACUNIT,   // height
		0,              // display offset
		100,            // mass
		1,              // damage
		sfx_None,       // activesound
		MF_SOLID|MF_PUSHABLE|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_MACEPOINT",
		1104,           // doomednum
		S_INVISIBLE,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		10*FRACUNIT,    // speed
		128*FRACUNIT,   // radius
		1*FRACUNIT,     // height
		0,              // display offset
		10000,          // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOSECTOR|MF_NOCLIP|MF_NOGRAVITY|MF_NOCLIPHEIGHT|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CHAINMACEPOINT",
		1105,           // doomednum
		S_INVISIBLE,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		10*FRACUNIT,    // speed
		128*FRACUNIT,   // radius
		1*FRACUNIT,     // height
		0,              // display offset
		10000,          // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOSECTOR|MF_NOCLIP|MF_NOGRAVITY|MF_NOCLIPHEIGHT|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SPRINGBALLPOINT",
		1106,           // doomednum
		S_INVISIBLE,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		10*FRACUNIT,    // speed
		128*FRACUNIT,   // radius
		1*FRACUNIT,     // height
		0,              // display offset
		10000,          // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOSECTOR|MF_NOCLIP|MF_NOGRAVITY|MF_NOCLIPHEIGHT|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CHAINPOINT",
		1107,           // doomednum
		S_INVISIBLE,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		10*FRACUNIT,    // speed
		128*FRACUNIT,   // radius
		1*FRACUNIT,     // height
		0,              // display offset
		10000,          // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOSECTOR|MF_NOCLIP|MF_NOGRAVITY|MF_NOCLIPHEIGHT|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_HIDDEN_SLING",
		1108,           // doomednum
		S_SLING1,       // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		10*FRACUNIT,    // speed
		8*FRACUNIT,     // radius
		8*FRACUNIT,     // height
		0,              // display offset
		0,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOGRAVITY|MF_NOCLIPHEIGHT|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_FIREBARPOINT",
		1109,           // doomednum
		S_INVISIBLE,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		10*FRACUNIT,    // speed
		128*FRACUNIT,   // radius
		1*FRACUNIT,     // height
		0,              // display offset
		200,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOSECTOR|MF_NOCLIP|MF_NOGRAVITY|MF_NOCLIPHEIGHT|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CUSTOMMACEPOINT",
		1110,           // doomednum
		S_INVISIBLE,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		10*FRACUNIT,    // speed
		128*FRACUNIT,   // radius
		1*FRACUNIT,     // height
		0,              // display offset
		200,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOSECTOR|MF_NOCLIP|MF_NOGRAVITY|MF_NOCLIPHEIGHT|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SMALLMACECHAIN",
		-1,               // doomednum
		S_SMALLMACECHAIN, // spawnstate
		1000,             // spawnhealth
		S_NULL,           // seestate
		sfx_None,         // seesound
		8,                // reactiontime
		sfx_None,         // attacksound
		S_NULL,           // painstate
		0,                // painchance
		sfx_None,         // painsound
		S_NULL,           // meleestate
		S_NULL,           // missilestate
		S_NULL,           // deathstate
		S_NULL,           // xdeathstate
		sfx_None,         // deathsound
		24*FRACUNIT,      // speed
		17*FRACUNIT,      // radius
		34*FRACUNIT,      // height
		0,                // display offset
		100,              // mass
		1,                // damage
		sfx_None,         // activesound
		MF_SCENERY|MF_NOGRAVITY, // flags
		S_NULL            // raisestate
	},

	{
		"MT_BIGMACECHAIN",
		-1,             // doomednum
		S_BIGMACECHAIN,	// spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		48*FRACUNIT,    // speed
		34*FRACUNIT,    // radius
		68*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		1,              // damage
		sfx_None,       // activesound
		MF_SCENERY|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SMALLMACE",
		1130,           // doomednum
		S_SMALLMACE,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		24*FRACUNIT,    // speed
		17*FRACUNIT,    // radius
		34*FRACUNIT,    // height
		1,              // display offset
		DMG_SPIKE,      // mass
		1,              // damage
		sfx_s3kc9s, //sfx_mswing, -- activesound
		MF_SCENERY|MF_PAIN|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BIGMACE",
		1131,           // doomednum
		S_BIGMACE,      // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		48*FRACUNIT,    // speed
		34*FRACUNIT,    // radius
		68*FRACUNIT,    // height
		1,              // display offset
		DMG_SPIKE,      // mass
		1,              // damage
		sfx_s3kc9s, //sfx_mswing, -- activesound
		MF_SCENERY|MF_PAIN|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SMALLGRABCHAIN",
		-1,               // doomednum
		S_SMALLGRABCHAIN, // spawnstate
		1000,             // spawnhealth
		S_NULL,           // seestate
		sfx_None,         // seesound
		8,                // reactiontime
		sfx_None,         // attacksound
		S_NULL,           // painstate
		0,                // painchance
		sfx_None,         // painsound
		S_NULL,           // meleestate
		S_NULL,           // missilestate
		S_NULL,           // deathstate
		S_NULL,           // xdeathstate
		sfx_None,         // deathsound
		24*FRACUNIT,      // speed
		17*FRACUNIT,      // radius
		34*FRACUNIT,      // height
		0,                // display offset
		100,              // mass
		1,                // damage
		sfx_None,         // activesound
		MF_SCENERY|MF_SPECIAL|MF_NOGRAVITY, // flags
		S_NULL            // raisestate
	},

	{
		"MT_BIGGRABCHAIN",
		-1,             // doomednum
		S_BIGGRABCHAIN, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		48*FRACUNIT,    // speed
		34*FRACUNIT,    // radius
		68*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		1,              // damage
		sfx_None,       // activesound
		MF_SCENERY|MF_SPECIAL|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BLUESPRINGBALL",
		1133,           // doomednum
		S_BLUESPRINGBALL, // spawnstate
		1000,           // spawnhealth
		S_BLUESPRINGBALL2, // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_spring,     // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		24*FRACUNIT,    // speed
		17*FRACUNIT,    // radius
		34*FRACUNIT,    // height
		1,              // display offset
		11*FRACUNIT,    // mass
		0,              // damage
		sfx_mswing,     // activesound
		MF_SCENERY|MF_SPRING|MF_NOGRAVITY, // flags
		S_BLUESPRINGBALL2 // raisestate
	},

	{
		"MT_YELLOWSPRINGBALL",
		1134,           // doomednum
		S_YELLOWSPRINGBALL, // spawnstate
		1000,           // spawnhealth
		S_YELLOWSPRINGBALL2, // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_spring,     // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		24*FRACUNIT,    // speed
		17*FRACUNIT,    // radius
		34*FRACUNIT,    // height
		1,              // display offset
		20*FRACUNIT,    // mass
		0,              // damage
		sfx_mswing,     // activesound
		MF_SCENERY|MF_SPRING|MF_NOGRAVITY, // flags
		S_YELLOWSPRINGBALL2 // raisestate
	},

	{
		"MT_REDSPRINGBALL",
		1135,           // doomednum
		S_REDSPRINGBALL, // spawnstate
		1000,           // spawnhealth
		S_REDSPRINGBALL2, // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_spring,     // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		24*FRACUNIT,    // speed
		17*FRACUNIT,    // radius
		34*FRACUNIT,    // height
		1,              // display offset
		32*FRACUNIT,    // mass
		0,              // damage
		sfx_mswing,     // activesound
		MF_SCENERY|MF_SPRING|MF_NOGRAVITY, // flags
		S_REDSPRINGBALL2 // raisestate
	},

	{
		"MT_SMALLFIREBAR",
		1136,           // doomednum
		S_SMALLFIREBAR1,     // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		MT_FLAMEPARTICLE, // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		24*FRACUNIT,    // speed
		17*FRACUNIT,    // radius
		34*FRACUNIT,    // height
		0,              // display offset
		DMG_FIRE,       // mass
		1,              // damage
		sfx_None,       // activesound
		MF_SCENERY|MF_PAIN|MF_FIRE|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BIGFIREBAR",
		1137,           // doomednum
		S_BIGFIREBAR1,  // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		MT_FLAMEPARTICLE, // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		48*FRACUNIT,    // speed
		34*FRACUNIT,    // radius
		68*FRACUNIT,    // height
		1,              // display offset
		DMG_FIRE,       // mass
		1,              // damage
		sfx_None,       // activesound
		MF_SCENERY|MF_PAIN|MF_FIRE|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CEZFLOWER",
		1103,           // doomednum
		S_CEZFLOWER,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CEZPOLE1",
		1117,           // doomednum
		S_CEZPOLE,      // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		40*FRACUNIT,    // radius
		224*FRACUNIT,   // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CEZPOLE2",
		1118,           // doomednum
		S_CEZPOLE,      // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		40*FRACUNIT,    // radius
		224*FRACUNIT,   // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CEZBANNER1",
		-1,             // doomednum
		S_CEZBANNER1,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		40*FRACUNIT,    // radius
		224*FRACUNIT,   // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CEZBANNER2",
		-1,             // doomednum
		S_CEZBANNER2,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		40*FRACUNIT,    // radius
		224*FRACUNIT,   // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_PINETREE",
		1114,           // doomednum
		S_PINETREE,     // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		628*FRACUNIT,   // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOGRAVITY|MF_SOLID|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CEZBUSH1",
		1115,           // doomednum
		S_CEZBUSH1,     // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CEZBUSH2",
		1116,           // doomednum
		S_CEZBUSH2,     // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		3*FRACUNIT,    // radius
		48*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CANDLE",
		1119,           // doomednum
		S_CANDLE,       // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		48*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CANDLEPRICKET",
		1120,           // doomednum
		S_CANDLEPRICKET, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		176*FRACUNIT,   // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SOLID,       // flags
		S_NULL          // raisestate
	},

	{
		"MT_FLAMEHOLDER",
		1121,           // doomednum
		S_FLAMEHOLDER,  // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		24*FRACUNIT,    // radius
		80*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SOLID,       // flags
		S_NULL          // raisestate
	},

	{
		"MT_FIRETORCH",
		1122,           // doomednum
		S_FIRETORCH,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		MT_FLAMEPARTICLE, // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		80*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_WAVINGFLAG1",
		1128,           // doomednum
		S_WAVINGFLAG,   // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		208*FRACUNIT,   // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SOLID,       // flags
		S_NULL          // raisestate
	},

	{
		"MT_WAVINGFLAG2",
		1129,           // doomednum
		S_WAVINGFLAG,   // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		208*FRACUNIT,   // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SOLID,       // flags
		S_NULL          // raisestate
	},

	{
		"MT_WAVINGFLAGSEG1",
		-1,             // doomednum
		S_WAVINGFLAGSEG1, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		1,              // height -- this is not a typo
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOCLIPHEIGHT|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_WAVINGFLAGSEG2",
		-1,             // doomednum
		S_WAVINGFLAGSEG2, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		1,              // height -- this is not a typo
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOCLIPHEIGHT|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CRAWLASTATUE",
		1111,           // doomednum
		S_CRAWLASTATUE, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SLIDEME|MF_SOLID|MF_PUSHABLE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_FACESTABBERSTATUE",
		1112,           // doomednum
		S_FACESTABBERSTATUE, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		32*FRACUNIT,    // radius
		72*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SLIDEME|MF_SOLID|MF_PUSHABLE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SUSPICIOUSFACESTABBERSTATUE",
		1113,           // doomednum
		S_SUSPICIOUSFACESTABBERSTATUE_WAIT, // spawnstate
		1000,           // spawnhealth
		S_SUSPICIOUSFACESTABBERSTATUE_BURST1, // seestate
		sfx_s3k6f,      // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		32*FRACUNIT,    // radius
		72*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SLIDEME|MF_SOLID|MF_PUSHABLE, // flags
		(statenum_t)MT_ROCKCRUMBLE3// raisestate
	},

	{
		"MT_BRAMBLES",
		1125,           // doomednum
		S_BRAMBLES,     // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		48*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SCENERY|MF_NOBLOCKMAP, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BIGTUMBLEWEED",
		1200,           // doomednum
		S_BIGTUMBLEWEED,// spawnstate
		1000,           // spawnhealth
		S_BIGTUMBLEWEED_ROLL1, // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		24*FRACUNIT,    // radius
		48*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		1,              // damage
		sfx_s3k64,      // activesound
		MF_SPECIAL|MF_BOUNCE,      // flags
		S_NULL          // raisestate
	},

	{
		"MT_LITTLETUMBLEWEED",
		1201,           // doomednum
		S_LITTLETUMBLEWEED,// spawnstate
		1000,           // spawnhealth
		S_LITTLETUMBLEWEED_ROLL1, // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		12*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		1,              // damage
		sfx_s3k64,      // activesound
		MF_SPECIAL|MF_BOUNCE,      // flags
		S_NULL          // raisestate
	},

	{
		"MT_CACTI1",
		1203,           // doomednum
		S_CACTI1,       // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		13*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		DMG_SPIKE,      // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SCENERY|MF_PAIN|MF_NOGRAVITY|MF_RUNSPAWNFUNC, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CACTI2",
		1204,           // doomednum
		S_CACTI2,       // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		15*FRACUNIT,    // radius
		52*FRACUNIT,    // height
		0,              // display offset
		DMG_SPIKE,      // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SCENERY|MF_PAIN|MF_NOGRAVITY|MF_RUNSPAWNFUNC, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CACTI3",
		1205,           // doomednum
		S_CACTI3,       // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		13*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		DMG_SPIKE,      // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SCENERY|MF_PAIN|MF_NOGRAVITY|MF_RUNSPAWNFUNC, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CACTI4",
		1206,           // doomednum
		S_CACTI4,       // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		15*FRACUNIT,    // radius
		52*FRACUNIT,    // height
		0,              // display offset
		DMG_SPIKE,      // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SCENERY|MF_PAIN|MF_NOGRAVITY|MF_RUNSPAWNFUNC, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CACTI5",
		1207,           // doomednum
		S_CACTI5,       // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		32*FRACUNIT,    // radius
		96*FRACUNIT,    // height
		0,              // display offset
		DMG_SPIKE,      // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SCENERY|MF_PAIN, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CACTI6",
		1208,           // doomednum
		S_CACTI6,       // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		20*FRACUNIT,    // radius
		128*FRACUNIT,   // height
		0,              // display offset
		DMG_SPIKE,      // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SCENERY|MF_PAIN, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CACTI7",
		1209,           // doomednum
		S_CACTI7,       // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		24*FRACUNIT,    // radius
		224*FRACUNIT,   // height
		0,              // display offset
		DMG_SPIKE,      // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SCENERY|MF_PAIN, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CACTI8",
		1210,           // doomednum
		S_CACTI8,       // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		24*FRACUNIT,    // radius
		256*FRACUNIT,   // height
		0,              // display offset
		DMG_SPIKE,      // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SCENERY|MF_PAIN, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CACTI9",
		1211,           // doomednum
		S_CACTI9,       // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		48*FRACUNIT,    // radius
		96*FRACUNIT,    // height
		0,              // display offset
		DMG_SPIKE,      // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SCENERY|MF_PAIN, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CACTI10",
		1230,           // doomednum
		S_CACTI10,       // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		13*FRACUNIT,    // radius
		28*FRACUNIT,    // height
		0,              // display offset
		DMG_SPIKE,      // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SCENERY|MF_PAIN|MF_NOGRAVITY|MF_RUNSPAWNFUNC, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CACTI11",
		1231,           // doomednum
		S_CACTI11,       // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		15*FRACUNIT,    // radius
		60*FRACUNIT,    // height
		0,              // display offset
		DMG_SPIKE,      // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SCENERY|MF_PAIN|MF_NOGRAVITY|MF_RUNSPAWNFUNC, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CACTITINYSEG",
		-1,             // doomednum
		S_CACTITINYSEG, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		13*FRACUNIT,    // radius
		28*FRACUNIT,    // height
		0,              // display offset
		DMG_SPIKE,      // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_SCENERY|MF_PAIN|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CACTISMALLSEG",
		-1,              // doomednum
		S_CACTISMALLSEG, // spawnstate
		1000,            // spawnhealth
		S_NULL,          // seestate
		sfx_None,        // seesound
		8,               // reactiontime
		sfx_None,        // attacksound
		S_NULL,          // painstate
		0,               // painchance
		sfx_None,        // painsound
		S_NULL,          // meleestate
		S_NULL,          // missilestate
		S_NULL,          // deathstate
		S_NULL,          // xdeathstate
		sfx_None,        // deathsound
		0,               // speed
		15*FRACUNIT,     // radius
		60*FRACUNIT,     // height
		0,               // display offset
		DMG_SPIKE,       // mass
		0,               // damage
		sfx_None,        // activesound
		MF_NOTHINK|MF_SCENERY|MF_PAIN|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_ARIDSIGN_CAUTION",
		1212,           // doomednum
		S_ARIDSIGN_CAUTION,       // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		22*FRACUNIT,    // radius
		64*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SCENERY|MF_SOLID|MF_PAPERCOLLISION, // flags
		S_NULL          // raisestate
	},

	{
		"MT_ARIDSIGN_CACTI",
		1213,           // doomednum
		S_ARIDSIGN_CACTI,       // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		22*FRACUNIT,    // radius
		64*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SCENERY|MF_SOLID|MF_PAPERCOLLISION, // flags
		S_NULL          // raisestate
	},

	{
		"MT_ARIDSIGN_SHARPTURN",
		1214,           // doomednum
		S_ARIDSIGN_SHARPTURN,       // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		192*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SCENERY|MF_SOLID|MF_PAPERCOLLISION, // flags
		S_NULL          // raisestate
	},

	{
		"MT_OILLAMP",
		1215,           // doomednum
		S_OILLAMP,      // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		22*FRACUNIT,    // radius
		64*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_s3k4b,      // activesound
		MF_SCENERY|MF_NOBLOCKMAP|MF_NOGRAVITY|MF_SPAWNCEILING, // flags
		S_NULL          // raisestate
	},

	{
		"MT_TNTBARREL",
		1216,           // doomednum
		S_TNTBARREL_STND1,      // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_bowl,       // attacksound
		S_TNTBARREL_EXPL1,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_TNTBARREL_FLYING,         // missilestate
		S_TNTBARREL_EXPL1,         // deathstate
		S_NULL,         // xdeathstate
		sfx_s3k4e,      // deathsound
		0,              // speed
		24*FRACUNIT,    // radius
		63*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SHOOTABLE|MF_PUSHABLE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_PROXIMITYTNT",
		1217,           // doomednum
		S_PROXIMITY_TNT,    // spawnstate
		1,              // spawnhealth
		S_PROXIMITY_TNT_TRIGGER1,         // seestate
		sfx_s3k5c,      // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_s3k4e,      // deathsound
		0,              // speed
		64*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_s3k89,      // activesound
		MF_SOLID,       // flags
		S_NULL          // raisestate
	},

	{
		"MT_DUSTDEVIL",
		1218,           // doomednum
		S_DUSTDEVIL,    // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		2,              // speed
		80*FRACUNIT,    // radius
		416*FRACUNIT,   // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_s3k4b,      // activesound
		MF_NOBLOCKMAP|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_DUSTLAYER",
		-1,             // doomednum
		S_DUSTLAYER1,   // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		64*FRACUNIT,    // radius
		256*FRACUNIT,   // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOGRAVITY|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_ARIDDUST",
		-1,             // doomednum
		S_ARIDDUST1,    // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOGRAVITY|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY|MF_NOCLIPHEIGHT, // flags
		S_NULL          // raisestate
	},

	{
		"MT_MINECART",
		-1,             // doomednum
		S_MINECART_IDLE,// spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		24*FRACUNIT,    // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_statu2,     // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_MINECART_DTH1,// deathstate
		S_NULL,         // xdeathstate
		sfx_s3k59,      // deathsound
		20*FRACUNIT,    // speed
		22*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_s3k76,      // activesound
		MF_PUSHABLE,    // flags
		(statenum_t)MT_MINECARTSIDEMARK// raisestate
	},

	{
		"MT_MINECARTSEG",
		-1,             // doomednum
		S_INVISIBLE,    // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		FRACUNIT,       // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOCLIPHEIGHT|MF_NOCLIP,    // flags
		S_NULL          // raisestate
	},

	{
		"MT_MINECARTSPAWNER",
		1219,           // doomednum
		S_INVISIBLE,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		22*FRACUNIT,    // radius
		16*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SPECIAL,     // flags
		S_NULL          // raisestate
	},

	{
		"MT_MINECARTEND",
		1220,           // doomednum
		S_MINECARTEND,  // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		32*FRACUNIT,    // radius
		160*FRACUNIT,   // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SPECIAL|MF_NOCLIPHEIGHT|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_MINECARTENDSOLID",
		-1,             // doomednum
		S_INVISIBLE,    // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		32*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SOLID|MF_PAPERCOLLISION|MF_NOCLIPHEIGHT|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_MINECARTSIDEMARK",
		-1,             // doomednum
		S_MINECARTSIDEMARK2, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		22*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_MINECARTSPARK",
		-1,             // doomednum
		S_MINECARTSPARK,// spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		2*FRACUNIT,     // radius
		2*FRACUNIT,     // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_BOUNCE|MF_NOCLIPTHING|MF_GRENADEBOUNCE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SALOONDOOR",
		-1,             // doomednum
		S_SALOONDOOR,   // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		48*FRACUNIT,    // radius
		160*FRACUNIT,   // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_s3k90,      // activesound
		MF_SOLID|MF_NOGRAVITY|MF_RUNSPAWNFUNC|MF_PAPERCOLLISION|MF_NOCLIPHEIGHT, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SALOONDOORCENTER",
		1221,           // doomednum
		S_SALOONDOORCENTER, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		96*FRACUNIT,    // radius
		160*FRACUNIT,   // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SOLID|MF_NOGRAVITY|MF_RUNSPAWNFUNC|MF_PAPERCOLLISION|MF_NOCLIPHEIGHT, // flags
		S_NULL          // raisestate
	},

	{
		"MT_TRAINCAMEOSPAWNER",
		1222,           // doomednum
		S_TRAINCAMEOSPAWNER_1,    // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		28*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOGRAVITY|MF_NOCLIP, // flags
		S_NULL          // raisestate
	},

	{
		"MT_TRAINSEG",
		-1,             // doomednum
		S_INVISIBLE,    // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		FRACUNIT,       // radius
		FRACUNIT,       // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOGRAVITY|MF_NOBLOCKMAP|MF_NOCLIP|MF_NOCLIPHEIGHT, // flags
		S_NULL          // raisestate
	},

	{
		"MT_TRAINDUSTSPAWNER",
		1223,           // doomednum
		S_INVISIBLE,    // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		FRACUNIT,       // radius
		FRACUNIT,       // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOGRAVITY|MF_NOBLOCKMAP|MF_NOCLIP, // flags
		S_NULL          // raisestate
	},

	{
		"MT_TRAINSTEAMSPAWNER",
		1224,           // doomednum
		S_INVISIBLE,    // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		FRACUNIT,       // radius
		FRACUNIT,       // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOGRAVITY|MF_NOBLOCKMAP|MF_NOCLIP, // flags
		S_NULL          // raisestate
	},

	{
		"MT_MINECARTSWITCHPOINT",
		1229,           // doomednum
		S_INVISIBLE,    // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		FRACUNIT,       // radius
		160*FRACUNIT,   // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SPECIAL|MF_NOCLIPHEIGHT|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_FLAMEJET",
		1300,           // doomednum
		S_FLAMEJETSTND, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOCLIP|MF_SCENERY|MF_NOGRAVITY|MF_NOBLOCKMAP|MF_NOSECTOR, // flags
		S_NULL          // raisestate
	},

	{
		"MT_VERTICALFLAMEJET",
		1301,           // doomednum
		S_FLAMEJETSTND, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOCLIP|MF_SCENERY|MF_NOGRAVITY|MF_NOBLOCKMAP|MF_NOSECTOR, // flags
		S_NULL          // raisestate
	},

	{
		"MT_FLAMEJETFLAME",
		-1,             // doomednum
		S_FLAMEJETFLAME1, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		5*FRACUNIT,     // speed
		8*FRACUNIT,     // radius
		8*FRACUNIT,     // height
		0,              // display offset
		DMG_FIRE,       // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOGRAVITY|MF_MISSILE|MF_FIRE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_FJSPINAXISA",
		1302,           // doomednum
		S_FJSPINAXISA1, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		10*FRACUNIT,    // speed
		16*FRACUNIT,    // radius
		1*FRACUNIT,     // height
		0,              // display offset
		100,            // mass
		1,              // damage
		sfx_None,       // activesound
		MF_NOCLIP|MF_NOCLIPTHING|MF_NOGRAVITY|MF_NOSECTOR, // flags
		S_NULL          // raisestate
	},

	{
		"MT_FJSPINAXISB",
		1303,           // doomednum
		S_FJSPINAXISB1, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		10*FRACUNIT,    // speed
		16*FRACUNIT,    // radius
		1*FRACUNIT,     // height
		0,              // display offset
		100,            // mass
		1,              // damage
		sfx_None,       // activesound
		MF_NOCLIP|MF_NOCLIPTHING|MF_NOGRAVITY|MF_NOSECTOR, // flags
		S_NULL          // raisestate
	},

	{
		"MT_FLAMEJETFLAMEB",
		-1,             // doomednum
		S_FLAMEJETFLAMEB1, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_fire,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		18,             // speed
		16*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		DMG_FIRE,       // mass
		1,              // damage
		sfx_None,       // activesound
		MF_NOGRAVITY|MF_MISSILE|MF_FIRE|MF_NOBLOCKMAP|MF_RUNSPAWNFUNC, // flags
		S_NULL          // raisestate
	},

	{
		"MT_LAVAFALL",
		1304,           // doomednum
		S_LAVAFALL_DORMANT, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_lvfal1,     // seesound
		8,              // reactiontime
		sfx_s3kd5l,     // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		3200*FRACUNIT,  // speed
		30*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		1,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOGRAVITY|MF_SPAWNCEILING, // flags
		S_NULL          // raisestate
	},

	{
		"MT_LAVAFALL_LAVA",
		-1,             // doomednum
		S_LAVAFALL_LAVA1, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_LAVAFALL_LAVA3, // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		30*FRACUNIT,    // radius
		48*FRACUNIT,    // height
		0,              // display offset
		DMG_FIRE,       // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SPECIAL|MF_PAIN|MF_NOGRAVITY|MF_FIRE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_LAVAFALLROCK",
		-1,             // doomednum
		S_LAVAFALLROCK, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		8*FRACUNIT,     // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP,  // flags
		S_NULL          // raisestate
	},

	{
		"MT_ROLLOUTSPAWN",
		1305,           // doomednum
		S_ROLLOUTSPAWN, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		8*FRACUNIT,     // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOCLIP|MF_SPAWNCEILING|MF_SCENERY,  // flags
		S_NULL          // raisestate
	},

	{
		"MT_ROLLOUTROCK",
		-1,             // doomednum
		S_ROLLOUTROCK,  // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime (sets number of frames the rock cycles through)
		sfx_None,       // attacksound
		S_NULL,         // painstate
		12*TICRATE,     // painchance (sets how long an unridden rock should last before disappearing - set to 0 to disable)
		sfx_s3k49,      // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		32*FRACUNIT,    // speed
		30*FRACUNIT,    // radius
		60*FRACUNIT,    // height
		-1,             // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_PUSHABLE|MF_SOLID|MF_SLIDEME,  // flags
		S_NULL          // raisestate
	},

	{
		"MT_BIGFERNLEAF",
		-1,             // doomednum
		S_BIGFERNLEAF,  // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		32*FRACUNIT,    // radius
		48*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SCENERY|MF_NOBLOCKMAP, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BIGFERN",
		1306,           // doomednum
		S_BIGFERN1,     // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		32*FRACUNIT,    // radius
		48*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SCENERY|MF_NOBLOCKMAP|MF_RUNSPAWNFUNC, // flags
		S_NULL          // raisestate
	},

	{
		"MT_JUNGLEPALM",
		1307,           // doomednum
		S_JUNGLEPALM,   // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		32*FRACUNIT,    // radius
		48*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SCENERY|MF_NOBLOCKMAP, // flags
		S_NULL          // raisestate
	},

	{
		"MT_TORCHFLOWER",
		1308,           // doomednum
		S_TORCHFLOWER,  // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		14*FRACUNIT,    // radius
		110*FRACUNIT,   // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SCENERY|MF_NOBLOCKMAP, // flags
		S_NULL          // raisestate
	},

	{
		"MT_WALLVINE_LONG",
		1309,           // doomednum
		S_WALLVINE_LONG, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		1*FRACUNIT,    // radius
		288*FRACUNIT,   // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SCENERY|MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOCLIP, // flags
		S_NULL          // raisestate
	},

	{
		"MT_WALLVINE_SHORT",
		1310,           // doomednum
		S_WALLVINE_SHORT, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		1*FRACUNIT,    // radius
		288*FRACUNIT,   // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SCENERY|MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOCLIP, // flags
		S_NULL          // raisestate
	},

	{
		"MT_GLAREGOYLE",
		1500,           // doomednum
		S_GLAREGOYLE,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		21*FRACUNIT,    // speed
		16*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		1,              // damage
		sfx_statu2,     // activesound
		MF_SLIDEME|MF_SOLID|MF_PUSHABLE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_GLAREGOYLEUP",
		1501,           // doomednum
		S_GLAREGOYLEUP,  // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		21*FRACUNIT,    // speed
		16*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		1,              // damage
		sfx_statu2,     // activesound
		MF_SLIDEME|MF_SOLID|MF_PUSHABLE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_GLAREGOYLEDOWN",
		1502,           // doomednum
		S_GLAREGOYLEDOWN,// spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		21*FRACUNIT,    // speed
		16*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		1,              // damage
		sfx_statu2,     // activesound
		MF_SLIDEME|MF_SOLID|MF_PUSHABLE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_GLAREGOYLELONG",
		1503,           // doomednum
		S_GLAREGOYLELONG,// spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		21*FRACUNIT,    // speed
		16*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		1,              // damage
		sfx_statu2,     // activesound
		MF_SLIDEME|MF_SOLID|MF_PUSHABLE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_TARGET",
		1504,           // doomednum
		S_TARGET_IDLE,  // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		32,             // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		200,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_TARGET_HIT1,  // deathstate
		S_TARGET_ALLDONE, // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		24*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SPECIAL|MF_SHOOTABLE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_GREENFLAME",
		1505,           // doomednum
		S_GREENFLAME,   // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		MT_NULL,        // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		32*FRACUNIT,    // height
		0,              // display offset
		0,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOGRAVITY|MF_PAIN, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BLUEGARGOYLE",
		1506,           // doomednum
		S_BLUEGARGOYLE, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		21*FRACUNIT,    // speed
		16*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		1,              // damage
		sfx_statu2,     // activesound
		MF_SLIDEME|MF_SOLID|MF_PUSHABLE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_STALAGMITE0",
		1900,           // doomednum
		S_STG0,         // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_STALAGMITE1",
		1901,           // doomednum
		S_STG1,         // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_STALAGMITE2",
		1902,           // doomednum
		S_STG2,         // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_STALAGMITE3",
		1903,           // doomednum
		S_STG3,         // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_STALAGMITE4",
		1904,           // doomednum
		S_STG4,         // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_STALAGMITE5",
		1905,           // doomednum
		S_STG5,         // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_STALAGMITE6",
		1906,           // doomednum
		S_STG6,         // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_STALAGMITE7",
		1907,           // doomednum
		S_STG7,         // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_STALAGMITE8",
		1908,           // doomednum
		S_STG8,         // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_STALAGMITE9",
		1909,           // doomednum
		S_STG9,         // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_XMASPOLE",
		1850,           // doomednum
		S_XMASPOLE,     // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CANDYCANE",
		1851,           // doomednum
		S_CANDYCANE,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		8*FRACUNIT,     // radius
		32*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SNOWMAN",
		1852,           // doomednum
		S_SNOWMAN,      // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		25*FRACUNIT,    // speed
		16*FRACUNIT,    // radius
		64*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		1,              // damage
		sfx_None,       // activesound
		MF_SLIDEME|MF_SOLID|MF_PUSHABLE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SNOWMANHAT",
		1853,           // doomednum
		S_SNOWMANHAT,   // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		25*FRACUNIT,    // speed
		16*FRACUNIT,    // radius
		80*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		1,              // damage
		sfx_None,       // activesound
		MF_SLIDEME|MF_SOLID|MF_PUSHABLE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_LAMPPOST1",
		1854,           // doomednum
		S_LAMPPOST1,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		120*FRACUNIT,   // height
		0,              // display offset
		100,            // mass
		1,              // damage
		sfx_None,       // activesound
		MF_SOLID,       // flags
		S_NULL          // raisestate
	},

	{
		"MT_LAMPPOST2",
		1855,           // doomednum
		S_LAMPPOST2,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		120*FRACUNIT,   // height
		0,              // display offset
		100,            // mass
		1,              // damage
		sfx_None,       // activesound
		MF_SOLID,       // flags
		S_NULL          // raisestate
	},

	{
		"MT_HANGSTAR",
		1856,           // doomednum
		S_HANGSTAR,     // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		4*FRACUNIT,     // radius
		80*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		1,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SPAWNCEILING|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_MISTLETOE",
		2105,           // doomednum
		S_MISTLETOE,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		52*FRACUNIT,    // radius
		106*FRACUNIT,   // height
		0,              // display offset
		100,            // mass
		1,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SPAWNCEILING|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SSZTREE",
		1860,           // doomednum
		S_SSZTREE,    	// spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		20*FRACUNIT,    // radius
		256*FRACUNIT,   // height
		0,              // display offset
		100,            // mass
		1,              // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SSZTREE_BRANCH",
		-1,		        // doomednum
		S_SSZTREE_BRANCH,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		20*FRACUNIT,    // radius
		256*FRACUNIT,   // height
		0,              // display offset
		100,            // mass
		1,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SSZTREE2",
		1861,           // doomednum
		S_SSZTREE2,    	// spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		20*FRACUNIT,    // radius
		256*FRACUNIT,   // height
		0,              // display offset
		100,            // mass
		1,              // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SSZTREE2_BRANCH",
		-1,		        // doomednum
		S_SSZTREE2_BRANCH,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		20*FRACUNIT,    // radius
		256*FRACUNIT,   // height
		0,              // display offset
		100,            // mass
		1,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_XMASBLUEBERRYBUSH",
		1859,           // doomednum
		S_XMASBLUEBERRYBUSH, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_XMASBERRYBUSH",
		1857,           // doomednum
		S_XMASBERRYBUSH, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_XMASBUSH",
		1858,           // doomednum
		S_XMASBUSH,     // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_FHZICE1",
		2100,           // doomednum
		S_FHZICE1,      // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_FHZICE2",
		2101,           // doomednum
		S_FHZICE2,      // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_ROSY",
		2104,           // doomednum
		S_ROSY_IDLE,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		48*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SCENERY|MF_ENEMY|MF_SLIDEME, // flags -- "enemy" may seem weird but it doesn't have any unintended consequences in context because no MF_SHOOTABLE|MF_SPECIAL
		S_NULL          // raisestate
	},

	{
		"MT_CDLHRT",
		-1,             // doomednum
		S_LHRT,         // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		4*FRACUNIT,     // speed
		4*FRACUNIT,     // radius
		4*FRACUNIT,     // height
		1,              // display offset
		4,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOCLIPHEIGHT|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_JACKO1",
		2006,           // doomednum
		S_JACKO1,       // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		FRACUNIT,       // radius
		FRACUNIT,       // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_SCENERY, // flags
		S_JACKO1OVERLAY_1 // raisestate
	},

	{
		"MT_JACKO2",
		2007,           // doomednum
		S_JACKO2,       // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		FRACUNIT,       // radius
		FRACUNIT,       // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_SCENERY, // flags
		S_JACKO2OVERLAY_1 // raisestate
	},

	{
		"MT_JACKO3",
		2008,           // doomednum
		S_JACKO3,       // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		FRACUNIT,       // radius
		FRACUNIT,       // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_SCENERY, // flags
		S_JACKO3OVERLAY_1 // raisestate
	},

	{
		"MT_HHZTREE_TOP",
		2010,           // doomednum
		S_HHZTREE_TOP,  // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		FRACUNIT,       // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_SCENERY|MF_NOBLOCKMAP|MF_NOGRAVITY|MF_RUNSPAWNFUNC, // flags
		S_NULL          // raisestate
	},

	{
		"MT_HHZTREE_PART",
		-1,             // doomednum
		S_HHZTREE_TRUNK,// spawnstate
		1000,           // spawnhealth
		S_HHZTREE_LEAF, // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		FRACUNIT,       // radius
		40*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_SCENERY|MF_NOBLOCKMAP|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_HHZSHROOM",
		2009,           // doomednum
		S_HHZSHROOM_1,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		FRACUNIT,       // radius
		FRACUNIT,       // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SCENERY|MF_NOBLOCKMAP, // flags
		S_NULL          // raisestate
	},

	{
		"MT_HHZGRASS",
		2001,           // doomednum
		S_HHZGRASS,     // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		FRACUNIT,       // radius
		FRACUNIT,       // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_SCENERY|MF_NOBLOCKMAP, // flags
		S_NULL          // raisestate
	},

	{
		"MT_HHZTENTACLE1",
		2002,           // doomednum
		S_HHZTENT1,     // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		FRACUNIT,       // radius
		FRACUNIT,       // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_SCENERY|MF_NOBLOCKMAP, // flags
		S_NULL          // raisestate
	},

	{
		"MT_HHZTENTACLE2",
		2003,           // doomednum
		S_HHZTENT2,     // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		FRACUNIT,       // radius
		FRACUNIT,       // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_SCENERY|MF_NOBLOCKMAP, // flags
		S_NULL          // raisestate
	},

	{
		"MT_HHZSTALAGMITE_TALL",
		2004,           // doomednum
		S_HHZSTALAGMITE_TALL, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		FRACUNIT,       // radius
		FRACUNIT,       // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_SCENERY|MF_NOBLOCKMAP, // flags
		S_NULL          // raisestate
	},

	{
		"MT_HHZSTALAGMITE_SHORT",
		2005,           // doomednum
		S_HHZSTALAGMITE_SHORT, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		FRACUNIT,       // radius
		FRACUNIT,       // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_SCENERY|MF_NOBLOCKMAP, // flags
		S_NULL          // raisestate
	},

	// No, I did not do all of this by hand.
	// I made a script to make all of these for me.
	// Ha HA. ~Inuyasha
	{
		"MT_BSZTALLFLOWER_RED",
		1400,           // doomednum
		S_BSZTALLFLOWER_RED, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZTALLFLOWER_PURPLE",
		1401,           // doomednum
		S_BSZTALLFLOWER_PURPLE, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZTALLFLOWER_BLUE",
		1402,           // doomednum
		S_BSZTALLFLOWER_BLUE, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZTALLFLOWER_CYAN",
		1403,           // doomednum
		S_BSZTALLFLOWER_CYAN, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZTALLFLOWER_YELLOW",
		1404,           // doomednum
		S_BSZTALLFLOWER_YELLOW, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZTALLFLOWER_ORANGE",
		1405,           // doomednum
		S_BSZTALLFLOWER_ORANGE, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZFLOWER_RED",
		1410,           // doomednum
		S_BSZFLOWER_RED, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZFLOWER_PURPLE",
		1411,           // doomednum
		S_BSZFLOWER_PURPLE, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZFLOWER_BLUE",
		1412,           // doomednum
		S_BSZFLOWER_BLUE, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZFLOWER_CYAN",
		1413,           // doomednum
		S_BSZFLOWER_CYAN, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZFLOWER_YELLOW",
		1414,           // doomednum
		S_BSZFLOWER_YELLOW, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZFLOWER_ORANGE",
		1415,           // doomednum
		S_BSZFLOWER_ORANGE, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZSHORTFLOWER_RED",
		1420,           // doomednum
		S_BSZSHORTFLOWER_RED, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZSHORTFLOWER_PURPLE",
		1421,           // doomednum
		S_BSZSHORTFLOWER_PURPLE, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZSHORTFLOWER_BLUE",
		1422,           // doomednum
		S_BSZSHORTFLOWER_BLUE, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZSHORTFLOWER_CYAN",
		1423,           // doomednum
		S_BSZSHORTFLOWER_CYAN, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZSHORTFLOWER_YELLOW",
		1424,           // doomednum
		S_BSZSHORTFLOWER_YELLOW, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZSHORTFLOWER_ORANGE",
		1425,           // doomednum
		S_BSZSHORTFLOWER_ORANGE, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZTULIP_RED",
		1430,           // doomednum
		S_BSZTULIP_RED, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZTULIP_PURPLE",
		1431,           // doomednum
		S_BSZTULIP_PURPLE, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZTULIP_BLUE",
		1432,           // doomednum
		S_BSZTULIP_BLUE, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZTULIP_CYAN",
		1433,           // doomednum
		S_BSZTULIP_CYAN, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZTULIP_YELLOW",
		1434,           // doomednum
		S_BSZTULIP_YELLOW, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZTULIP_ORANGE",
		1435,           // doomednum
		S_BSZTULIP_ORANGE, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZCLUSTER_RED",
		1440,           // doomednum
		S_BSZCLUSTER_RED, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZCLUSTER_PURPLE",
		1441,           // doomednum
		S_BSZCLUSTER_PURPLE, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZCLUSTER_BLUE",
		1442,           // doomednum
		S_BSZCLUSTER_BLUE, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZCLUSTER_CYAN",
		1443,           // doomednum
		S_BSZCLUSTER_CYAN, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZCLUSTER_YELLOW",
		1444,           // doomednum
		S_BSZCLUSTER_YELLOW, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZCLUSTER_ORANGE",
		1445,           // doomednum
		S_BSZCLUSTER_ORANGE, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZBUSH_RED",
		1450,           // doomednum
		S_BSZBUSH_RED,  // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZBUSH_PURPLE",
		1451,           // doomednum
		S_BSZBUSH_PURPLE, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZBUSH_BLUE",
		1452,           // doomednum
		S_BSZBUSH_BLUE, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZBUSH_CYAN",
		1453,           // doomednum
		S_BSZBUSH_CYAN, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZBUSH_YELLOW",
		1454,           // doomednum
		S_BSZBUSH_YELLOW, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZBUSH_ORANGE",
		1455,           // doomednum
		S_BSZBUSH_ORANGE, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZVINE_RED",
		1460,           // doomednum
		S_BSZVINE_RED,  // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZVINE_PURPLE",
		1461,           // doomednum
		S_BSZVINE_PURPLE, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZVINE_BLUE",
		1462,           // doomednum
		S_BSZVINE_BLUE, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZVINE_CYAN",
		1463,           // doomednum
		S_BSZVINE_CYAN, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZVINE_YELLOW",
		1464,           // doomednum
		S_BSZVINE_YELLOW, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZVINE_ORANGE",
		1465,           // doomednum
		S_BSZVINE_ORANGE, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZSHRUB",
		1470,           // doomednum
		S_BSZSHRUB,     // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BSZCLOVER",
		1471,           // doomednum
		S_BSZCLOVER,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BIG_PALMTREE_TRUNK",
		-1,             // doomednum
		S_BIG_PALMTREE_TRUNK, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		160*FRACUNIT,   // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BIG_PALMTREE_TOP",
		1473,           // doomednum
		S_BIG_PALMTREE_TOP, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		160*FRACUNIT,   // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_RUNSPAWNFUNC|MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_PALMTREE_TRUNK",
		-1,             // doomednum
		S_PALMTREE_TRUNK, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		80*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_PALMTREE_TOP",
		1475,           // doomednum
		S_PALMTREE_TOP, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		80*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_RUNSPAWNFUNC|MF_NOTHINK|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_DBALL",
		1875,           // doomednum
		S_DBALL1,       // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		16*FRACUNIT,    // radius
		54*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SPAWNCEILING|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_EGGSTATUE2",
		1876,           // doomednum
		S_EGGSTATUE2,   // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		20*FRACUNIT,    // radius
		96*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		1,              // damage
		sfx_None,       // activesound
		MF_SOLID|MF_PUSHABLE|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_GINE",
		3048,           // doomednum
		S_GINE,         // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		32*FRACUNIT,    // radius
		628*FRACUNIT,   // height
		0,              // display offset
		100,            // mass
		1,              // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_PPAL",
		3050,           // doomednum
		S_PPAL,         // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		626*FRACUNIT,   // height
		0,              // display offset
		100,            // mass
		1,              // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_PPEL",
		3051,           // doomednum
		S_PPEL,         // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		517*FRACUNIT,   // height
		0,              // display offset
		100,            // mass
		1,              // damage
		sfx_None,       // activesound
		MF_SOLID|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_ELEMENTAL_ORB",
		-1,             // doomednum
		S_ELEM1,        // spawnstate
		1000,           // spawnhealth
		S_ELEMF1,       // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_ELEM13,       // painstate
		SKINCOLOR_NONE, // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		SH_ELEMENTAL,   // speed
		64*FRACUNIT,    // radius
		64*FRACUNIT,    // height
		4,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOCLIPHEIGHT|MF_NOGRAVITY|MF_SCENERY, // flags
		S_ELEMF9        // raisestate
	},

	{
		"MT_ATTRACT_ORB",
		-1,             // doomednum
		S_MAGN1,        // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_MAGN13,       // painstate
		SKINCOLOR_NONE, // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		SH_ATTRACT,     // speed
		64*FRACUNIT,    // radius
		64*FRACUNIT,    // height
		4,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOCLIPHEIGHT|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_FORCE_ORB",
		-1,             // doomednum
		S_FORC1,        // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_FORC11,       // painstate
		SKINCOLOR_NONE, // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		SH_FORCE,       // speed
		64*FRACUNIT,    // radius
		64*FRACUNIT,    // height
		4,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOCLIPHEIGHT|MF_NOGRAVITY|MF_SCENERY, // flags
		S_FORC21        // raisestate
	},

	{
		"MT_ARMAGEDDON_ORB",
		-1,             // doomednum
		S_ARMA1,        // spawnstate
		1000,           // spawnhealth
		S_ARMF1,        // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		SKINCOLOR_NONE, // painchance
		sfx_None,       // painsound
		S_ARMB1,        // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		SH_ARMAGEDDON,  // speed
		64*FRACUNIT,    // radius
		64*FRACUNIT,    // height
		4,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOCLIPHEIGHT|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_WHIRLWIND_ORB",
		-1,             // doomednum
		S_WIND1,        // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		SKINCOLOR_NONE, // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		SH_WHIRLWIND,        // speed
		64*FRACUNIT,    // radius
		64*FRACUNIT,    // height
		4,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOCLIPHEIGHT|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_PITY_ORB",
		-1,             // doomednum
		S_PITY1,        // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		SKINCOLOR_NONE, // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		SH_PITY,        // speed
		64*FRACUNIT,    // radius
		64*FRACUNIT,    // height
		4,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOCLIPHEIGHT|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_FLAMEAURA_ORB",
		-1,             // doomednum
		S_FIRSB1,       // spawnstate
		1000,           // spawnhealth
		S_FIRS1,        // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_FIRSB10,      // painstate
		SKINCOLOR_NONE, // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		SH_FLAMEAURA,   // speed
		64*FRACUNIT,    // radius
		64*FRACUNIT,    // height
		-4,             // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOCLIPHEIGHT|MF_NOGRAVITY|MF_SCENERY, // flags
		S_FIRS10        // raisestate
	},

	{
		"MT_BUBBLEWRAP_ORB",
		-1,             // doomednum
		S_BUBSB1,       // spawnstate
		1000,           // spawnhealth
		S_BUBS1,        // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_BUBSB5,       // painstate
		SKINCOLOR_NONE, // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		SH_BUBBLEWRAP,  // speed
		64*FRACUNIT,    // radius
		64*FRACUNIT,    // height
		4,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOCLIPHEIGHT|MF_NOGRAVITY|MF_SCENERY, // flags
		S_BUBS10        // raisestate
	},

	{
		"MT_THUNDERCOIN_ORB",
		-1,             // doomednum
		S_ZAPSB1,       // spawnstate
		1000,           // spawnhealth
		S_ZAPS1,        // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_ZAPSB11,      // painstate
		SKINCOLOR_NONE, // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		SH_THUNDERCOIN, // speed
		64*FRACUNIT,    // radius
		64*FRACUNIT,    // height
		-4,             // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOCLIPHEIGHT|MF_NOGRAVITY|MF_SCENERY, // flags
		S_ZAPS14        // raisestate
	},

	{
		"MT_THUNDERCOIN_SPARK",
		-1,             // doomednum
		S_THUNDERCOIN_SPARK, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		4*FRACUNIT,     // radius
		4*FRACUNIT,     // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOCLIPHEIGHT|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_IVSP",
		-1,             // doomednum
		S_IVSP,         // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		64*FRACUNIT,    // radius
		64*FRACUNIT,    // height
		3,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOCLIPHEIGHT|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SUPERSPARK",
		-1,             // doomednum
		S_SSPK1,        // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		8*FRACUNIT,     // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOCLIPHEIGHT|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	// Bluebird
	{
		"MT_FLICKY_01",
		-1,             // doomednum
		S_FLICKY_01_OUT, // spawnstate
		1000,           // spawnhealth
		S_FLICKY_01_STAND, // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		8*FRACUNIT,     // radius
		20*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOCLIPTHING, // flags
		S_FLICKY_BUBBLE // raisestate
	},

	{
		"MT_FLICKY_01_CENTER",
		2200,             // doomednum
		S_FLICKY_01_CENTER, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		8*FRACUNIT,     // radius
		20*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOSECTOR|MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOCLIP|MF_SCENERY|MF_RUNSPAWNFUNC, // flags
		S_NULL // raisestate
	},

	{
		"MT_FLICKY_02",
		-1,             // doomednum
		S_FLICKY_02_OUT, // spawnstate
		1000,           // spawnhealth
		S_FLICKY_02_STAND, // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		8*FRACUNIT,     // radius
		20*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOCLIPTHING, // flags
		S_FLICKY_BUBBLE // raisestate
	},

	{
		"MT_FLICKY_02_CENTER",
		2201,             // doomednum
		S_FLICKY_02_CENTER, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		8*FRACUNIT,     // radius
		20*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOSECTOR|MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOCLIP|MF_SCENERY|MF_RUNSPAWNFUNC, // flags
		S_NULL // raisestate
	},

	{
		"MT_FLICKY_03",
		-1,             // doomednum
		S_FLICKY_03_OUT, // spawnstate
		1000,           // spawnhealth
		S_FLICKY_03_STAND, // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		8*FRACUNIT,     // radius
		20*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOCLIPTHING, // flags
		S_FLICKY_BUBBLE // raisestate
	},

	{
		"MT_FLICKY_03_CENTER",
		2202,             // doomednum
		S_FLICKY_03_CENTER, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		8*FRACUNIT,     // radius
		20*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOSECTOR|MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOCLIP|MF_SCENERY|MF_RUNSPAWNFUNC, // flags
		S_NULL // raisestate
	},

	{
		"MT_FLICKY_04",
		-1,             // doomednum
		S_FLICKY_04_OUT, // spawnstate
		1000,           // spawnhealth
		S_FLICKY_04_STAND, // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_FLICKY_04_SWIM1, // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		8*FRACUNIT,     // radius
		20*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOCLIPTHING, // flags
		S_NULL          // raisestate
	},

	{
		"MT_FLICKY_04_CENTER",
		2203,             // doomednum
		S_FLICKY_04_CENTER, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		8*FRACUNIT,     // radius
		20*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOSECTOR|MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOCLIP|MF_SCENERY|MF_RUNSPAWNFUNC, // flags
		S_NULL // raisestate
	},

	{
		"MT_FLICKY_05",
		-1,             // doomednum
		S_FLICKY_05_OUT, // spawnstate
		1000,           // spawnhealth
		S_FLICKY_05_STAND, // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		8*FRACUNIT,     // radius
		20*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOCLIPTHING, // flags
		S_FLICKY_BUBBLE // raisestate
	},

	{
		"MT_FLICKY_05_CENTER",
		2204,             // doomednum
		S_FLICKY_05_CENTER, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		8*FRACUNIT,     // radius
		20*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOSECTOR|MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOCLIP|MF_SCENERY|MF_RUNSPAWNFUNC, // flags
		S_NULL // raisestate
	},

	{
		"MT_FLICKY_06",
		-1,             // doomednum
		S_FLICKY_06_OUT, // spawnstate
		1000,           // spawnhealth
		S_FLICKY_06_STAND, // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		8*FRACUNIT,     // radius
		20*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOCLIPTHING, // flags
		S_FLICKY_BUBBLE // raisestate
	},

	{
		"MT_FLICKY_06_CENTER",
		2205,             // doomednum
		S_FLICKY_06_CENTER, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		8*FRACUNIT,     // radius
		20*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOSECTOR|MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOCLIP|MF_SCENERY|MF_RUNSPAWNFUNC, // flags
		S_NULL // raisestate
	},

	{
		"MT_FLICKY_07",
		-1,             // doomednum
		S_FLICKY_07_OUT, // spawnstate
		1000,           // spawnhealth
		S_FLICKY_07_STAND, // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_FLICKY_07_SWIM1, // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		8*FRACUNIT,     // radius
		20*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOCLIPTHING, // flags
		S_NULL          // raisestate
	},

	{
		"MT_FLICKY_07_CENTER",
		2206,             // doomednum
		S_FLICKY_07_CENTER, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		8*FRACUNIT,     // radius
		20*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOSECTOR|MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOCLIP|MF_SCENERY|MF_RUNSPAWNFUNC, // flags
		S_NULL // raisestate
	},

	{
		"MT_FLICKY_08",
		-1,             // doomednum
		S_FLICKY_08_OUT, // spawnstate
		1000,           // spawnhealth
		S_FLICKY_08_STAND, // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_FLICKY_08_SWIM1, // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		8*FRACUNIT,     // radius
		20*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOCLIPTHING, // flags
		S_NULL          // raisestate
	},

	{
		"MT_FLICKY_08_CENTER",
		2207,             // doomednum
		S_FLICKY_08_CENTER, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		8*FRACUNIT,     // radius
		20*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOSECTOR|MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOCLIP|MF_SCENERY|MF_RUNSPAWNFUNC, // flags
		S_NULL // raisestate
	},

	{
		"MT_FLICKY_09",
		-1,             // doomednum
		S_FLICKY_09_OUT, // spawnstate
		1000,           // spawnhealth
		S_FLICKY_09_STAND, // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		8*FRACUNIT,     // radius
		20*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOCLIPTHING, // flags
		S_FLICKY_BUBBLE // raisestate
	},

	{
		"MT_FLICKY_09_CENTER",
		2208,             // doomednum
		S_FLICKY_09_CENTER, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		8*FRACUNIT,     // radius
		20*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOSECTOR|MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOCLIP|MF_SCENERY|MF_RUNSPAWNFUNC, // flags
		S_NULL // raisestate
	},

	{
		"MT_FLICKY_10",
		-1,             // doomednum
		S_FLICKY_10_OUT, // spawnstate
		1000,           // spawnhealth
		S_FLICKY_10_STAND, // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		8*FRACUNIT,     // radius
		20*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOCLIPTHING, // flags
		S_FLICKY_BUBBLE // raisestate
	},

	{
		"MT_FLICKY_10_CENTER",
		2209,             // doomednum
		S_FLICKY_10_CENTER, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		8*FRACUNIT,     // radius
		20*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOSECTOR|MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOCLIP|MF_SCENERY|MF_RUNSPAWNFUNC, // flags
		S_NULL // raisestate
	},

	{
		"MT_FLICKY_11",
		-1,             // doomednum
		S_FLICKY_11_OUT, // spawnstate
		1000,           // spawnhealth
		S_FLICKY_11_STAND, // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		8*FRACUNIT,     // radius
		20*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOCLIPTHING, // flags
		S_FLICKY_BUBBLE // raisestate
	},

	{
		"MT_FLICKY_11_CENTER",
		2210,             // doomednum
		S_FLICKY_11_CENTER, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		8*FRACUNIT,     // radius
		20*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOSECTOR|MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOCLIP|MF_SCENERY|MF_RUNSPAWNFUNC, // flags
		S_NULL // raisestate
	},

	{
		"MT_FLICKY_12",
		-1,             // doomednum
		S_FLICKY_12_OUT, // spawnstate
		1000,           // spawnhealth
		S_FLICKY_12_STAND, // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		8*FRACUNIT,     // radius
		20*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOCLIPTHING, // flags
		S_FLICKY_BUBBLE // raisestate
	},

	{
		"MT_FLICKY_12_CENTER",
		2211,             // doomednum
		S_FLICKY_12_CENTER, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		8*FRACUNIT,     // radius
		20*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOSECTOR|MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOCLIP|MF_SCENERY|MF_RUNSPAWNFUNC, // flags
		S_NULL // raisestate
	},

	{
		"MT_FLICKY_13",
		-1,             // doomednum
		S_FLICKY_13_OUT, // spawnstate
		1000,           // spawnhealth
		S_FLICKY_13_STAND, // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		8*FRACUNIT,     // radius
		20*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOCLIPTHING, // flags
		S_FLICKY_BUBBLE // raisestate
	},

	{
		"MT_FLICKY_13_CENTER",
		2212,             // doomednum
		S_FLICKY_13_CENTER, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		8*FRACUNIT,     // radius
		20*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOSECTOR|MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOCLIP|MF_SCENERY|MF_RUNSPAWNFUNC, // flags
		S_NULL // raisestate
	},

	{
		"MT_FLICKY_14",
		-1,             // doomednum
		S_FLICKY_14_OUT, // spawnstate
		1000,           // spawnhealth
		S_FLICKY_14_STAND, // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		8*FRACUNIT,     // radius
		20*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOCLIPTHING, // flags
		S_FLICKY_BUBBLE // raisestate
	},

	{
		"MT_FLICKY_14_CENTER",
		2213,             // doomednum
		S_FLICKY_14_CENTER, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		8*FRACUNIT,     // radius
		20*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOSECTOR|MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOCLIP|MF_SCENERY|MF_RUNSPAWNFUNC, // flags
		S_NULL // raisestate
	},

	{
		"MT_FLICKY_15",
		-1,             // doomednum
		S_FLICKY_15_OUT, // spawnstate
		1000,           // spawnhealth
		S_FLICKY_15_STAND, // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		8*FRACUNIT,     // radius
		20*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOCLIPTHING, // flags
		S_FLICKY_BUBBLE // raisestate
	},

	{
		"MT_FLICKY_15_CENTER",
		2214,             // doomednum
		S_FLICKY_15_CENTER, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		8*FRACUNIT,     // radius
		20*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOSECTOR|MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOCLIP|MF_SCENERY|MF_RUNSPAWNFUNC, // flags
		S_NULL // raisestate
	},

	{
		"MT_FLICKY_16",
		-1,             // doomednum
		S_FLICKY_16_OUT, // spawnstate
		1000,           // spawnhealth
		S_FLICKY_16_STAND, // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		8*FRACUNIT,     // radius
		20*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOCLIPTHING, // flags
		S_FLICKY_BUBBLE // raisestate
	},

	{
		"MT_FLICKY_16_CENTER",
		2215,             // doomednum
		S_FLICKY_16_CENTER, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		8*FRACUNIT,     // radius
		20*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOSECTOR|MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOCLIP|MF_SCENERY|MF_RUNSPAWNFUNC, // flags
		S_NULL // raisestate
	},

	{
		"MT_SECRETFLICKY_01",
		-1,             // doomednum
		S_SECRETFLICKY_01_OUT, // spawnstate
		1000,           // spawnhealth
		S_SECRETFLICKY_01_STAND, // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		8*FRACUNIT,     // radius
		20*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOCLIPTHING, // flags
		S_FLICKY_BUBBLE // raisestate
	},

	{
		"MT_SECRETFLICKY_01_CENTER",
		2216,             // doomednum
		S_SECRETFLICKY_01_CENTER, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		8*FRACUNIT,     // radius
		20*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOSECTOR|MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOCLIP|MF_SCENERY|MF_RUNSPAWNFUNC, // flags
		S_NULL // raisestate
	},

	{
		"MT_SECRETFLICKY_02",
		-1,             // doomednum
		S_SECRETFLICKY_02_OUT, // spawnstate
		1000,           // spawnhealth
		S_SECRETFLICKY_02_STAND, // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		8*FRACUNIT,     // radius
		20*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOCLIPTHING, // flags
		S_FLICKY_BUBBLE // raisestate
	},

	{
		"MT_SECRETFLICKY_02_CENTER",
		2217,             // doomednum
		S_SECRETFLICKY_02_CENTER, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		8*FRACUNIT,     // radius
		20*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOSECTOR|MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOCLIP|MF_SCENERY|MF_RUNSPAWNFUNC, // flags
		S_NULL // raisestate
	},

	{
		"MT_SEED",
		-1,             // doomednum
		S_SEED,         // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		-2*FRACUNIT,    // speed
		4*FRACUNIT,     // radius
		4*FRACUNIT,     // height
		0,              // display offset
		4,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_RAIN",
		-1,             // doomednum
		S_RAIN1,        // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		-72*FRACUNIT,   // speed
		1*FRACUNIT,     // radius
		8*FRACUNIT,     // height
		0,              // display offset
		4,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP,  // flags
		S_NULL          // raisestate
	},

	{
		"MT_SNOWFLAKE",
		-1,             // doomednum
		S_SNOW1,        // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		-2*FRACUNIT,    // speed
		4*FRACUNIT,     // radius
		4*FRACUNIT,     // height
		0,              // display offset
		4,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP,  // flags
		S_NULL          // raisestate
	},

	{
		"MT_SPLISH",
		-1,             // doomednum
		S_SPLISH1,      // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		6*FRACUNIT,     // radius
		1*FRACUNIT,     // height
		0,              // display offset
		100,            // mass
		1,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_LAVASPLISH",
		-1,             // doomednum
		S_LAVASPLISH,   // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		6*FRACUNIT,     // radius
		1*FRACUNIT,     // height
		0,              // display offset
		100,            // mass
		1,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SMOKE",
		-1,             // doomednum
		S_SMOKE1,       // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		20*FRACUNIT,    // radius
		16*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SMALLBUBBLE",
		-1,             // doomednum
		S_SMALLBUBBLE,  // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		4*FRACUNIT,     // radius
		4*FRACUNIT,     // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_MEDIUMBUBBLE",
		-1,             // doomednum
		S_MEDIUMBUBBLE, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		8*FRACUNIT,     // radius
		8*FRACUNIT,     // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_EXTRALARGEBUBBLE",
		-1,             // doomednum
		S_LARGEBUBBLE1, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_POP1,         // deathstate
		S_NULL,         // xdeathstate
		sfx_gasp,       // deathsound
		8,              // speed
		23*FRACUNIT,    // radius
		43*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SPECIAL|MF_NOGRAVITY|MF_SCENERY, // flags
		S_EXTRALARGEBUBBLE // raisestate
	},

	{
		"MT_WATERZAP",
		-1,             // doomednum
		S_WATERZAP,     // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		4*FRACUNIT,     // radius
		4*FRACUNIT,     // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SPINDUST",
		-1,             // doomednum
		S_SPINDUST1,     // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		4*FRACUNIT,     // speed
		4*FRACUNIT,     // radius
		4*FRACUNIT,     // height
		0,              // display offset
		4,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOCLIPHEIGHT|MF_NOCLIP, // flags
		S_NULL          // raisestate
	},

	{
		"MT_TFOG",
		-1,             // doomednum
		S_FOG1,         // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		1,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOCLIP, // flags
		S_NULL          // raisestate
	},

	{
		"MT_PARTICLE",
		-1,             // doomednum
		S_PARTICLE,     // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		4*FRACUNIT,     // speed
		4*FRACUNIT,     // radius
		4*FRACUNIT,     // height
		1,              // display offset
		4,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOCLIPHEIGHT|MF_NOCLIP, // flags
		S_NULL          // raisestate
	},

	{
		"MT_PARTICLEGEN",
		757,            // doomednum
		S_INVISIBLE,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		1*FRACUNIT,     // radius
		1*FRACUNIT,     // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOSECTOR|MF_NOCLIP|MF_NOGRAVITY|MF_NOCLIPHEIGHT|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SCORE",
		-1,             // doomednum
		S_SCRA,         // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		3*FRACUNIT,     // speed
		8*FRACUNIT,     // radius
		8*FRACUNIT,     // height
		1,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_DROWNNUMBERS",
		-1,             // doomednum
		S_ZERO1,        // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		8*FRACUNIT,     // radius
		8*FRACUNIT,     // height
		113,            // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_GOTEMERALD",
		-1,             // doomednum
		S_CEMG1,        // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_ORBITEM1,     // meleestate
		S_ORBIDYA1,     // missilestate
		S_XPLD1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_s3k8a,      // deathsound
		8,              // speed
		8*FRACUNIT,     // radius
		16*FRACUNIT,    // height
		112,            // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_LOCKON",
		-1,             // doomednum
		S_LOCKON1,       // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		111,            // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOCLIPHEIGHT|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_LOCKONINF",
		1126,           // doomednum
		S_INVISIBLE,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		111,            // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOCLIPHEIGHT|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_TAG",
		-1,             // doomednum
		S_TTAG,         // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		111,            // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_GOTFLAG",
		-1,             // doomednum
		S_GOTFLAG,      // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		64*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		111,            // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_FINISHFLAG",
		-1,             // doomednum
		S_FINISHFLAG,   // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		4*FRACUNIT,     // speed
		8*FRACUNIT,     // radius
		8*FRACUNIT,     // height
		1,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIPHEIGHT|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	// ambient sound effect
	{
		"MT_AMBIENT",
		700,            // doomednum
		S_INVISIBLE,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		16*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOSECTOR|MF_NOGRAVITY|MF_AMBIENT, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CORK",
		-1,             // doomednum
		S_CORK,         // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_corkp,      // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_SMOKE1,       // deathstate
		S_NULL,         // xdeathstate
		sfx_corkh,      // deathsound
		60*FRACUNIT,    // speed
		16*FRACUNIT,    // radius
		16*FRACUNIT,    // height
		0,              // display offset
		0,              // mass
		1,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_MISSILE|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_LHRT",
		-1,             // doomednum
		S_LHRT,         // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_SPRK1,        // deathstate
		S_SPRK1,        // xdeathstate
		sfx_None,       // deathsound
		60*FRACUNIT,    // speed
		16*FRACUNIT,    // radius
		16*FRACUNIT,    // height
		0,              // display offset
		0,              // mass
		1,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_MISSILE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_REDRING",
		-1,             // doomednum
		S_RRNG1,        // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_wepfir,     // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_SPRK1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_itemup,     // deathsound
		60*FRACUNIT,    // speed
		16*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		0,              // mass
		1,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_MISSILE|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

// Ring ammo: Health = amount given
	{
		"MT_BOUNCERING",
		301,            // doomednum
		S_BOUNCERINGAMMO, // spawnstate
		10,             // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_SPRK1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_itemup,     // deathsound
		60*FRACUNIT,    // speed
		16*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		pw_bouncering,  // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SLIDEME|MF_SPECIAL|MF_NOGRAVITY|MF_NOCLIPHEIGHT, // flags
		S_NULL          // raisestate
	},

	{
		"MT_RAILRING",
		302,            // doomednum
		S_RAILRINGAMMO, // spawnstate
		5,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_SPRK1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_itemup,     // deathsound
		60*FRACUNIT,    // speed
		16*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		pw_railring,    // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SLIDEME|MF_SPECIAL|MF_NOGRAVITY|MF_NOCLIPHEIGHT, // flags
		S_NULL          // raisestate
	},

	{
		"MT_INFINITYRING",
		303,            // doomednum
		S_INFINITYRINGAMMO,// spawnstate
		80,             // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_SPRK1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_itemup,     // deathsound
		60*FRACUNIT,    // speed
		24*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		pw_infinityring,// mass
		0,              // damage
		sfx_None,       // activesound
		MF_SLIDEME|MF_SPECIAL|MF_NOGRAVITY|MF_NOCLIPHEIGHT, // flags
		S_NULL          // raisestate
	},

	{
		"MT_AUTOMATICRING",
		304,            // doomednum
		S_AUTOMATICRINGAMMO, // spawnstate
		40,             // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_SPRK1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_itemup,     // deathsound
		60*FRACUNIT,    // speed
		16*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		pw_automaticring, // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SLIDEME|MF_SPECIAL|MF_NOGRAVITY|MF_NOCLIPHEIGHT, // flags
		S_NULL          // raisestate
	},

	{
		"MT_EXPLOSIONRING",
		305,            // doomednum
		S_EXPLOSIONRINGAMMO, // spawnstate
		5,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_SPRK1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_itemup,     // deathsound
		60*FRACUNIT,    // speed
		16*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		pw_explosionring, // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SLIDEME|MF_SPECIAL|MF_NOGRAVITY|MF_NOCLIPHEIGHT, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SCATTERRING",
		306,            // doomednum
		S_SCATTERRINGAMMO, // spawnstate
		5,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_SPRK1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_itemup,     // deathsound
		60*FRACUNIT,    // speed
		16*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		pw_scatterring, // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SLIDEME|MF_SPECIAL|MF_NOGRAVITY|MF_NOCLIPHEIGHT, // flags
		S_NULL          // raisestate
	},

	{
		"MT_GRENADERING",
		307,            // doomednum
		S_GRENADERINGAMMO, // spawnstate
		10,             // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_SPRK1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_itemup,     // deathsound
		60*FRACUNIT,    // speed
		16*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		pw_grenadering, // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SLIDEME|MF_SPECIAL|MF_NOGRAVITY|MF_NOCLIPHEIGHT, // flags
		S_NULL          // raisestate
	},

// Ring panels: Reactiontime = amount given
	{
		"MT_BOUNCEPICKUP",
		330,            // doomednum
		S_BOUNCEPICKUP, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		10,             // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		1,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_BOUNCEPICKUPFADE1, // deathstate
		S_NULL,         // xdeathstate
		sfx_ncitem,     // deathsound
		60*FRACUNIT,    // speed
		24*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		pw_bouncering,  // mass
		2*TICRATE,      // damage
		sfx_None,       // activesound
		MF_SLIDEME|MF_SPECIAL|MF_NOGRAVITY|MF_NOCLIPHEIGHT, // flags
		S_NULL          // raisestate
	},

	{
		"MT_RAILPICKUP",
		331,            // doomednum
		S_RAILPICKUP,   // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		5,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		2,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_RAILPICKUPFADE1, // deathstate
		S_NULL,         // xdeathstate
		sfx_ncitem,     // deathsound
		60*FRACUNIT,    // speed
		24*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		pw_railring,    // mass
		2*TICRATE,      // damage
		sfx_None,       // activesound
		MF_SLIDEME|MF_SPECIAL|MF_NOGRAVITY|MF_NOCLIPHEIGHT, // flags
		S_NULL          // raisestate
	},

	{
		"MT_AUTOPICKUP",
		332,            // doomednum
		S_AUTOPICKUP,   // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		40,             // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		4,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_AUTOPICKUPFADE1, // deathstate
		S_NULL,         // xdeathstate
		sfx_ncitem,     // deathsound
		60*FRACUNIT,    // speed
		24*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		pw_automaticring, // mass
		2*TICRATE,      // damage
		sfx_None,       // activesound
		MF_SLIDEME|MF_SPECIAL|MF_NOGRAVITY|MF_NOCLIPHEIGHT, // flags
		S_NULL          // raisestate
	},

	{
		"MT_EXPLODEPICKUP",
		333,            // doomednum
		S_EXPLODEPICKUP,// spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		5,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		8,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_EXPLODEPICKUPFADE1, // deathstate
		S_NULL,         // xdeathstate
		sfx_ncitem,     // deathsound
		60*FRACUNIT,    // speed
		24*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		pw_explosionring, // mass
		2*TICRATE,      // damage
		sfx_None,       // activesound
		MF_SLIDEME|MF_SPECIAL|MF_NOGRAVITY|MF_NOCLIPHEIGHT, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SCATTERPICKUP",
		334,            // doomednum
		S_SCATTERPICKUP,// spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		5,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		8,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_SCATTERPICKUPFADE1, // deathstate
		S_NULL,         // xdeathstate
		sfx_ncitem,     // deathsound
		60*FRACUNIT,    // speed
		24*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		pw_scatterring, // mass
		2*TICRATE,      // damage
		sfx_None,       // activesound
		MF_SLIDEME|MF_SPECIAL|MF_NOGRAVITY|MF_NOCLIPHEIGHT, // flags
		S_NULL          // raisestate
	},

	{
		"MT_GRENADEPICKUP",
		335,            // doomednum
		S_GRENADEPICKUP,// spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		10,             // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		8,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_GRENADEPICKUPFADE1, // deathstate
		S_NULL,         // xdeathstate
		sfx_ncitem,     // deathsound
		60*FRACUNIT,    // speed
		24*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		pw_grenadering, // mass
		2*TICRATE,      // damage
		sfx_None,       // activesound
		MF_SLIDEME|MF_SPECIAL|MF_NOGRAVITY|MF_NOCLIPHEIGHT, // flags
		S_NULL          // raisestate
	},

	{
		"MT_THROWNBOUNCE",
		-1,             // doomednum
		S_THROWNBOUNCE1,// spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_bnce1,      // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_SPRK1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_itemup,     // deathsound
		60*FRACUNIT,    // speed
		16*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		0,              // mass
		1,              // damage
		sfx_bnce1,      // activesound
		MF_NOBLOCKMAP|MF_MISSILE|MF_NOGRAVITY|MF_BOUNCE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_THROWNINFINITY",
		-1,             // doomednum
		S_THROWNINFINITY1, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_wepfir,     // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_SPRK1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_itemup,     // deathsound
		60*FRACUNIT,    // speed
		16*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		0,              // mass
		1,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_MISSILE|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_THROWNAUTOMATIC",
		-1,             // doomednum
		S_THROWNAUTOMATIC1, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_wepfir,     // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_SPRK1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_itemup,     // deathsound
		60*FRACUNIT,    // speed
		16*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		0,              // mass
		1,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_MISSILE|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_THROWNSCATTER",
		-1,             // doomednum
		S_THROWNSCATTER,// spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_bnce2,      // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_SPRK1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_itemup,     // deathsound
		60*FRACUNIT,    // speed
		16*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		0,              // mass
		1,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_MISSILE|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_THROWNEXPLOSION",
		-1,             // doomednum
		S_THROWNEXPLOSION1, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_cannon,     // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		192*FRACUNIT,   // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_RINGEXPLODE,  // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		60*FRACUNIT,    // speed
		16*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		0,              // mass
		1,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_MISSILE|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_THROWNGRENADE",
		-1,             // doomednum
		S_THROWNGRENADE1, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_wepfir,     // seesound
		6*TICRATE,      // reactiontime (<-- Looking for the Grenade Ring's fuse? It's right here! Again!)
		sfx_gbeep,      // attacksound
		S_NULL,         // painstate
		192*FRACUNIT,   // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_RINGEXPLODE,  // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		30*FRACUNIT,    // speed
		16*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		0,              // mass
		1,              // damage
		sfx_s3k5d,      // activesound
		MF_NOBLOCKMAP|MF_MISSILE|MF_BOUNCE|MF_GRENADEBOUNCE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_COIN",
		1800,           // doomednum
		S_COIN1,        // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		MT_FLINGCOIN,   // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_COINSPARKLE1, // deathstate
		S_NULL,         // xdeathstate
		sfx_mario4,     // deathsound
		60*FRACUNIT,    // speed
		16*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SLIDEME|MF_SPECIAL|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_FLINGCOIN",
		-1,             // doomednum
		S_COIN1,        // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		MT_FLINGCOIN,   // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		MT_COIN,        // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_COINSPARKLE1, // deathstate
		S_NULL,         // xdeathstate
		sfx_mario4,     // deathsound
		60*FRACUNIT,    // speed
		15*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SLIDEME|MF_SPECIAL, // flags
		S_NULL          // raisestate
	},

	{
		"MT_GOOMBA",
		1801,           // doomednum
		S_GOOMBA1,      // spawnstate
		1,              // spawnhealth
		S_GOOMBA2,      // seestate
		sfx_None,       // seesound
		32,             // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		200,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_GOOMBA_DEAD,  // deathstate
		S_NULL,         // xdeathstate
		sfx_mario5,     // deathsound
		6,              // speed
		24*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_ENEMY|MF_SPECIAL|MF_SHOOTABLE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BLUEGOOMBA",
		1802,              // doomednum
		S_BLUEGOOMBA1,     // spawnstate
		1,                 // spawnhealth
		S_BLUEGOOMBA2,     // seestate
		sfx_None,          // seesound
		32,                // reactiontime
		sfx_None,          // attacksound
		S_NULL,            // painstate
		170,               // painchance
		sfx_None,          // painsound
		S_NULL,            // meleestate
		S_NULL,            // missilestate
		S_BLUEGOOMBA_DEAD, // deathstate
		S_NULL,            // xdeathstate
		sfx_mario5,        // deathsound
		6,                 // speed
		24*FRACUNIT,       // radius
		32*FRACUNIT,       // height
		0,                 // display offset
		100,               // mass
		0,                 // damage
		sfx_None,          // activesound
		MF_ENEMY|MF_SPECIAL|MF_SHOOTABLE, // flags
		S_NULL             // raisestate
	},

	{
		"MT_FIREFLOWER",
		1803,           // doomednum
		S_FIREFLOWER1,  // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SPECIAL,     // flags
		S_NULL          // raisestate
	},

	{
		"MT_FIREBALL",
		-1,             // doomednum
		S_FIREBALL,     // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		40*FRACUNIT,    // speed
		4*FRACUNIT,     // radius
		8*FRACUNIT,     // height
		0,              // display offset
		DMG_FIRE,       // mass
		1,              // damage
		sfx_None,       // activesound
		MF_FIRE|MF_BOUNCE|MF_MISSILE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_FIREBALLTRAIL",
		-1,                  // doomednum
		S_FIREBALLTRAIL1,    // spawnstate
		1000,                // spawnhealth
		S_NULL,              // seestate
		sfx_None,            // seesound
		8,                   // reactiontime
		sfx_None,            // attacksound
		S_NULL,              // painstate
		0,                   // painchance
		sfx_None,            // painsound
		S_NULL,              // meleestate
		S_NULL,              // missilestate
		S_NULL,              // deathstate
		S_NULL,              // xdeathstate
		sfx_None,            // deathsound
		0,                   // speed
		16*FRACUNIT,         // radius
		16*FRACUNIT,         // height
		0,                   // display offset
		0,                   // mass
		1,                   // damage
		sfx_None,            // activesound
		MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOCLIP|MF_RUNSPAWNFUNC, // flags
		S_NULL               // raisestate
	},

	{
		"MT_SHELL",
		1804,           // doomednum
		S_SHELL,        // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		16,             // speed
		16*FRACUNIT,    // radius
		20*FRACUNIT,    // height
		0,              // display offset
		0,              // mass
		1,              // damage
		sfx_mario1,     // activesound
		MF_SPECIAL|MF_SHOOTABLE|MF_BOUNCE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_PUMA",
		1805,           // doomednum
		S_PUMA_START1,  // spawnstate
		1000,           // spawnhealth
		S_PUMA_START1,  // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_PUMA_DOWN1,   // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_PUMA_DOWN3,   // xdeathstate
		sfx_None,       // deathsound
		2000*FRACUNIT,  // speed
		8*FRACUNIT,     // radius
		16*FRACUNIT,    // height
		0,              // display offset
		DMG_FIRE,       // mass
		0,              // damage
		sfx_None,       // activesound
		MF_PAIN|MF_FIRE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_PUMATRAIL",
		-1,             // doomednum
		S_PUMATRAIL1,   // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		2*FRACUNIT,     // radius
		4*FRACUNIT,     // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOCLIPHEIGHT|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_HAMMER",
		-1,             // doomednum
		S_HAMMER,      // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		4*FRACUNIT,     // radius
		8*FRACUNIT,     // height
		0,              // display offset
		0,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_PAIN,        // flags
		S_NULL          // raisestate
	},
	{
		"MT_KOOPA",
		1806,           // doomednum
		S_KOOPA1,       // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		48*FRACUNIT,    // height
		0,              // display offset
		0,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_PAIN,        // flags
		S_NULL          // raisestate
	},

	{
		"MT_KOOPAFLAME",
		-1,             // doomednum
		S_KOOPAFLAME1,  // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		5*FRACUNIT,     // speed
		8*FRACUNIT,     // radius
		8*FRACUNIT,     // height
		0,              // display offset
		DMG_FIRE,       // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOGRAVITY|MF_MISSILE|MF_FIRE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_AXE",
		1807,           // doomednum
		S_AXE1,         // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		16*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SPECIAL,     // flags
		S_NULL          // raisestate
	},

	{
		"MT_MARIOBUSH1",
		1808,           // doomednum
		S_MARIOBUSH1,   // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_MARIOBUSH2",
		1809,           // doomednum
		S_MARIOBUSH2,   // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_TOAD",
		1810,           // doomednum
		S_TOAD,         // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_AXIS",
		1700,           // doomednum
		S_INVISIBLE,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		10*FRACUNIT,    // speed
		256*FRACUNIT,   // radius
		1*FRACUNIT,     // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOGRAVITY|MF_NOBLOCKMAP|MF_NOSECTOR|MF_NOCLIP, // flags
		S_NULL          // raisestate
	},

	{
		"MT_AXISTRANSFER",
		1701,           // doomednum
		S_INVISIBLE,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		10,             // speed
		16*FRACUNIT,    // radius
		1,              // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOSECTOR|MF_NOCLIP,    // flags
		S_NULL          // raisestate
	},

	{
		"MT_AXISTRANSFERLINE",
		1702,           // doomednum
		S_INVISIBLE,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		10,             // speed
		32*FRACUNIT,    // radius
		1,              // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOSECTOR|MF_NOCLIP,    // flags
		S_NULL          // raisestate
	},

	{
		"MT_NIGHTSDRONE",
		1703,           // doomednum
		S_INVISIBLE,  // spawnstate
		120,            // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		255,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		80*FRACUNIT,    // height
		1,              // display offset
		1000,           // mass
		0,              // damage
		sfx_ideya,      // activesound
		MF_NOGRAVITY|MF_NOCLIP|MF_SPECIAL, // flags
		S_NULL          // raisestate
	},

	{
		"MT_NIGHTSDRONE_MAN",
		-1,           // doomednum
		S_INVISIBLE,  // spawnstate
		120,            // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		255,            // painchance
		sfx_None,       // painsound
		S_NIGHTSDRONE_MAN1, // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		56*FRACUNIT,    // height
		1,              // display offset
		1000,           // mass
		0,              // damage
		sfx_None,      // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_NIGHTSDRONE_SPARKLING",
		-1,             // doomednum
		S_INVISIBLE,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		255,            // painchance
		sfx_None,       // painsound
		S_NIGHTSDRONE_SPARKLING1, // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		1,              // display offset
		1000,           // mass
		0,              // damage
		sfx_None,      // activesound
		MF_NOGRAVITY|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_NIGHTSDRONE_GOAL",
		-1,             // doomednum
		S_INVISIBLE,   // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		255,            // painchance
		sfx_None,       // painsound
		S_NIGHTSDRONE_GOAL1,  // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		-1,             // display offset
		1000,           // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOGRAVITY|MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_NIGHTSPARKLE",
		-1,             // doomednum
		S_NIGHTSPARKLE1,// spawnstate
		1000,           // spawnhealth
		S_NIGHTSPARKLESUPER1, // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		2*FRACUNIT,     // radius
		4*FRACUNIT,     // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOCLIPHEIGHT|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_NIGHTSLOOPHELPER",
		-1,             // doomednum
		S_NIGHTSLOOPHELPER,// spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		4*FRACUNIT,     // radius
		4*FRACUNIT,     // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SPECIAL|MF_NOCLIPHEIGHT|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_NIGHTSBUMPER",
		1704,           // doomednum
		S_NIGHTSBUMPER1,// spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_nbmper,     // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		21000,          // speed
		32*FRACUNIT,    // radius
		64*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SCENERY|MF_SPECIAL|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_HOOP",
		-1,             // doomednum
		S_HOOP,         // spawnstate
		1000,           // spawnhealth
		S_HOOP_XMASA,   // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		1,              // speed
		8*FRACUNIT,     // radius
		16*FRACUNIT,    // height
		0,              // display offset
		4,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_HOOPCOLLIDE",
		-1,             // doomednum
		S_INVISIBLE,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		1,              // speed
		8*FRACUNIT,     // radius
		16*FRACUNIT,    // height
		0,              // display offset
		4,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOSECTOR|MF_NOCLIP|MF_NOGRAVITY|MF_SPECIAL|MF_NOTHINK, // flags
		S_NULL          // raisestate
	},

	{
		"MT_HOOPCENTER",
		-1,             // doomednum
		S_INVISIBLE,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		1,              // speed
		2*FRACUNIT,     // radius
		4*FRACUNIT,     // height
		0,              // display offset
		4,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOSECTOR|MF_NOGRAVITY|MF_NOCLIPHEIGHT, // flags
		S_NULL          // raisestate
	},

	{
		"MT_NIGHTSCORE",
		-1,             // doomednum
		S_NIGHTSCORE10, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NIGHTSCORE10_2, // xdeathstate
		sfx_None,       // deathsound
		1,              // speed
		8*FRACUNIT,     // radius
		8*FRACUNIT,     // height
		0,              // display offset
		4,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_NIGHTSCHIP",
		-1,             // doomednum
		S_NIGHTSCHIP,   // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		MT_FLINGNIGHTSCHIP, // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_s3k33,      // painsound
		S_RING,         // meleestate
		S_NULL,         // missilestate
		S_SPRK1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_ncchip,     // deathsound
		1,              // speed
		16*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		4,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SLIDEME|MF_SPECIAL|MF_NOGRAVITY|MF_NOCLIPHEIGHT, // flags
		S_NIGHTSCHIPBONUS // raisestate
	},

	{
		"MT_FLINGNIGHTSCHIP",
		-1,             // doomednum
		S_NIGHTSCHIP,   // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		MT_FLINGNIGHTSCHIP, // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		MT_NIGHTSCHIP,  // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_SPRK1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_ncchip,     // deathsound
		38*FRACUNIT,    // speed
		16*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SLIDEME|MF_SPECIAL, // flags
		S_NIGHTSCHIPBONUS // raisestate
	},

	{
		"MT_NIGHTSSTAR",
		-1,             // doomednum
		S_NIGHTSSTAR,   // spawnstate
		1000,           // spawnhealth
		S_NIGHTSSTARXMAS, // seestate
		sfx_None,       // seesound
		MT_FLINGNIGHTSSTAR, // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_s3k33,      // painsound
		S_RING,         // meleestate
		S_NULL,         // missilestate
		S_SPRK1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_ncitem,     // deathsound
		1,              // speed
		16*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		4,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SLIDEME|MF_SPECIAL|MF_NOGRAVITY|MF_NOCLIPHEIGHT, // flags
		S_NULL          // raisestate
	},

	{
		"MT_FLINGNIGHTSSTAR",
		-1,             // doomednum
		S_NIGHTSSTAR,   // spawnstate
		1000,           // spawnhealth
		S_NIGHTSSTARXMAS, // seestate
		sfx_None,       // seesound
		MT_FLINGNIGHTSSTAR,  // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		MT_NIGHTSSTAR,  // painchance
		sfx_s3k33,      // painsound
		S_RING,         // meleestate
		S_NULL,         // missilestate
		S_SPRK1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_ncitem,     // deathsound
		38*FRACUNIT,    // speed
		16*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SLIDEME|MF_SPECIAL, // flags
		S_NULL          // raisestate
	},

	{
		"MT_NIGHTSSUPERLOOP",
		1707,           // doomednum
		S_NIGHTSSUPERLOOP, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		255,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_SPRK1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_ncspec,     // deathsound
		20*TICRATE,     // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		1000,           // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOCLIPHEIGHT|MF_NOGRAVITY|MF_NIGHTSITEM,   // flags
		S_NULL          // raisestate
	},

	{
		"MT_NIGHTSDRILLREFILL",
		1708,           // doomednum
		S_NIGHTSDRILLREFILL, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		255,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_SPRK1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_ncspec,     // deathsound
		96*20,          // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		1000,           // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOCLIPHEIGHT|MF_NOGRAVITY|MF_NIGHTSITEM,   // flags
		S_NULL          // raisestate
	},

	{
		"MT_NIGHTSHELPER",
		1709,           // doomednum
		S_NIGHTSHELPER, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		255,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_SPRK1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_ncspec,     // deathsound
		20*TICRATE,     // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		1000,           // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOCLIPHEIGHT|MF_NOGRAVITY|MF_NIGHTSITEM,   // flags
		S_NULL          // raisestate
	},

	{
		"MT_NIGHTSEXTRATIME",
		1711,           // doomednum
		S_NIGHTSEXTRATIME, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		255,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_SPRK1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_ncspec,     // deathsound
		30*TICRATE,     // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		1000,           // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOCLIPHEIGHT|MF_NOGRAVITY|MF_NIGHTSITEM,   // flags
		S_NULL          // raisestate
	},

	{
		"MT_NIGHTSLINKFREEZE",
		1712,           // doomednum
		S_NIGHTSLINKFREEZE, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		255,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_SPRK1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_ncspec,     // deathsound
		15*TICRATE,     // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		1000,           // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOCLIPHEIGHT|MF_NOGRAVITY|MF_NIGHTSITEM,   // flags
		S_NULL          // raisestate
	},

	{
		"MT_EGGCAPSULE",
		1710,           // doomednum
		S_EGGCAPSULE,   // spawnstate
		20,             // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		72*FRACUNIT,    // radius
		144*FRACUNIT,   // height
		0,              // display offset
		100,            // mass
		1,              // damage
		sfx_None,       // activesound
		MF_NOGRAVITY|MF_SPECIAL, // flags
		S_NULL          // raisestate
	},

	{
		"MT_IDEYAANCHOR",
		1714,           // doomednum
		S_INVISIBLE,    // spawnstate
		0,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		1*FRACUNIT,     // radius
		2*FRACUNIT,     // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOSECTOR|MF_NOCLIP|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_NIGHTOPIANHELPER",
		-1,             // doomednum
		S_NIGHTOPIANHELPER1, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		255,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		16*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOGRAVITY,   // flags
		S_NULL          // raisestate
	},

	{
		"MT_PIAN",
		1602,           // doomednum
		S_PIAN_LOOK1,   // spawnstate
		1000,           // spawnhealth
		S_PIAN_FLY1,    // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		200,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_PIAN_SING,    // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		FRACUNIT,       // speed
		16*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SLIDEME|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SHLEEP",
		1601,           // doomednum
		S_SHLEEP1,      // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		200,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_SHLEEPBOUNCE1, // deathstate
		S_NULL,         // xdeathstate
		sfx_peww,       // deathsound
		0,              // speed
		24*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SLIDEME|MF_ENEMY|MF_SPECIAL|MF_SHOOTABLE|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_PENGUINATOR",
		129,            // doomednum
		S_PENGUINATOR_LOOK, // spawnstate
		1,              // spawnhealth
		S_PENGUINATOR_WADDLE1, // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_ngjump,     // attacksound
		S_NULL,         // painstate
		200,            // painchance
		sfx_None,       // painsound
		S_PENGUINATOR_SLIDE1, // meleestate
		S_PENGUINATOR_SLIDE1, // missilestate
		S_XPLD_FLICKY,  // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		5,              // speed
		24*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SPECIAL|MF_SHOOTABLE|MF_ENEMY|MF_SLIDEME, // flags
		S_NULL          // raisestate
	},

	{
		"MT_POPHAT",
		130,            // doomednum -- happy anniversary!
		S_POPHAT_LOOK,  // spawnstate
		1,              // spawnhealth
		S_POPHAT_SHOOT1, // seestate
		sfx_None,       // seesound
		1,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		200,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_XPLD_FLICKY,  // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		0,              // speed
		24*FRACUNIT,    // radius
		64*FRACUNIT,    // height
		0,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SPECIAL|MF_SHOOTABLE|MF_ENEMY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_POPSHOT",
		-1,             // doomednum
		S_POPSHOT,      // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_kc4c,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		200,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_SONIC3KBOSSEXPLOSION1, // deathstate
		S_NULL,         // xdeathstate
		sfx_cybdth,     // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		0,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_MISSILE, // flags
		S_NULL          // raisestate
	},

	{
		"MT_POPSHOT_TRAIL",
		-1,             // doomednum
		S_POPSHOT_TRAIL,// spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		4*FRACUNIT,     // speed
		4*FRACUNIT,     // radius
		4*FRACUNIT,     // height
		0,              // display offset
		4,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOCLIPHEIGHT|MF_NOCLIP, // flags
		S_NULL          // raisestate
	},

	{
		"MT_HIVEELEMENTAL",
		127,            // doomednum
		S_HIVEELEMENTAL_LOOK, // spawnstate
		2,              // spawnhealth
		S_HIVEELEMENTAL_PREPARE1, // seestate
		sfx_s3k74,      // seesound
		0,              // reactiontime
		sfx_s3k91,      // attacksound
		S_HIVEELEMENTAL_PAIN, // painstate
		0,              // painchance
		sfx_dmpain,     // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_HIVEELEMENTAL_DIE1, // deathstate
		S_NULL,         // xdeathstate
		sfx_s3kb4,      // deathsound
		6*FRACUNIT,     // speed
		30*FRACUNIT,    // radius
		80*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_s3k72,      // activesound
		MF_SPECIAL|MF_SHOOTABLE|MF_ENEMY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BUMBLEBORE",
		128,			// doomednum
		S_BUMBLEBORE_SPAWN, // spawnstate
		0,              // spawnhealth -- this is how you do drones...
		S_BUMBLEBORE_FLY1, // seestate
		sfx_s3k8e,      // seesound
		2,              // reactiontime
		sfx_s3k9e,      // attacksound
		S_BUMBLEBORE_STUCK1, // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_BUMBLEBORE_RAISE, // meleestate
		S_NULL,         // missilestate
		S_BUMBLEBORE_DIE, // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		4*FRACUNIT,     // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SPECIAL|MF_SHOOTABLE|MF_ENEMY|MF_NOGRAVITY|MF_SLIDEME, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BUGGLE",
		124,            // doomednum
		S_BUGGLEIDLE,   // spawnstate
		1,              // spawnhealth
		S_BUGGLEFLY,    // seestate
		sfx_None,       // seesound
		2,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		TICRATE,        // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_XPLD_FLICKY,  // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		6*FRACUNIT,     // speed
		20*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_gbeep,      // activesound
		MF_SLIDEME|MF_ENEMY|MF_SPECIAL|MF_SHOOTABLE|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SMASHINGSPIKEBALL",
		2000,           // doomednum
		S_SMASHSPIKE_FLOAT, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		255,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		18*FRACUNIT,    // radius
		28*FRACUNIT,    // height
		0,              // display offset
		DMG_SPIKE,      // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOGRAVITY|MF_PAIN, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CACOLANTERN",
		132,            // doomednum
		S_CACO_LOOK,    // spawnstate
		1,              // spawnhealth
		S_CACO_WAKE1,   // seestate
		sfx_s3k8a,      // seesound
		32,             // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		200,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_CACO_DIE_FLAGS, // deathstate
		S_NULL,         // xdeathstate
		sfx_lntdie,     // deathsound
		FRACUNIT,       // speed
		32*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_lntsit,       // activesound
		MF_SPECIAL|MF_SHOOTABLE|MF_ENEMY|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CACOSHARD",
		-1,             // doomednum
		S_CACOSHARD_RANDOMIZE, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		200,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_lntdie,     // deathsound
		FRACUNIT,       // speed
		FRACUNIT,       // radius
		FRACUNIT,       // height
		0,              // display offset
		0,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_MISSILE|MF_NOBLOCKMAP|MF_RUNSPAWNFUNC, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CACOFIRE",
		-1,             // doomednum
		S_CACOFIRE1,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_s3k70,      // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		200,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_CACOFIRE_EXPLODE1, // deathstate
		S_NULL,         // xdeathstate
		sfx_s3k81,      // deathsound
		20*FRACUNIT,    // speed
		16*FRACUNIT,    // radius
		16*FRACUNIT,    // height
		0,              // display offset
		0,              // mass
		20,             // damage
		sfx_s3k48,      // activesound
		MF_MISSILE|MF_NOBLOCKMAP|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SPINBOBERT",
		131,            // doomednum
		S_SPINBOBERT_MOVE_FLIPUP, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_s3ka0,      // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		200,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_XPLD1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_s3k92,      // deathsound
		20*FRACUNIT,    // speed
		32*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		20,             // damage
		sfx_s3k48,      // activesound
		MF_SPECIAL|MF_SHOOTABLE|MF_ENEMY|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SPINBOBERT_FIRE1",
		-1,             // doomednum
		S_SPINBOBERT_FIRE_MOVE, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		200,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_XPLD1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		10*FRACUNIT,    // speed
		16*FRACUNIT,    // radius
		16*FRACUNIT,    // height
		0,              // display offset
		(sfx_ghosty<<8),// mass
		20,             // damage
		sfx_None,       // activesound
		MF_PAIN|MF_NOGRAVITY|MF_NOCLIPHEIGHT, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SPINBOBERT_FIRE2",
		-1,             // doomednum
		S_SPINBOBERT_FIRE_MOVE, // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		200,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_XPLD1,        // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		-10*FRACUNIT,   // speed - only difference from above
		16*FRACUNIT,    // radius
		16*FRACUNIT,    // height
		0,              // display offset
		(sfx_ghosty<<8),// mass
		20,             // damage
		sfx_None,       // activesound
		MF_PAIN|MF_NOGRAVITY|MF_NOCLIPHEIGHT, // flags
		S_NULL          // raisestate
	},

	{
		"MT_HANGSTER",
		133,            // doomednum
		S_HANGSTER_LOOK, // spawnstate
		1,              // spawnhealth
		S_HANGSTER_SWOOP1, // seestate
		sfx_s3ka0,      // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		200,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_XPLD_FLICKY,  // deathstate
		S_NULL,         // xdeathstate
		sfx_pop,        // deathsound
		20*FRACUNIT,    // speed
		24*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		20,             // damage
		sfx_s3k48,      // activesound
		MF_SPECIAL|MF_SHOOTABLE|MF_ENEMY|MF_NOGRAVITY|MF_SPAWNCEILING, // flags
		S_NULL          // raisestate
	},

	{
		"MT_TELEPORTMAN",
		751,            // doomednum
		S_INVISIBLE,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8,              // radius
		8,              // height
		0,              // display offset
		10,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_ALTVIEWMAN",
		752,            // doomednum
		S_INVISIBLE,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8,              // radius
		8,              // height
		0,              // display offset
		10,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_CRUMBLEOBJ",
		-1,             // doomednum
		S_CRUMBLE1,     // spawnstate
		1000,           // spawnhealth
		S_CRUMBLE1,     // seestate
		0,              // seesound
		1,              // reactiontime
		0,              // attacksound
		S_NULL,         // painstate
		200,            // painchance
		0,              // painsound
		0,              // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_crumbl,     // deathsound
		3,              // speed
		1*FRACUNIT,     // radius
		1*FRACUNIT,     // height
		0,              // display offset
		100,            // mass
		0,              // damage
		0,              // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	// Waypoint for zoom tubes
	{
		"MT_TUBEWAYPOINT",
		753,            // doomednum
		S_INVISIBLE,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		1*FRACUNIT,     // radius
		2*FRACUNIT,     // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOSECTOR|MF_NOCLIP|MF_NOGRAVITY|MF_NOCLIPHEIGHT,    // flags
		S_NULL          // raisestate
	},

	// for use with wind and current effects
	{
		"MT_PUSH",
		754,            // doomednum
		S_INVISIBLE,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8,              // radius
		8,              // height
		0,              // display offset
		10,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOGRAVITY,  // flags
		S_NULL          // raisestate
	},

	{
		"MT_GHOST",
		-1,             // doomednum
		S_THOK,         // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		48*FRACUNIT,    // height
		1,              // display offset
		1000,           // mass
		8,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOCLIP|MF_NOCLIPHEIGHT|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_OVERLAY",
		-1,             // doomednum
		S_NULL,         // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		3,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		1*FRACUNIT,     // radius
		1*FRACUNIT,     // height
		0,              // display offset
		1000,           // mass
		8,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOCLIP|MF_NOCLIPHEIGHT|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_ANGLEMAN",
		758,            // doomednum
		S_INVISIBLE,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8,              // radius
		8,              // height
		0,              // display offset
		10,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOTHINK|MF_NOBLOCKMAP|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_POLYANCHOR",
		760,            // doomednum
		S_INVISIBLE,    // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		3,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		1*FRACUNIT,     // radius
		1*FRACUNIT,     // height
		0,              // display offset
		1000,           // mass
		8,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOSECTOR|MF_NOGRAVITY|MF_NOCLIP, // flags
		S_NULL          // raisestate
	},

	{
		"MT_POLYSPAWN",
		761,            // doomednum
		S_INVISIBLE,    // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		3,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		1*FRACUNIT,     // radius
		1*FRACUNIT,     // height
		0,              // display offset
		1000,           // mass
		8,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOSECTOR|MF_NOGRAVITY|MF_NOCLIP, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SKYBOX",
		780,            // doomednum
		S_INVISIBLE,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		12*FRACUNIT,    // radius
		24*FRACUNIT,    // height
		0,              // display offset
		10,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SCENERY|MF_NOBLOCKMAP|MF_NOGRAVITY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_SPARK",
		-1,             // doomednum
		S_SPRK1,        // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		8,              // speed
		32*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		2,              // display offset
		16,             // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_EXPLODE",
		-1,             // doomednum
		S_XPLD1,        // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		32,             // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		200,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		1*FRACUNIT,     // speed
		8*FRACUNIT,     // radius
		16*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_UWEXPLODE",
		-1,             // doomednum
		S_WPLD1,        // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		32,             // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		200,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		1*FRACUNIT,     // speed
		16*FRACUNIT,    // radius
		32*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIP|MF_NOCLIPHEIGHT|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_DUST",
		-1,             // doomednum
		S_DUST1,     // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		3*FRACUNIT,     // speed
		FRACUNIT,       // radius
		FRACUNIT,       // height
		0,              // display offset
		4,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOGRAVITY|MF_NOCLIPHEIGHT|MF_NOCLIP, // flags
		S_NULL          // raisestate
	},

	{
		"MT_ROCKSPAWNER",
		1202,           // doomednum
		S_ROCKSPAWN,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		255,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		16*FRACUNIT,    // height
		0,              // display offset
		1000,           // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOSECTOR|MF_NOGRAVITY,  // flags
		S_NULL          // raisestate
	},

	{
		"MT_FALLINGROCK",
		-1,             // doomednum
		S_ROCKCRUMBLEA, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_ambint,     // seesound
		4,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		255,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		16*FRACUNIT,    // height
		0,              // display offset
		0,              // mass
		0,              // damage
		sfx_rocks1,     // activesound
		MF_PAIN|MF_BOUNCE,  // flags
		S_NULL          // raisestate
	},

	{
		"MT_ROCKCRUMBLE1",
		-1,             // doomednum
		S_ROCKCRUMBLEA, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_ambint,     // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		255,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		16*FRACUNIT,    // height
		0,              // display offset
		1000,           // mass
		0,              // damage
		sfx_crumbl,     // activesound
		MF_NOBLOCKMAP|MF_NOCLIPTHING|MF_SCENERY|MF_NOCLIPHEIGHT,  // flags
		S_NULL          // raisestate
	},

	{
		"MT_ROCKCRUMBLE2",
		-1,             // doomednum
		S_ROCKCRUMBLEB, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_ambint,     // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		255,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		16*FRACUNIT,    // height
		0,              // display offset
		1000,           // mass
		0,              // damage
		sfx_crumbl,     // activesound
		MF_NOBLOCKMAP|MF_NOCLIPTHING|MF_SCENERY|MF_NOCLIPHEIGHT,  // flags
		S_NULL          // raisestate
	},

	{
		"MT_ROCKCRUMBLE3",
		-1,             // doomednum
		S_ROCKCRUMBLEC, //spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_ambint,     // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		255,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		16*FRACUNIT,    // height
		0,              // display offset
		1000,           // mass
		0,              // damage
		sfx_crumbl,     // activesound
		MF_NOBLOCKMAP|MF_NOCLIPTHING|MF_SCENERY|MF_NOCLIPHEIGHT,  // flags
		S_NULL          // raisestate
	},

	{
		"MT_ROCKCRUMBLE4",
		-1,             // doomednum
		S_ROCKCRUMBLED, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_ambint,     // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		255,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		16*FRACUNIT,    // height
		0,              // display offset
		1000,           // mass
		0,              // damage
		sfx_crumbl,     // activesound
		MF_NOBLOCKMAP|MF_NOCLIPTHING|MF_SCENERY|MF_NOCLIPHEIGHT,  // flags
		S_NULL          // raisestate
	},

	{
		"MT_ROCKCRUMBLE5",
		-1,             // doomednum
		S_ROCKCRUMBLEE, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_ambint,     // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		255,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		16*FRACUNIT,    // height
		0,              // display offset
		1000,           // mass
		0,              // damage
		sfx_crumbl,     // activesound
		MF_NOBLOCKMAP|MF_NOCLIPTHING|MF_SCENERY|MF_NOCLIPHEIGHT,  // flags
		S_NULL          // raisestate
	},

	{
		"MT_ROCKCRUMBLE6",
		-1,             // doomednum
		S_ROCKCRUMBLEF, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_ambint,     // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		255,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		16*FRACUNIT,    // height
		0,              // display offset
		1000,           // mass
		0,              // damage
		sfx_crumbl,     // activesound
		MF_NOBLOCKMAP|MF_NOCLIPTHING|MF_SCENERY|MF_NOCLIPHEIGHT,  // flags
		S_NULL          // raisestate
	},

	{
		"MT_ROCKCRUMBLE7",
		-1,             // doomednum
		S_ROCKCRUMBLEG, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_ambint,     // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		255,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		16*FRACUNIT,    // height
		0,              // display offset
		1000,           // mass
		0,              // damage
		sfx_crumbl,     // activesound
		MF_NOBLOCKMAP|MF_NOCLIPTHING|MF_SCENERY|MF_NOCLIPHEIGHT,  // flags
		S_NULL          // raisestate
	},

	{
		"MT_ROCKCRUMBLE8",
		-1,             // doomednum
		S_ROCKCRUMBLEH, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_ambint,     // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		255,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		16*FRACUNIT,    // height
		0,              // display offset
		1000,           // mass
		0,              // damage
		sfx_crumbl,     // activesound
		MF_NOBLOCKMAP|MF_NOCLIPTHING|MF_SCENERY|MF_NOCLIPHEIGHT,  // flags
		S_NULL          // raisestate
	},

	{
		"MT_ROCKCRUMBLE9",
		-1,             // doomednum
		S_ROCKCRUMBLEI, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_ambint,     // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		255,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		16*FRACUNIT,    // height
		0,              // display offset
		1000,           // mass
		0,              // damage
		sfx_crumbl,     // activesound
		MF_NOBLOCKMAP|MF_NOCLIPTHING|MF_SCENERY|MF_NOCLIPHEIGHT,  // flags
		S_NULL          // raisestate
	},

	{
		"MT_ROCKCRUMBLE10",
		-1,             // doomednum
		S_ROCKCRUMBLEJ, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_ambint,     // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		255,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		16*FRACUNIT,    // height
		0,              // display offset
		1000,           // mass
		0,              // damage
		sfx_crumbl,     // activesound
		MF_NOBLOCKMAP|MF_NOCLIPTHING|MF_SCENERY|MF_NOCLIPHEIGHT,  // flags
		S_NULL          // raisestate
	},

	{
		"MT_ROCKCRUMBLE11",
		-1,             // doomednum
		S_ROCKCRUMBLEK, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_ambint,     // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		255,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		16*FRACUNIT,    // height
		0,              // display offset
		1000,           // mass
		0,              // damage
		sfx_crumbl,     // activesound
		MF_NOBLOCKMAP|MF_NOCLIPTHING|MF_SCENERY|MF_NOCLIPHEIGHT,  // flags
		S_NULL          // raisestate
	},

	{
		"MT_ROCKCRUMBLE12",
		-1,             // doomednum
		S_ROCKCRUMBLEL, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_ambint,     // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		255,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		16*FRACUNIT,    // height
		0,              // display offset
		1000,           // mass
		0,              // damage
		sfx_crumbl,     // activesound
		MF_NOBLOCKMAP|MF_NOCLIPTHING|MF_SCENERY|MF_NOCLIPHEIGHT,  // flags
		S_NULL          // raisestate
	},

	{
		"MT_ROCKCRUMBLE13",
		-1,             // doomednum
		S_ROCKCRUMBLEM, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_ambint,     // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		255,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		16*FRACUNIT,    // height
		0,              // display offset
		1000,           // mass
		0,              // damage
		sfx_crumbl,     // activesound
		MF_NOBLOCKMAP|MF_NOCLIPTHING|MF_SCENERY|MF_NOCLIPHEIGHT,  // flags
		S_NULL          // raisestate
	},

	{
		"MT_ROCKCRUMBLE14",
		-1,             // doomednum
		S_ROCKCRUMBLEN, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_ambint,     // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		255,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		16*FRACUNIT,    // height
		0,              // display offset
		1000,           // mass
		0,              // damage
		sfx_crumbl,     // activesound
		MF_NOBLOCKMAP|MF_NOCLIPTHING|MF_SCENERY|MF_NOCLIPHEIGHT,  // flags
		S_NULL          // raisestate
	},

	{
		"MT_ROCKCRUMBLE15",
		-1,             // doomednum
		S_ROCKCRUMBLEO, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_ambint,     // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		255,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		16*FRACUNIT,    // height
		0,              // display offset
		1000,           // mass
		0,              // damage
		sfx_crumbl,     // activesound
		MF_NOBLOCKMAP|MF_NOCLIPTHING|MF_SCENERY|MF_NOCLIPHEIGHT,  // flags
		S_NULL          // raisestate
	},

	{
		"MT_ROCKCRUMBLE16",
		-1,             // doomednum
		S_ROCKCRUMBLEP, // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_ambint,     // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		255,            // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		8*FRACUNIT,     // radius
		16*FRACUNIT,    // height
		0,              // display offset
		1000,           // mass
		0,              // damage
		sfx_crumbl,     // activesound
		MF_NOBLOCKMAP|MF_NOCLIPTHING|MF_SCENERY|MF_NOCLIPHEIGHT,  // flags
		S_NULL          // raisestate
	},

	{
		"MT_GFZDEBRIS",
		-1,             // doomednum
		S_GFZDEBRIS,    // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		32*FRACUNIT,    // radius
		64*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_crumbl,     // activesound
		MF_NOBLOCKMAP|MF_NOCLIPTHING|MF_RUNSPAWNFUNC|MF_NOCLIPHEIGHT|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BRICKDEBRIS",
		-1,             // doomednum
		S_BRICKDEBRIS,  // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		16*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOCLIPTHING|MF_RUNSPAWNFUNC|MF_NOCLIPHEIGHT|MF_SCENERY,  // flags
		S_NULL          // raisestate
	},

	{
		"MT_WOODDEBRIS",
		-1,             // doomednum
		S_WOODDEBRIS,   // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		16*FRACUNIT,    // radius
		16*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_wbreak,     // activesound
		MF_NOBLOCKMAP|MF_NOCLIPTHING|MF_RUNSPAWNFUNC|MF_NOCLIPHEIGHT|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_REDBRICKDEBRIS",
		-1,             // doomednum
		S_REDBRICKDEBRIS,    // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		32*FRACUNIT,    // radius
		64*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_crumbl,     // activesound
		MF_NOBLOCKMAP|MF_NOCLIPTHING|MF_RUNSPAWNFUNC|MF_NOCLIPHEIGHT|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_BLUEBRICKDEBRIS",
		-1,             // doomednum
		S_BLUEBRICKDEBRIS,    // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		32*FRACUNIT,    // radius
		64*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_crumbl,     // activesound
		MF_NOBLOCKMAP|MF_NOCLIPTHING|MF_RUNSPAWNFUNC|MF_NOCLIPHEIGHT|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_YELLOWBRICKDEBRIS",
		-1,             // doomednum
		S_YELLOWBRICKDEBRIS,    // spawnstate
		1,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		32*FRACUNIT,    // radius
		64*FRACUNIT,    // height
		0,              // display offset
		100,            // mass
		0,              // damage
		sfx_crumbl,     // activesound
		MF_NOBLOCKMAP|MF_NOCLIPTHING|MF_RUNSPAWNFUNC|MF_NOCLIPHEIGHT|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_NAMECHECK",
		-1,             // doomednum
		S_NAMECHECK,    // spawnstate
		1000,           // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		8,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		60*FRACUNIT,    // speed
		30*FRACUNIT,    // radius
		40*FRACUNIT,    // height
		0,              // display offset
		0,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_MISSILE|MF_NOGRAVITY|MF_NOSECTOR, // flags
		S_NULL          // raisestate
	},

	{
		"MT_RAY",
		-1,             // doomednum
		S_NULL,         // spawnstate
		0,              // spawnhealth
		S_NULL,         // seestate
		sfx_None,       // seesound
		0,              // reactiontime
		sfx_None,       // attacksound
		S_NULL,         // painstate
		0,              // painchance
		sfx_None,       // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_NULL,         // deathstate
		S_NULL,         // xdeathstate
		sfx_None,       // deathsound
		0,              // speed
		0,              // radius
		0,              // height
		0,              // display offset
		0,              // mass
		0,              // damage
		sfx_None,       // activesound
		MF_NOBLOCKMAP|MF_NOSECTOR|MF_NOCLIP|MF_NOCLIPHEIGHT|MF_NOGRAVITY|MF_SCENERY, // flags
		S_NULL          // raisestate
	},

	{
		"MT_OLDK",
		666,            // doomednum
		S_OLDK_STND,	// spawnstate
		1,              // spawnhealth
		S_NULL, 		// seestate
		sfx_None,		// seesound
		32,             // reactiontime
		sfx_None,       // attacksound
		S_OLDK_DIE0,    // painstate
		128,            // painchance
		sfx_s3k35,      // painsound
		S_NULL,         // meleestate
		S_NULL,         // missilestate
		S_OLDK_DIE0,	// deathstate
		S_NULL,         // xdeathstate
		sfx_s3k35,      // deathsound
		2*FRACUNIT,		// speed
		32*FRACUNIT,    // radius
		64*FRACUNIT,    // height
		0,              // display offset
		1000,           // mass
		0,              // damage
		sfx_None,       // activesound
		MF_SPECIAL|MF_SHOOTABLE|MF_NOGRAVITY|MF_BOSS, // flags
		S_NULL          // raisestate
	},
};

mobjinfo_t **mobjinfo;
UINT32 nummobjinfo;

skincolor_t skincolors[MAXSKINCOLORS] = {
	{"None", {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, SKINCOLOR_NONE, 0, 0, false}, // SKINCOLOR_NONE

	// Greyscale ranges
	{"White",  {0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x02, 0x02, 0x04, 0x06, 0x08, 0x0a, 0x0c, 0x0e, 0x10, 0x11}, SKINCOLOR_BLACK,  5,  0,         true}, // SKINCOLOR_WHITE
	{"Bone",   {0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x05, 0x06, 0x08, 0x0a, 0x0c, 0x0e, 0x10, 0x11, 0x12}, SKINCOLOR_JET,    7,  0,         true}, // SKINCOLOR_BONE
	{"Cloudy", {0x02, 0x03, 0x04, 0x05, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14}, SKINCOLOR_CARBON, 7,  0,         true}, // SKINCOLOR_CLOUDY
	{"Grey",   {0x04, 0x06, 0x08, 0x0a, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18}, SKINCOLOR_AETHER, 12, 0,         true}, // SKINCOLOR_GREY
	{"Silver", {0x02, 0x03, 0x05, 0x07, 0x09, 0x0b, 0x0d, 0x0f, 0x11, 0x13, 0x15, 0x17, 0x19, 0x1b, 0x1d, 0x1f}, SKINCOLOR_SLATE,  12, 0,         true}, // SKINCOLOR_SILVER
	{"Carbon", {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x16, 0x17, 0x17, 0x19, 0x19, 0x1a, 0x1a, 0x1b, 0x1c, 0x1d}, SKINCOLOR_CLOUDY, 7,  V_GRAYMAP, true}, // SKINCOLOR_CARBON
	{"Jet",    {0x00, 0x05, 0x0a, 0x0f, 0x14, 0x19, 0x1a, 0x1b, 0x1c, 0x1e, 0x1e, 0x1e, 0x1f, 0x1f, 0x1f, 0x1f}, SKINCOLOR_BONE,   7,  V_GRAYMAP, true}, // SKINCOLOR_JET
	{"Black",  {0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1b, 0x1b, 0x1c, 0x1d, 0x1d, 0x1e, 0x1e, 0x1f, 0x1f}, SKINCOLOR_WHITE,  7,  V_GRAYMAP, true}, // SKINCOLOR_BLACK

	// Desaturated
	{"Aether",    {0x00, 0x00, 0x01, 0x01, 0x90, 0x90, 0x91, 0x91, 0x92, 0xaa, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xae}, SKINCOLOR_GREY,      15, 0,           true}, // SKINCOLOR_AETHER
	{"Slate",     {0x00, 0x02, 0x04, 0x06, 0x08, 0x0a, 0xaa, 0xaa, 0xaa, 0xab, 0xac, 0xac, 0xad, 0xad, 0xae, 0xaf}, SKINCOLOR_SILVER,    12, 0,           true}, // SKINCOLOR_SLATE
	{"Moonstone", {   0,    4,    8,    9,   11,   12,   14,   15,  171,  172,  173,  174,  175,   27,   29,   31}, SKINCOLOR_TOPAZ,     15, V_GRAYMAP,   true}, // SKINCOLOR_MOONSTONE
	{"Bluebell",  {0x90, 0x91, 0x92, 0x93, 0x94, 0x94, 0x95, 0xac, 0xac, 0xad, 0xad, 0xa8, 0xa8, 0xa9, 0xfd, 0xfe}, SKINCOLOR_COPPER,    4,  V_BLUEMAP,   true}, // SKINCOLOR_BLUEBELL
	{"Pink",      {0xd0, 0xd0, 0xd1, 0xd1, 0xd2, 0xd2, 0xd3, 0xd3, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0x2b, 0x2c, 0x2e}, SKINCOLOR_AZURE,     9,  V_REDMAP,    true}, // SKINCOLOR_PINK
	{"Rosewood",  { 209,  210,  211,  212,  213,  214,  228,  230,  232,  234,  235,  237,   26,   27,   28,   29}, SKINCOLOR_SEPIA,     5,  V_BROWNMAP,  true}, // SKINCOLOR_ROSEWOOD
	{"Yogurt",    {0xd0, 0x30, 0xd8, 0xd9, 0xda, 0xdb, 0xdb, 0xdc, 0xdd, 0xde, 0xdf, 0xe0, 0xe3, 0xe6, 0xe8, 0xe9}, SKINCOLOR_RUST,      7,  V_BROWNMAP,  true}, // SKINCOLOR_YOGURT
	{"Latte",     {  48,  217,  219,  221,  223,  224,  226,  228,   68,   69,   70,   70,   44,   45,   46,   47}, SKINCOLOR_BOTTLE,    12, V_BROWNMAP,  true}, // SKINCOLOR_LATTE
	{"Brown",     {0xdf, 0xe0, 0xe1, 0xe2, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef}, SKINCOLOR_TAN,       2,  V_BROWNMAP,  true}, // SKINCOLOR_BROWN
	{"Boulder",   {0xde, 0xe0, 0xe1, 0xe4, 0xe7, 0xe9, 0xeb, 0xec, 0xed, 0xed, 0xed, 0x19, 0x19, 0x1b, 0x1d, 0x1e}, SKINCOLOR_KETCHUP,   0,  V_BROWNMAP,  true}, // SKINCOLOR_BOULDER
	{"Bronze",    {  82,   84,   50,   51,  223,  228,  230,  232,  234,  236,  237,  238,  239,  239,   30,   31}, SKINCOLOR_VOLCANIC,  9,  V_BROWNMAP,  true}, // SKINCOLOR_BRONZE
	{"Sepia",     {  88,   84,   85,   86,  224,  226,  228,  230,  232,  235,  236,  237,  238,  239,   28,   28}, SKINCOLOR_ROSEWOOD,  5,  V_BROWNMAP,  true}, // SKINCOLOR_SEPIA
	{"Ecru",      {  80,   83,   84,   85,   86,  242,  243,  245,  230,  232,  234,  236,  238,  239,   47,   47}, SKINCOLOR_ARCTIC,    12, V_BROWNMAP,  true}, // SKINCOLOR_ECRU
	{"Tan",       {0x51, 0x51, 0x54, 0x54, 0x55, 0x55, 0x56, 0x56, 0x56, 0x57, 0xf5, 0xf5, 0xf9, 0xf9, 0xed, 0xed}, SKINCOLOR_BROWN,     12, V_BROWNMAP,  true}, // SKINCOLOR_TAN
	{"Beige",     {0x54, 0x55, 0x56, 0x56, 0xf2, 0xf3, 0xf3, 0xf4, 0xf5, 0xf6, 0xf8, 0xf9, 0xfa, 0xfb, 0xed, 0xed}, SKINCOLOR_MOSS,      5,  V_BROWNMAP,  true}, // SKINCOLOR_BEIGE
	{"Rosebush",  { 208,  216,  209,   85,   90,   91,   91,   92,  191,   93,   94,  107,  109,  110,  111,  111}, SKINCOLOR_EGGPLANT,  5,  V_GREENMAP,  true}, // SKINCOLOR_ROSEBUSH
	{"Moss",      {0x58, 0x58, 0x59, 0x59, 0x5a, 0x5a, 0x5b, 0x5b, 0x5b, 0x5c, 0x5d, 0x5d, 0x5e, 0x5e, 0x5f, 0x5f}, SKINCOLOR_BEIGE,     13, V_GREENMAP,  true}, // SKINCOLOR_MOSS
	{"Azure",     {0x90, 0x90, 0x91, 0x91, 0xaa, 0xaa, 0xab, 0xab, 0xab, 0xac, 0xad, 0xad, 0xae, 0xae, 0xaf, 0xaf}, SKINCOLOR_PINK,      5,  V_AZUREMAP,  true}, // SKINCOLOR_AZURE
	{"Eggplant",  {   4,   8,    11,   11,   16,  195,  195,  195,  196,  186,  187,  187,  254,  254,   30,   31}, SKINCOLOR_ROSEBUSH,  5,  V_PURPLEMAP, true}, // SKINCOLOR_EGGPLANT
	{"Lavender",  {0xc0, 0xc0, 0xc1, 0xc1, 0xc2, 0xc2, 0xc3, 0xc3, 0xc3, 0xc4, 0xc5, 0xc5, 0xc6, 0xc6, 0xc7, 0xc7}, SKINCOLOR_HEADLIGHT, 8,  V_PURPLEMAP, true}, // SKINCOLOR_LAVENDER

	// Viv's vivid colours (toast 21/07/17)
	// Tweaks & additions (Lach, Chrispy, sphere, Alice, MotorRoach & Saneko 26/10/22)
	{"Ruby",       {0xb0, 0xb0, 0xc9, 0xca, 0xcc, 0x26, 0x27, 0x28, 0x29, 0x2a, 0xb9, 0xb9, 0xba, 0xba, 0xbb, 0xfd}, SKINCOLOR_EMERALD,    10, V_REDMAP,     true}, // SKINCOLOR_RUBY
	{"Cherry",     { 202,  203,  204,  205,  206,   40,   41,   42,   43,   44,  186,  187,   28,   29,   30,   31}, SKINCOLOR_MIDNIGHT,   10, V_REDMAP,     true}, // SKINCOLOR_CHERRY
	{"Salmon",     {0xd0, 0xd0, 0xd1, 0xd2, 0x20, 0x21, 0x24, 0x25, 0x26, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e}, SKINCOLOR_FOREST,     6,  V_REDMAP,     true}, // SKINCOLOR_SALMON
	{"Pepper",     { 210,   32,   33,   34,   35,   35,   36,   37,   38,   39,   41,   43,   45,   45,   46,   47}, SKINCOLOR_GREEN,      10, V_REDMAP,     true}, // SKINCOLOR_PEPPER
	{"Red",        {0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x47, 0x2e, 0x2f}, SKINCOLOR_MASTER,     8,  V_REDMAP,     true}, // SKINCOLOR_RED
	{"Crimson",    {0x27, 0x27, 0x28, 0x28, 0x29, 0x2a, 0x2b, 0x2b, 0x2c, 0x2d, 0x2e, 0x2e, 0x2e, 0x2f, 0x2f, 0x1f}, SKINCOLOR_ICY,        10, V_REDMAP,     true}, // SKINCOLOR_CRIMSON
	{"Flame",      {0x31, 0x32, 0x33, 0x36, 0x22, 0x22, 0x25, 0x25, 0x25, 0xcd, 0xcf, 0xcf, 0xc5, 0xc5, 0xc7, 0xc7}, SKINCOLOR_PURPLE,     8,  V_REDMAP,     true}, // SKINCOLOR_FLAME
	{"Garnet",     {   0,   83,   50,   53,   34,   35,   37,   38,   39,   40,   42,   44,   45,   46,   47,   47}, SKINCOLOR_AQUAMARINE, 6,  V_REDMAP,     true}, // SKINCOLOR_GARNET
	{"Ketchup",    {0x48, 0x49, 0x40, 0x33, 0x34, 0x36, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2b, 0x2c, 0x47, 0x2e, 0x2f}, SKINCOLOR_BOULDER,    8,  V_REDMAP,     true}, // SKINCOLOR_KETCHUP
	{"Peachy",     {0xd0, 0x30, 0x31, 0x31, 0x32, 0x32, 0xdc, 0xdc, 0xdc, 0xd3, 0xd4, 0xd4, 0xcc, 0xcd, 0xce, 0xcf}, SKINCOLOR_TEAL,       7,  V_ROSYMAP,    true}, // SKINCOLOR_PEACHY
	{"Quail",      {0xd8, 0xd9, 0xdb, 0xdc, 0xde, 0xdf, 0xd5, 0xd5, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0x1d, 0x1f}, SKINCOLOR_WAVE,       5,  V_BROWNMAP,   true}, // SKINCOLOR_QUAIL
	{"Foundation", {  80,   81,   82,   84,  219,  221,  221,  212,  213,  214,  215,  197,  186,  187,  187,   30}, SKINCOLOR_DREAM,      6,  V_ORANGEMAP,  true}, // SKINCOLOR_FOUNDATION
	{"Sunset",     {0x51, 0x52, 0x40, 0x40, 0x34, 0x36, 0xd5, 0xd5, 0xd6, 0xd7, 0xcf, 0xcf, 0xc6, 0xc6, 0xc7, 0xfe}, SKINCOLOR_SAPPHIRE,   5,  V_ORANGEMAP,  true}, // SKINCOLOR_SUNSET
	{"Copper",     {0x58, 0x54, 0x40, 0x34, 0x35, 0x38, 0x3a, 0x3c, 0x3d, 0x2a, 0x2b, 0x2c, 0x2c, 0xba, 0xba, 0xbb}, SKINCOLOR_BLUEBELL,   5,  V_ORANGEMAP,  true}, // SKINCOLOR_COPPER
	{"Apricot",    {0x00, 0xd8, 0xd9, 0xda, 0xdb, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e}, SKINCOLOR_CYAN,       4,  V_ORANGEMAP,  true}, // SKINCOLOR_APRICOT
	{"Orange",     {  49,   50,   51,   52,   53,   54,   55,   57,   58,   59,   60,   42,   44,   45,   46,   46}, SKINCOLOR_BLUE,       4,  V_ORANGEMAP,  true}, // SKINCOLOR_ORANGE
	{"Rust",       {0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3c, 0x3d, 0x3d, 0x3d, 0x3f, 0x2c, 0x2d, 0x47, 0x2e, 0x2f, 0x2f}, SKINCOLOR_YOGURT,     8,  V_ORANGEMAP,  true}, // SKINCOLOR_RUST
	{"Tangerine",  {  81,   83,   64,   64,   51,   52,   53,   54,   56,   58,   60,   61,   63,   45,   46,   47}, SKINCOLOR_OCEAN,      12, V_ORANGEMAP,  true}, // SKINCOLOR_TANGERINE
	{"Topaz",      {   0,   81,   83,   73,   74,   74,   65,   52,   53,   54,   56,   58,   60,   42,   43,   45}, SKINCOLOR_MOONSTONE,  10, V_YELLOWMAP,  true}, // SKINCOLOR_TOPAZ
	{"Gold",       {0x51, 0x51, 0x54, 0x54, 0x41, 0x42, 0x43, 0x43, 0x44, 0x45, 0x46, 0x3f, 0x2d, 0x2e, 0x2f, 0x2f}, SKINCOLOR_MAUVE,      8,  V_YELLOWMAP,  true}, // SKINCOLOR_GOLD
	{"Sandy",      {0x53, 0x40, 0x41, 0x42, 0x43, 0xe6, 0xe9, 0xe9, 0xea, 0xec, 0xec, 0xc6, 0xc6, 0xc7, 0xc7, 0xfe}, SKINCOLOR_SKY,        8,  V_YELLOWMAP,  true}, // SKINCOLOR_SANDY
	{"Goldenrod",  {   0,   80,   81,   81,   83,   73,   73,   64,   65,   66,   67,   68,   69,   62,   44,   45}, SKINCOLOR_MAJESTY,    8,  V_YELLOWMAP,  true}, // SKINCOLOR_GOLDENROD
	{"Yellow",     {0x52, 0x53, 0x49, 0x49, 0x4a, 0x4a, 0x4b, 0x4b, 0x4b, 0x4c, 0x4d, 0x4d, 0x4e, 0x4e, 0x4f, 0xed}, SKINCOLOR_CORNFLOWER, 8,  V_YELLOWMAP,  true}, // SKINCOLOR_YELLOW
	{"Olive",      {0x4b, 0x4b, 0x4c, 0x4c, 0x4d, 0x4e, 0xe7, 0xe7, 0xe9, 0xc5, 0xc5, 0xc6, 0xc6, 0xc7, 0xc7, 0xfd}, SKINCOLOR_DUSK,       3,  V_YELLOWMAP,  true}, // SKINCOLOR_OLIVE
	{"Pear",       {  88,   89,  188,  189,  189,   76,   76,   67,   67,   68,   69,   70,   45,   46,   47,   47}, SKINCOLOR_MARINE,     9,  V_PERIDOTMAP, true}, // SKINCOLOR_PEAR
	{"Lemon",      {   0,   80,   81,   83,   73,   73,   74,   74,   76,   76,  191,  191,   79,   79,  110,  111}, SKINCOLOR_FUCHSIA,    8,  V_YELLOWMAP,  true}, // SKINCOLOR_LEMON
	{"Lime",       {0x50, 0x51, 0x52, 0x53, 0x48, 0xbc, 0xbd, 0xbe, 0xbe, 0xbf, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f}, SKINCOLOR_MAGENTA,    9,  V_PERIDOTMAP, true}, // SKINCOLOR_LIME
	{"Peridot",    {0x58, 0x58, 0xbc, 0xbc, 0xbd, 0xbd, 0xbe, 0xbe, 0xbe, 0xbf, 0x5e, 0x5e, 0x5f, 0x5f, 0x77, 0x77}, SKINCOLOR_COBALT,     2,  V_PERIDOTMAP, true}, // SKINCOLOR_PERIDOT
	{"Apple",      {0x49, 0x49, 0xbc, 0xbd, 0xbe, 0xbe, 0xbe, 0x67, 0x69, 0x6a, 0x6b, 0x6b, 0x6c, 0x6d, 0x6d, 0x6d}, SKINCOLOR_RASPBERRY,  13, V_PERIDOTMAP, true}, // SKINCOLOR_APPLE
	{"Headlight",  {   0,   80,   81,   82,   73,   84,   64,   65,   91,   91,  124,  125,  126,  137,  138,  139}, SKINCOLOR_LAVENDER,   10, V_YELLOWMAP,  true}, // SKINCOLOR_HEADLIGHT
	{"Chartreuse", {  80,   82,   72,   73,  188,  188,  113,  114,  114,  125,  126,  137,  138,  139,  253,  254}, SKINCOLOR_NOBLE,      9,  V_PERIDOTMAP, true}, // SKINCOLOR_CHARTREUSE
	{"Green",      {0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f}, SKINCOLOR_PEPPER,     8,  V_GREENMAP,   true}, // SKINCOLOR_GREEN
	{"Forest",     {0x65, 0x66, 0x67, 0x68, 0x69, 0x69, 0x6a, 0x6b, 0x6b, 0x6c, 0x6d, 0x6d, 0x6e, 0x6e, 0x6e, 0x6f}, SKINCOLOR_SALMON,     9,  V_GREENMAP,   true}, // SKINCOLOR_FOREST
	{"Shamrock",   {0x70, 0x70, 0x71, 0x71, 0x72, 0x72, 0x73, 0x73, 0x73, 0x74, 0x75, 0x75, 0x76, 0x76, 0x77, 0x77}, SKINCOLOR_SIBERITE,   10, V_GREENMAP,   true}, // SKINCOLOR_SHAMROCK
	{"Jade",       { 128,  120,  121,  122,  122,  113,  114,  114,  115,  116,  117,  118,  119,  110,  111,   30}, SKINCOLOR_ROSY,       7,  V_GREENMAP,   true}, // SKINCOLOR_JADE
	{"Mint",       {0x00, 0x00, 0x58, 0x58, 0x59, 0x62, 0x62, 0x62, 0x64, 0x67, 0x7e, 0x7e, 0x8f, 0x8f, 0x8a, 0x8a}, SKINCOLOR_VIOLET,     5,  V_GREENMAP,   true}, // SKINCOLOR_MINT
	{"Master",     {   0,   80,   88,   96,  112,  113,   99,  100,  124,  125,  126,  117,  107,  118,  119,  111}, SKINCOLOR_RED,        6,  V_GREENMAP,   true}, // SKINCOLOR_MASTER
	{"Emerald",    {  80,   96,  112,  113,  114,  114,  125,  125,  126,  126,  137,  137,  138,  138,  139,  139}, SKINCOLOR_RUBY,       9,  V_GREENMAP,   true}, // SKINCOLOR_EMERALD
	{"Seafoam",    {0x01, 0x58, 0x59, 0x5a, 0x7c, 0x7d, 0x7d, 0x7e, 0x7e, 0x8f, 0x8f, 0x8a, 0x8a, 0x8b, 0xfd, 0xfd}, SKINCOLOR_PLUM,       6,  V_AQUAMAP,    true}, // SKINCOLOR_SEAFOAM
	{"Island",     {  96,   97,  113,  113,  114,  124,  142,  136,  136,  150,  151,  153,  168,  168,  169,  169}, SKINCOLOR_GALAXY,     7,  V_AQUAMAP,    true}, // SKINCOLOR_ISLAND
	{"Bottle",     {   0,    1,    3,    4,    5,  140,  141,  141,  124,  125,  126,  127,  118,  119,  111,  111}, SKINCOLOR_LATTE,      14, V_AQUAMAP,    true}, // SKINCOLOR_BOTTLE
	{"Aqua",       {0x78, 0x79, 0x7a, 0x7a, 0x7b, 0x7b, 0x7c, 0x7c, 0x7c, 0x7d, 0x7e, 0x7e, 0x7f, 0x7f, 0x76, 0x77}, SKINCOLOR_TAFFY,      10, V_AQUAMAP,    true}, // SKINCOLOR_AQUA
	{"Teal",       {0x78, 0x78, 0x8c, 0x8c, 0x8d, 0x8d, 0x8d, 0x8e, 0x8e, 0x8f, 0x8f, 0x8f, 0x8a, 0x8a, 0x8a, 0x8a}, SKINCOLOR_PEACHY,     7,  V_SKYMAP,     true}, // SKINCOLOR_TEAL
	{"Ocean",      { 120,  121,  122,  122,  123,  141,  142,  142,  136,  137,  138,  138,  139,  139,  253,  253}, SKINCOLOR_TANGERINE,  4,  V_AQUAMAP,    true}, // SKINCOLOR_OCEAN
	{"Wave",       {0x00, 0x78, 0x78, 0x79, 0x8d, 0x87, 0x88, 0x89, 0x89, 0xae, 0xa8, 0xa8, 0xa9, 0xa9, 0xfd, 0xfd}, SKINCOLOR_QUAIL,      5,  V_SKYMAP,     true}, // SKINCOLOR_WAVE
	{"Cyan",       {0x80, 0x81, 0xff, 0xff, 0x83, 0x83, 0x8d, 0x8d, 0x8d, 0x8e, 0x7e, 0x7f, 0x76, 0x76, 0x77, 0x6e}, SKINCOLOR_APRICOT,    6,  V_SKYMAP,     true}, // SKINCOLOR_CYAN
	{"Turquoise",  {  0,   120,  121,  122,  123,  141,  141,  135,  136,  136,  150,  153,  155,  157,  159,  253}, SKINCOLOR_SANGRIA,    12, V_SKYMAP,     true}, // SKINCOLOR_TURQUOISE
	{"Aquamarine", {   0,  120,  121,  131,  132,  133,  134,  134,  135,  135,  149,  149,  172,  173,  174,  175}, SKINCOLOR_GARNET,     8,  V_SKYMAP,     true}, // SKINCOLOR_AQUAMARINE
	{"Sky",        {0x80, 0x80, 0x81, 0x82, 0x83, 0x83, 0x84, 0x85, 0x85, 0x86, 0x87, 0x88, 0x89, 0x89, 0x8a, 0x8b}, SKINCOLOR_SANDY,      1,  V_SKYMAP,     true}, // SKINCOLOR_SKY
	{"Marine",     { 144,  146,  147,  147,  148,  135,  136,  136,  137,  137,  127,  118,  119,  111,  111,  111}, SKINCOLOR_PEAR,       13, V_SKYMAP,     true}, // SKINCOLOR_MARINE
	{"Cerulean",   {0x85, 0x86, 0x87, 0x88, 0x88, 0x89, 0x89, 0x89, 0x8a, 0x8a, 0xfd, 0xfd, 0xfd, 0x1f, 0x1f, 0x1f}, SKINCOLOR_NEON,       4,  V_SKYMAP,     true}, // SKINCOLOR_CERULEAN
	{"Dream",      {  80,  208,  200,  200,  146,  146,  133,  134,  135,  136,  137,  138,  139,  139,  254,  254}, SKINCOLOR_FOUNDATION, 9,  V_SKYMAP,     true}, // SKINCOLOR_DREAM
	{"Icy",        {0x00, 0x00, 0x00, 0x00, 0x80, 0x81, 0x83, 0x83, 0x86, 0x87, 0x95, 0x95, 0xad, 0xad, 0xae, 0xaf}, SKINCOLOR_CRIMSON,    0,  V_SKYMAP,     true}, // SKINCOLOR_ICY
	{"Daybreak",   {  80,   81,   82,   72,   64,    9,   11,  171,  149,  150,  151,  153,  156,  157,  159,  253}, SKINCOLOR_EVENTIDE,   12, V_BLUEMAP,    true}, // SKINCOLOR_DAYBREAK
	{"Sapphire",   {0x80, 0x82, 0x86, 0x87, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f, 0xfd, 0xfe}, SKINCOLOR_SUNSET,     5,  V_BLUEMAP,    true}, // SKINCOLOR_SAPPHIRE
	{"Arctic",     {   0,    1,    3,    4,  145,  146,  147,  148,  148,  149,  150,  153,  156,  159,  253,  254}, SKINCOLOR_ECRU,       15, V_BLUEMAP,    true}, // SKINCOLOR_ARCTIC
	{"Cornflower", {0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x9a, 0x9c, 0x9d, 0x9d, 0x9e, 0x9e, 0x9e}, SKINCOLOR_YELLOW,     4,  V_BLUEMAP,    true}, // SKINCOLOR_CORNFLOWER
	{"Blue",       {0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f, 0xfd, 0xfe}, SKINCOLOR_ORANGE,     5,  V_BLUEMAP,    true}, // SKINCOLOR_BLUE
	{"Cobalt",     { 145,  147,  149,  150,  151,  153,  154,  155,  156,  157,  158,  159,  253,  253,  254,  254}, SKINCOLOR_PERIDOT,    5,  V_BLUEMAP,    true}, // SKINCOLOR_COBALT
	{"Midnight",   { 171,  171,  172,  173,  173,  174,  175,  157,  158,  159,  253,  253,  254,  254,   31,   31}, SKINCOLOR_CHERRY,     10, V_GRAYMAP,    true}, // SKINCOLOR_MIDNIGHT
	{"Galaxy",     { 160,  161,  162,  163,  164,  165,  166,  166,  154,  155,  156,  157,  159,  253,  254,   31}, SKINCOLOR_ISLAND,     7,  V_PURPLEMAP,  true}, // SKINCOLOR_GALAXY
	{"Vapor",      {0x80, 0x81, 0x83, 0x86, 0x94, 0x94, 0xa3, 0xa3, 0xa4, 0xa6, 0xa6, 0xa6, 0xa8, 0xa8, 0xa9, 0xa9}, SKINCOLOR_LILAC,      4,  V_SKYMAP,     true}, // SKINCOLOR_VAPOR
	{"Dusk",       {0x92, 0x93, 0x94, 0x94, 0xac, 0xad, 0xad, 0xad, 0xae, 0xae, 0xaf, 0xaf, 0xa9, 0xa9, 0xfd, 0xfd}, SKINCOLOR_OLIVE,      0,  V_BLUEMAP,    true}, // SKINCOLOR_DUSK
	{"Majesty",    {   0,    1,  176,  160,  160,  161,  162,  162,  163,  172,  173,  174,  174,  175,  139,  139}, SKINCOLOR_GOLDENROD,  9,  V_PURPLEMAP,  true}, // SKINCOLOR_MAJESTY
	{"Pastel",     {0x90, 0x90, 0xa0, 0xa0, 0xa1, 0xa1, 0xa2, 0xa2, 0xa2, 0xa3, 0xa4, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8}, SKINCOLOR_BUBBLEGUM,  9,  V_PURPLEMAP,  true}, // SKINCOLOR_PASTEL
	{"Purple",     {0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa4, 0xa5, 0xa5, 0xa5, 0xa6, 0xa7, 0xa7, 0xa8, 0xa8, 0xa9, 0xa9}, SKINCOLOR_FLAME,      7,  V_PURPLEMAP,  true}, // SKINCOLOR_PURPLE
	{"Noble",      { 144,  146,  147,  148,  149,  164,  164,  165,  166,  185,  186,  186,  187,  187,   28,   29}, SKINCOLOR_CHARTREUSE, 12, V_PURPLEMAP,  true}, // SKINCOLOR_NOBLE
	{"Fuchsia",    { 200,  201,  203,  204,  204,  183,  184,  184,  165,  166,  167,  168,  169,  159,  253,  254}, SKINCOLOR_LEMON,      10, V_PURPLEMAP,  true}, // SKINCOLOR_FUCHSIA
	{"Bubblegum",  {   0,  208,  208,  176,  177,  178,  179,  180,  181,  182,  164,  166,  167,  168,  169,  253}, SKINCOLOR_PASTEL,     8,  V_MAGENTAMAP, true}, // SKINCOLOR_BUBBLEGUM
	{"Siberite",   { 252,  177,  179,  180,  181,  181,  182,  182,  183,  164,  166,  167,  167,  168,  169,  159}, SKINCOLOR_EMERALD,    8,  V_MAGENTAMAP, true}, // SKINCOLOR_SIBERITE
	{"Magenta",    {0xb3, 0xb3, 0xb4, 0xb5, 0xb6, 0xb6, 0xb7, 0xb7, 0xb7, 0xb8, 0xb9, 0xb9, 0xba, 0xba, 0xbb, 0xbb}, SKINCOLOR_LIME,       6,  V_MAGENTAMAP, true}, // SKINCOLOR_MAGENTA
	{"Neon",       {0xb3, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xb9, 0xba, 0xba, 0xbb, 0xbb, 0xc7, 0xc7, 0x1d, 0x1d, 0x1e}, SKINCOLOR_CERULEAN,   2,  V_MAGENTAMAP, true}, // SKINCOLOR_NEON
	{"Violet",     {0xd0, 0xd1, 0xd2, 0xca, 0xcc, 0xb8, 0xb9, 0xb9, 0xba, 0xa8, 0xa8, 0xa9, 0xa9, 0xfd, 0xfe, 0xfe}, SKINCOLOR_MINT,       6,  V_MAGENTAMAP, true}, // SKINCOLOR_VIOLET
	{"Royal",      { 208,  209,  192,  192,  192,  193,  193,  194,  194,  172,  173,  174,  175,  175,  139,  139}, SKINCOLOR_FANCY,      9,  V_PURPLEMAP,  true}, // SKINCOLOR_ROYAL
	{"Lilac",      {0x00, 0xd0, 0xd1, 0xd2, 0xd3, 0xc1, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc5, 0xc6, 0xc6, 0xfe, 0x1f}, SKINCOLOR_VAPOR,      4,  V_ROSYMAP,    true}, // SKINCOLOR_LILAC
	{"Mauve",      { 176,  177,  178,  192,  193,  194,  195,  195,  196,  185,  185,  186,  186,  187,  187,  253}, SKINCOLOR_GOLD,       4,  V_PURPLEMAP,  true}, // SKINCOLOR_MAUVE
	{"Eventide",   {  51,   52,   53,   33,   34,  204,  183,  183,  184,  184,  166,  167,  168,  169,  253,  254}, SKINCOLOR_DAYBREAK,   13, V_MAGENTAMAP, true}, // SKINCOLOR_EVENTIDE
	{"Plum",       {0xc8, 0xd3, 0xd5, 0xd6, 0xd7, 0xce, 0xcf, 0xb9, 0xb9, 0xba, 0xba, 0xa9, 0xa9, 0xa9, 0xfd, 0xfe}, SKINCOLOR_MINT,       7,  V_ROSYMAP,    true}, // SKINCOLOR_PLUM
	{"Raspberry",  {0xc8, 0xc9, 0xca, 0xcb, 0xcb, 0xcc, 0xcd, 0xcd, 0xce, 0xb9, 0xb9, 0xba, 0xba, 0xbb, 0xfe, 0xfe}, SKINCOLOR_APPLE,      13, V_ROSYMAP,    true}, // SKINCOLOR_RASPBERRY
	{"Taffy",      {   1,  176,  176,  177,  178,  179,  202,  203,  204,  204,  205,  206,  207,   44,   45,   46}, SKINCOLOR_AQUA,       1,  V_ROSYMAP,    true}, // SKINCOLOR_TAFFY
	{"Rosy",       {0xfc, 0xc8, 0xc8, 0xc9, 0xc9, 0xca, 0xca, 0xcb, 0xcb, 0xcc, 0xcc, 0xcd, 0xcd, 0xce, 0xce, 0xcf}, SKINCOLOR_JADE,       8,  V_ROSYMAP,    true}, // SKINCOLOR_ROSY
	{"Fancy",      {   0,  208,   49,  210,  210,  202,  202,  203,  204,  204,  205,  206,  207,  207,  186,  186}, SKINCOLOR_ROYAL,      9,  V_ROSYMAP,    true}, // SKINCOLOR_FANCY
	{"Sangria",    { 210,   32,   33,   34,   34,  215,  215,  207,  207,  185,  186,  186,  186,  169,  169,  253}, SKINCOLOR_TURQUOISE,  12, V_ROSYMAP,    true}, // SKINCOLOR_SANGRIA
	{"Volcanic",   {  54,   36,   42,   44,   45,   46,   46,   47,   28,  253,  253,  254,  254,   30,   31,   31}, SKINCOLOR_BRONZE,     9,  V_REDMAP,     true}, // SKINCOLOR_VOLCANIC

	// super
	{"Super Silver 1", {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x02, 0x03}, SKINCOLOR_BLACK, 15, 0,         false}, // SKINCOLOR_SUPERSILVER1
	{"Super Silver 2", {0x00, 0x01, 0x02, 0x02, 0x03, 0x03, 0x03, 0x03, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x07}, SKINCOLOR_BLACK, 6,  0,         false}, // SKINCOLOR_SUPERSILVER2
	{"Super Silver 3", {0x01, 0x02, 0x02, 0x03, 0x03, 0x03, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x07, 0x09, 0x0b}, SKINCOLOR_BLACK, 5,  0,         false}, // SKINCOLOR_SUPERSILVER3
	{"Super Silver 4", {0x02, 0x03, 0x03, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x07, 0x09, 0x0b, 0x0d, 0x0f, 0x11}, SKINCOLOR_BLACK, 5,  V_GRAYMAP, false}, // SKINCOLOR_SUPERSILVER4
	{"Super Silver 5", {0x03, 0x03, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x07, 0x09, 0x0b, 0x0d, 0x0f, 0x11, 0x13}, SKINCOLOR_BLACK, 5,  V_GRAYMAP, false}, // SKINCOLOR_SUPERSILVER5

	{"Super Red 1", {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd0, 0xd0, 0xd1, 0xd1, 0xd2, 0xd2}, SKINCOLOR_CYAN, 15, 0,         false}, // SKINCOLOR_SUPERRED1
	{"Super Red 2", {0x00, 0x00, 0x00, 0xd0, 0xd0, 0xd0, 0xd1, 0xd1, 0xd1, 0xd2, 0xd2, 0xd2, 0x20, 0x20, 0x21, 0x21}, SKINCOLOR_CYAN, 14, V_ROSYMAP, false}, // SKINCOLOR_SUPERRED2
	{"Super Red 3", {0x00, 0x00, 0xd0, 0xd0, 0xd1, 0xd1, 0xd2, 0xd2, 0x20, 0x20, 0x21, 0x21, 0x22, 0x22, 0x23, 0x23}, SKINCOLOR_CYAN, 13, V_REDMAP,  false}, // SKINCOLOR_SUPERRED3
	{"Super Red 4", {0x00, 0xd0, 0xd1, 0xd1, 0xd2, 0xd2, 0x20, 0x20, 0x21, 0x21, 0x22, 0x22, 0x23, 0x23, 0x24, 0x24}, SKINCOLOR_CYAN, 11, V_REDMAP,  false}, // SKINCOLOR_SUPERRED4
	{"Super Red 5", {0xd0, 0xd1, 0xd2, 0xd2, 0x20, 0x20, 0x21, 0x21, 0x22, 0x22, 0x23, 0x23, 0x24, 0x24, 0x25, 0x25}, SKINCOLOR_CYAN, 10, V_REDMAP,  false}, // SKINCOLOR_SUPERRED5

	{"Super Orange 1", {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd0, 0x30, 0x31, 0x32, 0x33, 0x34}, SKINCOLOR_SAPPHIRE, 15, 0,           false}, // SKINCOLOR_SUPERORANGE1
	{"Super Orange 2", {0x00, 0x00, 0x00, 0x00, 0xd0, 0xd0, 0x30, 0x30, 0x31, 0x31, 0x32, 0x32, 0x33, 0x33, 0x34, 0x34}, SKINCOLOR_SAPPHIRE, 12, V_ORANGEMAP, false}, // SKINCOLOR_SUPERORANGE2
	{"Super Orange 3", {0x00, 0x00, 0xd0, 0xd0, 0x30, 0x30, 0x31, 0x31, 0x32, 0x32, 0x33, 0x33, 0x34, 0x34, 0x35, 0x35}, SKINCOLOR_SAPPHIRE, 9,  V_ORANGEMAP, false}, // SKINCOLOR_SUPERORANGE3
	{"Super Orange 4", {0x00, 0xd0, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x44, 0x45, 0x46}, SKINCOLOR_SAPPHIRE, 4,  V_ORANGEMAP, false}, // SKINCOLOR_SUPERORANGE4
	{"Super Orange 5", {0xd0, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x44, 0x45, 0x46, 0x47}, SKINCOLOR_SAPPHIRE, 3,  V_ORANGEMAP, false}, // SKINCOLOR_SUPERORANGE5

	{"Super Gold 1", {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0x50, 0x51, 0x52, 0x53, 0x48, 0x48, 0x48}, SKINCOLOR_CORNFLOWER, 15, 0,           false}, // SKINCOLOR_SUPERGOLD1
	{"Super Gold 2", {0x00, 0x50, 0x51, 0x52, 0x53, 0x49, 0x49, 0x49, 0x49, 0x49, 0x49, 0x49, 0x40, 0x41, 0x41, 0x41}, SKINCOLOR_CORNFLOWER, 9,  V_YELLOWMAP, false}, // SKINCOLOR_SUPERGOLD2
	{"Super Gold 3", {0x51, 0x52, 0x53, 0x53, 0x48, 0x49, 0x49, 0x49, 0x49, 0x49, 0x40, 0x41, 0x42, 0x43, 0x43, 0x43}, SKINCOLOR_CORNFLOWER, 8,  V_YELLOWMAP, false}, // SKINCOLOR_SUPERGOLD3
	{"Super Gold 4", {0x53, 0x48, 0x48, 0x49, 0x49, 0x49, 0x49, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x46, 0x46}, SKINCOLOR_CORNFLOWER, 8,  V_YELLOWMAP, false}, // SKINCOLOR_SUPERGOLD4
	{"Super Gold 5", {0x48, 0x48, 0x49, 0x49, 0x49, 0x40, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x47, 0x47}, SKINCOLOR_CORNFLOWER, 8,  V_YELLOWMAP, false}, // SKINCOLOR_SUPERGOLD5

	{"Super Peridot 1", {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x58, 0x58, 0x58, 0xbc, 0xbc, 0xbc}, SKINCOLOR_COBALT, 15, 0,            false}, // SKINCOLOR_SUPERPERIDOT1
	{"Super Peridot 2", {0x00, 0x58, 0x58, 0x58, 0xbc, 0xbc, 0xbc, 0xbc, 0xbd, 0xbd, 0xbd, 0xbd, 0xbd, 0xbd, 0xbe, 0xbe}, SKINCOLOR_COBALT, 4,  V_PERIDOTMAP, false}, // SKINCOLOR_SUPERPERIDOT2
	{"Super Peridot 3", {0x58, 0x58, 0xbc, 0xbc, 0xbc, 0xbc, 0xbd, 0xbd, 0xbd, 0xbd, 0xbd, 0xbd, 0xbe, 0xbe, 0xbf, 0xbf}, SKINCOLOR_COBALT, 3,  V_PERIDOTMAP, false}, // SKINCOLOR_SUPERPERIDOT3
	{"Super Peridot 4", {0x58, 0xbc, 0xbc, 0xbd, 0xbd, 0xbd, 0xbd, 0xbd, 0xbd, 0xbe, 0xbe, 0xbf, 0xbf, 0x5e, 0x5e, 0x5f}, SKINCOLOR_COBALT, 3,  V_PERIDOTMAP, false}, // SKINCOLOR_SUPERPERIDOT4
	{"Super Peridot 5", {0xbc, 0xbc, 0xbd, 0xbd, 0xbd, 0xbd, 0xbd, 0xbd, 0xbe, 0xbe, 0xbf, 0xbf, 0x5e, 0x5e, 0x5f, 0x77}, SKINCOLOR_COBALT, 3,  V_PERIDOTMAP, false}, // SKINCOLOR_SUPERPERIDOT5

	{"Super Sky 1", {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x81, 0x82, 0x83, 0x84}, SKINCOLOR_RUST, 15, 0,        false}, // SKINCOLOR_SUPERSKY1
	{"Super Sky 2", {0x00, 0x80, 0x81, 0x82, 0x83, 0x83, 0x84, 0x84, 0x85, 0x85, 0x85, 0x85, 0x85, 0x85, 0x86, 0x86}, SKINCOLOR_RUST, 4,  V_SKYMAP, false}, // SKINCOLOR_SUPERSKY2
	{"Super Sky 3", {0x81, 0x82, 0x83, 0x83, 0x84, 0x84, 0x85, 0x85, 0x85, 0x85, 0x85, 0x85, 0x86, 0x86, 0x87, 0x87}, SKINCOLOR_RUST, 3,  V_SKYMAP, false}, // SKINCOLOR_SUPERSKY3
	{"Super Sky 4", {0x83, 0x84, 0x84, 0x85, 0x85, 0x85, 0x85, 0x85, 0x85, 0x86, 0x86, 0x87, 0x87, 0x88, 0x89, 0x8a}, SKINCOLOR_RUST, 3,  V_SKYMAP, false}, // SKINCOLOR_SUPERSKY4
	{"Super Sky 5", {0x84, 0x84, 0x85, 0x85, 0x85, 0x85, 0x85, 0x85, 0x86, 0x86, 0x87, 0x87, 0x88, 0x89, 0x8a, 0x8b}, SKINCOLOR_RUST, 3,  V_SKYMAP, false}, // SKINCOLOR_SUPERSKY5

	{"Super Purple 1", {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0x90, 0xa0, 0xa0, 0xa1, 0xa2}, SKINCOLOR_EMERALD, 15, 0,           false}, // SKINCOLOR_SUPERPURPLE1
	{"Super Purple 2", {0x00, 0x90, 0xa0, 0xa0, 0xa1, 0xa1, 0xa2, 0xa2, 0xa3, 0xa3, 0xa3, 0xa3, 0xa4, 0xa4, 0xa5, 0xa5}, SKINCOLOR_EMERALD, 4,  V_PURPLEMAP, false}, // SKINCOLOR_SUPERPURPLE2
	{"Super Purple 3", {0xa0, 0xa0, 0xa1, 0xa1, 0xa2, 0xa2, 0xa3, 0xa3, 0xa3, 0xa3, 0xa4, 0xa4, 0xa5, 0xa5, 0xa6, 0xa6}, SKINCOLOR_EMERALD, 0,  V_PURPLEMAP, false}, // SKINCOLOR_SUPERPURPLE3
	{"Super Purple 4", {0xa1, 0xa2, 0xa2, 0xa3, 0xa3, 0xa3, 0xa3, 0xa4, 0xa4, 0xa5, 0xa5, 0xa6, 0xa6, 0xa7, 0xa8, 0xa9}, SKINCOLOR_EMERALD, 0,  V_PURPLEMAP, false}, // SKINCOLOR_SUPERPURPLE4
	{"Super Purple 5", {0xa2, 0xa2, 0xa3, 0xa3, 0xa3, 0xa3, 0xa4, 0xa4, 0xa5, 0xa5, 0xa6, 0xa6, 0xa7, 0xa8, 0xa9, 0xfd}, SKINCOLOR_EMERALD, 0,  V_PURPLEMAP, false}, // SKINCOLOR_SUPERPURPLE5

	{"Super Rust 1", {0x00, 0xd0, 0xd0, 0xd0, 0x30, 0x30, 0x31, 0x32, 0x33, 0x37, 0x3a, 0x44, 0x45, 0x46, 0x47, 0x2e}, SKINCOLOR_CYAN, 14, V_ORANGEMAP, false}, // SKINCOLOR_SUPERRUST1
	{"Super Rust 2", {0x30, 0x31, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x38, 0x3a, 0x44, 0x45, 0x46, 0x47, 0x47, 0x2e}, SKINCOLOR_CYAN, 10, V_ORANGEMAP, false}, // SKINCOLOR_SUPERRUST2
	{"Super Rust 3", {0x31, 0x32, 0x33, 0x34, 0x36, 0x37, 0x38, 0x3a, 0x44, 0x45, 0x45, 0x46, 0x46, 0x47, 0x2e, 0x2e}, SKINCOLOR_CYAN, 9,  V_ORANGEMAP, false}, // SKINCOLOR_SUPERRUST3
	{"Super Rust 4", {0x48, 0x40, 0x41, 0x42, 0x43, 0x44, 0x44, 0x45, 0x45, 0x46, 0x46, 0x47, 0x47, 0x2e, 0x2e, 0x2e}, SKINCOLOR_CYAN, 8,  V_ORANGEMAP, false}, // SKINCOLOR_SUPERRUST4
	{"Super Rust 5", {0x41, 0x42, 0x43, 0x43, 0x44, 0x44, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xed, 0xee, 0xee, 0xef, 0xef}, SKINCOLOR_CYAN, 8,  V_ORANGEMAP, false}, // SKINCOLOR_SUPERRUST5

	{"Super Tan 1", {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0x50, 0x51, 0x51, 0x52, 0x52}, SKINCOLOR_BROWN, 14, 0,          false}, // SKINCOLOR_SUPERTAN1
	{"Super Tan 2", {0x00, 0x50, 0x50, 0x51, 0x51, 0x52, 0x52, 0x52, 0x54, 0x54, 0x54, 0x54, 0x55, 0x56, 0x57, 0xf5}, SKINCOLOR_BROWN, 13, V_BROWNMAP, false}, // SKINCOLOR_SUPERTAN2
	{"Super Tan 3", {0x50, 0x51, 0x51, 0x52, 0x52, 0x52, 0x54, 0x54, 0x54, 0x54, 0x55, 0x56, 0x57, 0xf5, 0xf7, 0xf9}, SKINCOLOR_BROWN, 12, V_BROWNMAP, false}, // SKINCOLOR_SUPERTAN3
	{"Super Tan 4", {0x51, 0x52, 0x52, 0x52, 0x52, 0x54, 0x54, 0x54, 0x55, 0x56, 0x57, 0xf5, 0xf7, 0xf9, 0xfb, 0xed}, SKINCOLOR_BROWN, 11, V_BROWNMAP, false}, // SKINCOLOR_SUPERTAN4
	{"Super Tan 5", {0x52, 0x52, 0x54, 0x54, 0x54, 0x55, 0x56, 0x57, 0xf5, 0xf7, 0xf9, 0xfb, 0xed, 0xee, 0xef, 0xef}, SKINCOLOR_BROWN, 10, V_BROWNMAP, false}  // SKINCOLOR_SUPERTAN5
};

/** Patches the mobjinfo, state, and skincolor tables.
  * Free slots are emptied out and set to initial values.
  */
void P_PatchInfoTables(void)
{
	UINT32 i;
	char *tempname;

#if NUMSPRITEFREESLOTS > 9999 //tempname numbering actually starts at SPR_FIRSTFREESLOT, so the limit is actually 9999 + SPR_FIRSTFREESLOT-1, but the preprocessor doesn't understand enums, so its left at 9999 for safety
"Update P_PatchInfoTables, you big dumb head"
#endif

	// empty out free slots
	for (i = SPR_FIRSTFREESLOT; i <= SPR_LASTFREESLOT; i++)
	{
		tempname = sprnames[i];
		tempname[0] = (char)('0' + (char)((i-SPR_FIRSTFREESLOT+1)/1000));
		tempname[1] = (char)('0' + (char)(((i-SPR_FIRSTFREESLOT+1)/100)%10));
		tempname[2] = (char)('0' + (char)(((i-SPR_FIRSTFREESLOT+1)/10)%10));
		tempname[3] = (char)('0' + (char)((i-SPR_FIRSTFREESLOT+1)%10));
		tempname[4] = '\0';
#ifdef HWRENDER
		t_lspr[i] = &lspr[NOLIGHT];
#endif
	}
	memset(&skincolors[SKINCOLOR_FIRSTFREESLOT], 0, sizeof (skincolor_t) * NUMCOLORFREESLOTS);
	for (i = SKINCOLOR_FIRSTFREESLOT; i <= SKINCOLOR_LASTFREESLOT; i++) {
		skincolors[i].accessible = false;
		skincolors[i].name[0] = '\0';
	}
}

#ifdef ALLOW_RESETDATA
static char *sprnamesbackup;
static skincolor_t *skincolorsbackup;
static size_t sprnamesbackupsize, skincolorsbackupsize;
#endif

UINT32 P_AllocateMobjinfo(const char *name)
{
	mobjinfo = Z_Realloc(mobjinfo, sizeof(*mobjinfo) * ++nummobjinfo, PU_STATIC, NULL);
	mobjinfo[nummobjinfo-1] = Z_Malloc(sizeof(mobjinfo_t), PU_STATIC, NULL);
	memset(mobjinfo[nummobjinfo-1], 0, sizeof(mobjinfo_t));
	mobjinfo[nummobjinfo-1]->name = name;
	mobjinfo[nummobjinfo-1]->doomednum = -1;
	return nummobjinfo-1;
}

UINT32 P_AllocateState(const char *name)
{
	states = Z_Realloc(states, sizeof(*states) * ++numstates, PU_STATIC, NULL);
	states[numstates-1] = Z_Malloc(sizeof(state_t), PU_STATIC, NULL);
	memset(states[numstates-1], 0, sizeof(state_t));
	states[numstates-1]->num = numstates-1;
	states[numstates-1]->name = name;
	return numstates-1;
}

UINT32 P_GetMobjinfoIndex(mobjinfo_t *info)
{
	UINT32 i;
	for (i = 0; i < nummobjinfo; i++)
	{
		if (mobjinfo[i] == info)
			return i;
	}
	I_Error("Tried to get index of an invalid mobjinfo_t!");
}

void P_InitializeTables(void)
{
	UINT32 i;
	nummobjinfo = sizeof(startmobjinfo) / sizeof(startmobjinfo[0]);
	mobjinfo = Z_Malloc(sizeof(*mobjinfo) * nummobjinfo, PU_STATIC, NULL);
	for (i = 0; i < nummobjinfo; i++)
	{
		mobjinfo[i] = Z_Malloc(sizeof(mobjinfo_t), PU_STATIC, NULL);
		memcpy(mobjinfo[i], &startmobjinfo[i], sizeof(mobjinfo_t));
	}

	numstates = sizeof(startstates) / sizeof(startstates[0]);
	states = Z_Malloc(sizeof(*states) * numstates, PU_STATIC, NULL);
	for (i = 0; i < numstates; i++)
	{
		states[i] = Z_Malloc(sizeof(state_t), PU_STATIC, NULL);
		memcpy(states[i], &startstates[i], sizeof(state_t));
		states[i]->num = i;
	}
}

void P_BackupTables(void)
{
#ifdef ALLOW_RESETDATA
	// Allocate buffers in size equal to that of the uncompressed data to begin with
	sprnamesbackup = Z_Malloc(sizeof(sprnames), PU_STATIC, NULL);
	skincolorsbackup = Z_Malloc(sizeof(skincolors), PU_STATIC, NULL);

	// Sprite names
	sprnamesbackupsize = lzf_compress(sprnames, sizeof(sprnames), sprnamesbackup, sizeof(sprnames));
	if (sprnamesbackupsize > 0)
		sprnamesbackup = Z_Realloc(sprnamesbackup, sprnamesbackupsize, PU_STATIC, NULL);
	else
		M_Memcpy(sprnamesbackup, sprnames, sizeof(sprnames));

	//Skincolor info
	skincolorsbackupsize = lzf_compress(skincolors, sizeof(skincolors), skincolorsbackup, sizeof(skincolors));
	if (skincolorsbackupsize > 0)
		skincolorsbackup = Z_Realloc(skincolorsbackup, skincolorsbackupsize, PU_STATIC, NULL);
	else
		M_Memcpy(skincolorsbackup, skincolors, sizeof(skincolors));
#endif
}

void P_ResetData(INT32 flags)
{
#ifndef ALLOW_RESETDATA
	(void)flags;
	CONS_Alert(CONS_NOTICE, M_GetText("P_ResetData(): not supported in this build.\n"));
#else
	UINT32 i;
	if (flags & 1)
	{
		if (sprnamesbackupsize > 0)
			lzf_decompress(sprnamesbackup, sprnamesbackupsize, sprnames, sizeof(sprnames));
		else
			M_Memcpy(sprnames, sprnamesbackup, sizeof(sprnamesbackup));
	}

	if (flags & 2)
	{
		for (i = 0; i < sizeof(startstates) / sizeof(startstates[0]); i++)
		{
			memcpy(states[i], &startstates[i], sizeof(state_t));
			states[i]->num = i;
		}
	}

	if (flags & 4)
	{
		for (i = 0; i < sizeof(startmobjinfo) / sizeof(startmobjinfo[0]); i++)
		{
			memcpy(mobjinfo[i], &startmobjinfo[i], sizeof(mobjinfo_t));
		}
	}

	if (flags & 8)
	{
		if (skincolorsbackupsize > 0)
			lzf_decompress(skincolorsbackup, skincolorsbackupsize, skincolors, sizeof(skincolors));
		else
			M_Memcpy(skincolors, skincolorsbackup, sizeof(skincolorsbackup));
	}
#endif
}
