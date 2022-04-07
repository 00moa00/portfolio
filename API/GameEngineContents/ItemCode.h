#pragma once

enum class ITEM{
	WEEDS = 0,
	WILD_HORSERADISH = 16,
	DAFFODIL = 18,
	LEEK = 20,
	DANDELION = 22,
	PARSNIP = 24,
	LUMBER = 30,
	EMERALD = 60,
	AQUAMARINE = 62,
	RUBY = 64,
	AMETHYST = 66,
	TOPAZ = 68,
	JADE = 70,
	DIAMOND = 72,
	PRISMATIC_SHARD = 74,
	//STONE = 75,
	//STONE = 76,
	//STONE = 77,
	CAVE_CARROT = 78,
	SECRET_NOTE = 79,
	QUARTZ = 80,
	FIRE_QUARTZ = 82,
	FROZEN_TEAR = 84,
	EARTH_CRYSTAL = 86,
	COCONUT = 88,
	CACTUS_FRUIT = 90,
	SAP = 92,
	TORCH = 93,
	SPIRIT_TORCH = 94,
	DWARF_SCROLL_I = 96,
	DWARF_SCROLL_II = 97,
	DWARF_SCROLL_III = 98,
	DWARF_SCROLL_IV = 99,
	CHIPPED_AMPHORA = 100,
	ARROWHEAD = 101,
	LOST_BOOK = 102,
	ANCIENT_DOLL = 103,
	ELVISH_JEWELRY = 104,
	CHEWING_STICK = 105,
	ORNAMENTAL_FAN = 106,
	DINOSAUR_EGG = 107,
	RARE_DISC = 108,
	ANCIENT_SWORD = 109,
	RUSTY_SPOON = 110,
	RUSTY_SPUR = 111,
	RUSTY_COG = 112,
	CHICKEN_STATUE = 113,
	ANCIENT_SEED = 114,
	PREHISTORIC_TOOL = 115,
	DRIED_STARFISH = 116,
	ANCHOR = 117,
	GLASS_SHARDS = 118,
	BONE_FLUTE = 119,
	PREHISTORIC_HANDAXE = 120,
	DWARVISH_HELM = 121,
	DWARF_GADGET = 122,
	ANCIENT_DRUM = 123,
	GOLDEN_MASK = 124,
	GOLDEN_RELIC = 125,
	//STRANGE_DOLL = 126,
	//STRANGE_DOLL = 127,
	PUFFERFISH = 128,
	ANCHOVY = 129,
	TUNA = 130,
	SARDINE = 131,
	BREAM = 132,
	LARGEMOUTH_BASS = 136,
	SMALLMOUTH_BASS = 137,
	RAINBOW_TROUT = 138,
	SALMON = 139,
	WALLEYE = 140,
	PERCH = 141,
	CARP = 142,
	CATFISH = 143,
	PIKE = 144,
	SUNFISH = 145,
	RED_MULLET = 146,
	HERRING = 147,
	EEL = 148,
	OCTOPUS = 149,
	RED_SNAPPER = 150,
	SQUID = 151,
	SEAWEED = 152,
	GREEN_ALGAE = 153,
	SEA_CUCUMBER = 154,
	SUPER_CUCUMBER = 155,
	GHOSTFISH = 156,
	WHITE_ALGAE = 157,
	STONEFISH = 158,
	CRIMSONFISH = 159,
	ANGLER = 160,
	ICE_PIP = 161,
	LAVA_EEL = 162,
	LEGEND = 163,
	SANDFISH = 164,
	SCORPION_CARP = 165,
	TREASURE_CHEST = 166,
	JOJA_COLA = 167,
	TRASH = 168,
	DRIFTWOOD = 169,
	BROKEN_GLASSES = 170,
	BROKEN_CD = 171,
	SOGGY_NEWSPAPER = 172,
	EGG = 176,
	LARGE_EGG = 174,
	HAY = 178,
	//EGG = 180,
	//LARGE_EGG = 182,
	MILK = 184,
	LARGE_MILK = 186,
	GREEN_BEAN = 188,
	FIDDLEHEAD_RISOTTO = 189,

	CAULIFLOWER = 190,
	POTATO = 192,
	FRIED_EGG = 194,
	OMELET = 195,
	SALAD = 196,
	CHEESE_CAULIFLOWER = 197,
	BAKED_FISH = 198,
	PARSNIP_SOUP = 199,
	VEGETABLE_MEDLEY = 200,
	COMPLETE_BREAKFAST = 201,
	FRIED_CALAMARI = 202,
	STRANGE_BUN = 203,
	LUCKY_LUNCH = 204,
	FRIED_MUSHROOM = 205,
	PIZZA = 206,
	BEAN_HOTPOT = 207,
	GLAZED_YAMS = 208,
	CARP_SURPRISE = 209,
	HASHBROWNS = 210,
	PANCAKES = 211,
	SALMON_DINNER = 212,
	FISH_TACO = 213,
	CRISPY_BASS = 214,
	PEPPER_POPPERS = 215,
	//BREAD = 216,
	//BREAD = 217,
	TOM_KHA_SOUP = 218,
	TROUT_SOUP = 219,
	CHOCOLATE_CAKE = 220,
	PINK_CAKE = 221,
	RHUBARB_PIE = 222,
	COOKIE = 223,
	SPAGHETTI = 224,
	FRIED_EEL = 225,
	SPICY_EEL = 226,
	SASHIMI = 227,
	MAKI_ROLL = 228,
	TORTILLA = 229,
	RED_PLATE = 230,
	EGGPLANT_PARMESAN = 231,
	RICE_PUDDING = 232,
	ICE_CREAM = 233,
	BLUEBERRY_TART = 234,
	AUTUMN_BOUNTY = 235,
	PUMPKIN_SOUP = 236,
	SUPER_MEAL = 237,
	CRANBERRY_SAUCE = 238,
	STUFFING = 239,
	FARMER_LUNCH = 240,
	SURVIVAL_BURGER = 241,
	DISH_O_THE_SEA = 242,
	MINER_TREAT = 243,
	ROOTS_PLATTER = 244,
	SUGAR = 245,
	WHEAT_FLOUR = 246,
	OIL = 247,
	GARLIC = 248,
	KALE = 250,
	RHUBARB = 252,
	MELON = 254,
	TOMATO = 256,
	MOREL = 257,
	BLUEBERRY = 258,
	FIDDLEHEAD_FERN = 259,
	HOT_PEPPER = 260,
	WHEAT = 262,
	RADISH = 264,
	RED_CABBAGE = 266,
	STARFRUIT = 268,
	CORN = 270,
	EGGPLANT = 272,
	ARTICHOKE = 274,
	PUMPKIN = 276,
	BOK_CHOY = 278,
	YAM = 280,
	CHANTERELLE = 281,
	CRANBERRIES = 282,
	HOLLY = 283,
	BEET = 284,
	CHERRY_BOMB = 286,
	BOMB = 287,
	MEGA_BOMB = 288,
	SPEED_BOBBER = 289,
	STONE = 290,
	SPECIFIC_BOBBER = 291,
	CHEAP_DETECTOR = 292,
	STANDARD_DETECTOR = 293,
	//TWIG = 294,
	//TWIG = 295,
	SALMONBERRY = 296,
	GRASS_STARTER = 297,
	HARDWOOD_FENCE = 298,
	AMARANTH_SEEDS = 299,
	AMARANTH = 300,
	GRAPE_STARTER = 301,
	HOPS_STARTER = 302,
	PALE_ALE = 303,
	HOPS = 304,
	VOID_EGG = 305,
	MAYONNAISE = 306,
	DUCK_MAYONNAISE = 307,
	VOID_MAYONNAISE = 308,
	ACORN = 309,
	MAPLE_SEED = 310,
	PINE_CONE = 311,
	SPRING_BENCH = 312,
	//WEEDS = 313,
	//WEEDS = 314,
	//WEEDS = 315,
	//WEEDS = 316,
	//WEEDS = 317,
	//WEEDS = 318,
	//WEEDS = 319,
	//WEEDS = 320,
	//WEEDS = 321,
	WOOD_FENCE = 322,
	STONE_FENCE = 323,
	IRON_FENCE = 324,
	GATE = 325,
	DWARVISH_TRANSLATION_GUIDE = 326,

	PURPLE_DYE = 327,
	WOOD_FLOOR = 328,
	STONE_FLOOR = 329,
	CLAY = 330,
	WEATHERED_FLOOR = 331,
	POT = 332,
	CRYSTAL_FLOOR = 333,

	COPPER_BAR = 334,
	IRON_BAR = 335,
	GOLD_BAR = 336,
	IRIDIUM_BAR = 337,
	REFINED_QUARTZ = 338,
	QUARTZ_GLOBE = 339,
	HONEY = 340,
	TEA_SET = 341,
	PICKLES = 342,
	//STONE = 343,
	JELLY = 344,
	BEER = 346,
	RARE_SEED = 347,
	WINE = 348,
	ENERGY_TONIC = 349,
	JUICE = 350,
	MUSCLE_REMEDY = 351,
	BASIC_FERTILIZER = 368,
	QUALITY_FERTILIZER = 369,
	BASIC_RETAINING_SOIL = 370,
	QUALITY_RETAINING_SOIL = 371,
	CLAM = 372,
	GOLDEN_PUMPKIN = 373,
	GIZMO = 374,
	//GIZMO = 375,
	POPPY = 376,
	COPPER_ORE = 378,
	IRON_ORE = 380,
	COAL = 382,
	GOLD_ORE = 384,
	IRIDIUM_ORE = 386,
	WOOD = 388,
	//STONE = 390,
	NAUTILUS_SHELL = 392,
	CORAL = 393,
	RAINBOW_SHELL = 394,
	COFFEE = 395,
	SPICE_BERRY = 396,
	SEA_URCHIN = 397,
	GRAPE = 398,
	SPRING_ONION = 399,
	STRAWBERRY = 400,
	STRAW_FLOOR = 401,
	SWEET_PEA = 402,
	FIELD_SNACK = 403,
	COMMON_MUSHROOM = 404,
	WOOD_PATH = 405,
	WILD_PLUM = 406,
	GRAVEL_PATH = 407,
	HAZELNUT = 408,
	CRYSTAL_PATH = 409,
	BLACKBERRY = 410,
	COBBLESTONE_PATH = 411,
	WINTER_ROOT = 412,
	BLUE_SLIME_EGG = 413,
	CRYSTAL_FRUIT = 414,
	STEPPING_STONE_PATH = 415,
	SNOW_YAM = 416,
	SWEET_GEM_BERRY = 417,
	CROCUS = 418,
	VINEGAR = 419,
	RED_MUSHROOM = 420,
	SUNFLOWER = 421,
	PURPLE_MUSHROOM = 422,
	RICE = 423,
	CHEESE = 424,
	FAIRY_SEEDS = 425,
	GOAT_CHEESE = 426,
	TULIP_BULB = 427,
	CLOTH = 428,
	JAZZ_SEEDS = 429,
	TRUFFLE = 430,
	SUNFLOWER_SEEDS = 431,
	TRUFFLE_OIL = 432,
	COFFEE_BEAN = 433,
	STARDROP = 434,
	GOAT_MILK = 436,
	RED_SLIME_EGG = 437,
	//GOAT_MILK = 438,
	PURPLE_SLIME_EGG = 439,
	WOOL = 440,
	EXPLOSIVE_AMMO = 441,
	DUCK_EGG = 442,
	DUCK_FEATHER = 444,
	RABBIT_FOOT = 446,
	STONE_BASE = 449,
	//STONE = 450,
	//WEEDS = 452,
	POPPY_SEEDS = 453,
	ANCIENT_FRUIT = 454,
	SPANGLE_SEEDS = 455,

	ALGAE_SOUP = 456,
	PALE_BROTH = 457,
	BOUQUET = 458,
	MEAD = 459,
	MERMAID_PENDANT = 460,
	DECORATIVE_POT = 461,
	GLASS_PANE = 462,
	DRUM_BLOCK = 463,
	FLUTE_BLOCK = 464,
	SPEED_GRO = 465,
	DELUXE_SPEED_GRO = 466,
	STARDEW_HERO_TROPHY = 468,

	GROUND_LIGHT = 469,

	TABLE_LAMP = 470,
	KEY = 471,
	PARSNIP_SEEDS = 472,
	BEAN_STARTER = 473,
	CAULIFLOWER_SEEDS = 474,

	POTATO_SEEDS = 475,
	GARLIC_SEEDS = 476,
	KALE_SEEDS = 477,
	RHUBARB_SEEDS = 478,
	MELON_SEEDS = 479,
	TOMATO_SEEDS = 480,
	BLUEBERRY_SEEDS = 481,
	PEPPER_SEEDS = 482,
	WHEAT_SEEDS = 483,
	RADISH_SEEDS = 484,
	RED_CABBAGE_SEEDS = 485,

	STARFRUIT_SEEDS = 486,
	CORN_SEEDS = 487,
	EGGPLANT_SEEDS = 488,
	ARTICHOKE_SEEDS = 489,
	PUMPKIN_SEEDS = 490,
	BOK_CHOY_SEEDS = 491,

	YAM_SEEDS = 492,
	CRANBERRY_SEEDS = 493,
	BEET_SEEDS = 494,
	SPRING_SEEDS = 495,
	SUMMER_SEEDS = 496,
	FALL_SEEDS = 497,
	WINTER_SEEDS = 498,
	ANCIENT_SEEDS = 499,
	SMALL_GLOW_RING = 516,
	GLOW_RING = 517,
	SMALL_MAGNET_RING = 518,
	MAGNET_RING = 519,
	SLIME_CHARMER_RING = 520,

	WARRIOR_RING = 521,
	VAMPIRE_RING = 522,
	SAVAGE_RING = 523,
	RING_OF_YOBA = 524,
	STURDY_RING = 525,
	BURGLAR_RING = 526,
	IRIDIUM_BAND = 527,
	JUKEBOX_RING = 528,
	AMETHYST_RING = 529,
	TOPAZ_RING = 530,
	AQUAMARINE_RING = 531,
	JADE_RING = 532,
	EMERALD_RING = 533,
	RUBY_RING = 534,
	GEODE = 535,
	FROZEN_GEODE = 536,

	MAGMA_GEODE = 537,
	ALAMITE = 538,
	BIXITE = 539,
	BARYTE = 540,
	AERINITE = 541,
	CALCITE = 542,
	DOLOMITE = 543,
	ESPERITE = 544,
	FLUORAPATITE = 545,
	GEMINITE = 546,
	HELVITE = 547,
	JAMBORITE = 548,
	JAGOITE = 549,
	KYANITE = 550,
	LUNARITE = 551,
	MALACHITE = 552,
	NEPTUNITE = 553,
	LEMON_STONE = 554,
	NEKOITE = 555,
	ORPIMENT = 556,
	PETRIFIED_SLIME = 557,
	THUNDER_EGG = 558,
	PYRITE = 559,
	OCEAN_STONE = 560,
	GHOST_CRYSTAL = 561,

	TIGERSEYE = 562,
	JASPER = 563,
	OPAL = 564,
	FIRE_OPAL = 565,
	CELESTINE = 566,
	MARBLE = 567,
	SANDSTONE = 568,
	GRANITE = 569,
	BASALT = 570,
	LIMESTONE = 571,
	SOAPSTONE = 572,
	HEMATITE = 573,
	MUDSTONE = 574,
	OBSIDIAN = 575,
	SLATE = 576,
	FAIRY_STONE = 577,
	STAR_SHARDS = 578,
	PREHISTORIC_SCAPULA = 579,

	PREHISTORIC_TIBIA = 580,
	PREHISTORIC_SKULL = 581,
	SKELETAL_HAND = 582,
	PREHISTORIC_RIB = 583,

	PREHISTORIC_VERTEBRA = 584,
	SKELETAL_TAIL = 585,
	NAUTILUS_FOSSIL = 586,
	AMPHIBIAN_FOSSIL = 587,
	PALM_FOSSIL = 588,
	TRILOBITE = 589,
	ARTIFACT_SPOT = 590,
	TULIP = 591,
	SUMMER_SPANGLE = 593,
	FAIRY_ROSE = 595,
	BLUE_JAZZ = 597,
	SPRINKLER = 599,
	PLUM_PUDDING = 604,
	ARTICHOKE_DIP = 605,
	STIR_FRY = 606,
	ROASTED_HAZELNUTS = 607,
	PUMPKIN_PIE = 608,
	RADISH_SALAD = 609,
	FRUIT_SALAD = 610,
	BLACKBERRY_COBBLER = 611,

	CRANBERRY_CANDY = 612,
	APPLE = 613,
	TEA_LEAVES = 614,
	SPICE_BERRY_TEA = 615,

	TEA_EGG = 616,
	TUNA_FISH_SANDWICH = 617,
	BRUSCHETTA = 618,
	STRAWBERRY_MILKSHAKE = 619,

	QUALITY_SPRINKLER = 621,

	CHERRY_SAPLING = 628,
	APRICOT_SAPLING = 629,
	ORANGE_SAPLING = 630,
	PEACH_SAPLING = 631,
	POMEGRANATE_SAPLING = 632,
	APPLE_SAPLING = 633,
	APRICOT = 634,
	ORANGE = 635,
	PEACH = 636,
	POMEGRANATE = 637,
	CHERRY = 638,
	BEEF = 639,
	PORK = 640,
	CHICKEN = 641,
	DUCK = 642,
	RABBIT = 643,
	CHEAP_MEAT = 644,
	IRIDIUM_SPRINKLER = 645,

	COLESLAW = 648,
	//FIDDLEHEAD_RISOTTO = 649,
	
	HORSERADISH_BEETS = 650,

	POPPYSEED_MUFFIN = 651,
	MEATLOAF = 652,
	ORANGE_CHICKEN = 653,
	MONTE_CRISTO = 654,
	BACON_CHEESEBURGER = 655,

	ROAST_DUCK = 656,
	RABBIT_AU_VIN = 657,
	STEAK_FAJITAS = 658,

	GLAZED_HAM = 659,
	SUMMER_SAUSAGE = 660,
	SWEET_AND_SOUR_PORK = 661,
	RABBIT_STEW = 662,
	WINTER_DUCK = 663,
	STEAK_WITH_MUSHROOMS = 664,
	COWBOY_DINNER = 665,
	BACON = 666,
	CLAMS_CASINO = 667,
	//STONE = 668,
	//STONE = 670,
	//WEEDS = 674,
	//WEEDS = 675,
	//WEEDS = 676,
	//WEEDS = 677,
	//WEEDS = 678,
	//WEEDS = 679,
	GREEN_SLIME_EGG = 680,
	RAIN_TOTEM = 681,
	MUTANT_CARP = 682,
	BREAD_BALL = 683,
	BUG_MEAT = 684,
	BAIT = 685,
	SPINNER = 686,
	DRESSED_SPINNER = 687,

	WARP_TOTEM_FARM = 688,


	WARP_TOTEM_MOUNTAINS = 689,
	WARP_TOTEM_BEACH = 690,

	BARBED_HOOK = 691,
	LEAD_BOBBER = 692,
	TREASURE_HUNTER = 693,
	TRAP_BOBBER = 694,
	CORK_BOBBER = 695,
	STURGEON = 698,
	TIGER_TROUT = 699,
	BULLHEAD = 700,
	TILAPIA = 701,
	CHUB = 702,
	MAGNET = 703,
	DORADO = 704,
	ALBACORE = 705,
	SHAD = 706,
	LINGCOD = 707,
	HALIBUT = 708,
	HARDWOOD = 709,
	CRAB_POT = 710,
	LOBSTER = 715,
	CRAYFISH = 716,
	CRAB = 717,
	COCKLE = 718,
	MUSSEL = 719,
	SHRIMP = 720,
	SNAIL = 721,
	PERIWINKLE = 722,
	OYSTER = 723,
	MAPLE_SYRUP = 724,
	OAK_RESIN = 725,
	PINE_TAR = 726,
	CHOWDER = 727,
	FISH_STEW = 728,
	ESCARGOT = 729,
	LOBSTER_BISQUE = 730,
	MAPLE_BAR = 731,
	CRAB_CAKES = 732,
	SHRIMP_COCKTAIL = 733,
	WOODSKIP = 734,
	STRAWBERRY_SEEDS = 745,
	JACK_O_LANTERN = 746,
	ROTTEN_PLANT = 747,
	//ROTTEN_PLANT = 748,
	OMNI_GEODE = 749,
	//WEEDS = 750,
	//STONE = 751,
	//STONE = 760,
	//STONE = 762,
	//STONE = 764,
	//STONE = 765,
	SLIME = 766,
	BAT_WING = 767,
	SOLAR_ESSENCE = 768,
	VOID_ESSENCE = 769,
	MIXED_SEEDS = 770,
	FIBER = 771,
	OIL_OF_GARLIC = 772,
	LIFE_ELIXIR = 773,
	WILD_BAIT = 774,
	GLACIERFISH = 775,
	//WEEDS = 784,
	//WEEDS = 785,
	//WEEDS = 786,
	BATTERY_PACK = 787,
	LOST_AXE = 788,
	LUCKY_PURPLE_SHORTS = 789,

	BERRY_BASKET = 790,
	//WEEDS = 792,
	//WEEDS = 793,
	//WEEDS = 794,
	VOID_SALMON = 795,
	SLIMEJACK = 796,
	PEARL = 797,
	MIDNIGHT_SQUID = 798,

	SPOOK_FISH = 799,
	BLOBFISH = 800,
	WEDDING_RING = 801,
	CACTUS_SEEDS = 802,
	IRIDIUM_MILK = 803,




};