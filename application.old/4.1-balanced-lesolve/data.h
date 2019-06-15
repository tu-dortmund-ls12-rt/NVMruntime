#define RANGE 50

float system[RANGE][RANGE] = {
    {643,  954,  -499, -865, 127,  -641, -188, -364, -993, 353,
     822,  -469, -838, -320, -836, -132, -141, 94,   -714, -713,
     -936, 517,  691,  846,  468,  151,  20,   -404, -853, -473,
     607,  -964, 276,  -666, 251,  -293, -995, 582,  -441, -947,
     206,  -156, -676, -655, 409,  25,   443,  -584, 697,  -371},
    {-636, 865,  -718, -730, 128,  336,  752,  878,  -25,  -245,
     -222, 334,  446,  -332, 129,  -741, 622,  -562, -162, 424,
     -785, -420, -83,  -124, -391, 841,  54,   -945, -125, 406,
     -90,  167,  -204, -492, -196, 667,  490,  -376, -797, -363,
     -65,  -283, 347,  242,  848,  785,  -577, -917, 631,  380},
    {-846, 669,  886,  -539, 235,  -471, -422, 44,   564,  505,
     812,  -905, -456, -783, 646,  918,  -978, 27,   801,  766,
     87,   -32,  192,  -688, 606,  -321, -551, -503, -632, 457,
     618,  -944, -758, -137, -10,  -351, -965, -880, -189, 305,
     -364, 661,  -111, -790, -943, 652,  209,  -263, 921,  -298},
    {-162, 706,  294,  -416, -575, 618,  966,  767,  444,  406,
     399,  -342, 17,   495,  388,  -388, -684, -935, -931, 504,
     -378, -476, -985, 778,  -772, 24,   448,  770,  -67,  319,
     777,  366,  -338, -913, 703,  -218, -711, -486, -833, 55,
     -682, 459,  -677, -709, 345,  757,  794,  -192, -478, 17},
    {740,  -558, -775, 343,  920,  -20,  248,  -273, -947, -267,
     208,  656,  478,  -253, -872, -538, -143, -773, 253,  194,
     -724, 94,   606,  19,   769,  -830, -803, -613, -107, 435,
     340,  -791, -432, -678, -676, 448,  -907, 728,  -736, 749,
     365,  681,  -783, 835,  -139, -114, 467,  16,   -265, -366},
    {521,  -840, -705, -784, 423,  310, 8,    -669, -855, 696,
     -270, -599, 82,   -418, 923,  15,  -556, -913, -983, 256,
     51,   -399, 313,  -213, -312, 497, 635,  500,  -861, 768,
     -160, 882,  -125, -689, -418, 694, 441,  -852, -418, 206,
     125,  -81,  290,  542,  155,  822, -907, 700,  438,  389},
    {-447, 296,  906,  -117, 549,  -685, 590,  -675, 480,  288,
     851,  972,  -350, -158, 13,   843,  348,  -529, 731,  -804,
     184,  -241, -645, -588, -449, 668,  -111, -563, 923,  303,
     -821, -686, 483,  526,  -39,  397,  -88,  824,  -367, -877,
     143,  -897, 675,  908,  -472, 322,  -449, 969,  935,  -505},
    {198, 119, -455, -672, 582,  833,  -178, 222,  -528, 43,   -395, 604,  433,
     535, 352, 878,  599,  227,  247,  -68,  -707, -417, 365,  52,   -534, -288,
     731, 742, -125, -797, 814,  538,  823,  110,  779,  540,  694,  62,   869,
     -4,  191, -527, 626,  -956, -656, 658,  277,  -317, -409, -809},
    {620,  -615, 44,   -603, -456, 0,    384,  332,  503,  -367, -414, 786, 609,
     310,  361,  -42,  -91,  -449, -416, 749,  462,  372,  -143, 789,  492, 337,
     981,  -735, -157, -281, 354,  -619, -83,  -509, -458, -431, 16,   960, 883,
     -441, -791, 531,  -486, -976, 910,  -847, 482,  727,  523,  262},
    {673, -115, -939, -553, -505, 713,  -426, -812, -903, -752,
     590, 492,  -231, 634,  488,  287,  -828, 508,  835,  878,
     758, 17,   393,  593,  266,  1000, 313,  238,  -520, 711,
     214, -658, 255,  372,  -599, -791, 764,  -109, -380, -357,
     540, 392,  97,   741,  -967, -791, 608,  -716, 181,  215},
    {-561, 985,  994,  -671, -650, 237, -524, 30,   502,  902,  188, 671,  305,
     -187, 663,  303,  -144, 721,  298, -929, -795, 136,  -462, 954, 304,  724,
     -253, -283, -484, 611,  432,  485, -810, 215,  -755, 895,  922, -626, 275,
     -760, 560,  -893, -516, 813,  540, 829,  789,  -117, 425,  631},
    {282,  245,  -829, -548, 994,  49,   425,  -382, 226, 97,
     -790, -505, -785, 637,  -92,  605,  474,  881,  952, -901,
     174,  -164, 206,  -757, 230,  249,  -245, 607,  509, 623,
     -758, -397, -56,  -568, -520, -860, 326,  679,  101, -245,
     430,  892,  724,  66,   342,  -942, 624,  -115, 567, 103},
    {-132, 471,  -493, 304,  665,  -968, 569,  999,  141,  -816,
     -697, -728, -944, -502, -206, -132, 240,  -570, 39,   267,
     -471, -161, 195,  -185, -609, 473,  -649, 108,  -940, 86,
     -527, -117, -833, -327, 454,  808,  26,   199,  680,  -255,
     173,  -501, -988, 277,  -185, 400,  803,  -354, -873, 590},
    {100,  382,  523, -912, -967, 621,  1000, 877,  242,  -652, 76,  137,  -236,
     -110, -936, 20,  229,  303,  470,  143,  -723, -845, -532, 602, -287, -234,
     -471, 987,  7,   -64,  636,  -190, -146, -516, 613,  303,  73,  519,  741,
     -534, 523,  679, 348,  45,   -211, 874,  -35,  576,  675,  433},
    {730,  632, 945,  -540, -798, 206,  24,   264,  -473, 674,
     -46,  604, -278, 646,  631,  -927, 537,  -249, -582, -181,
     -983, 124, -919, -161, 463,  757,  -857, -220, 548,  -840,
     25,   567, 21,   -252, -558, -744, 157,  -564, 708,  -844,
     607,  82,  -922, -337, 603,  851,  18,   -262, -793, 105},
    {557,  730,  805, 612,  -262, 346,  560,  -183, 220,  -638, 647, 635, -581,
     520,  -548, 221, -176, 758,  -981, 864,  599,  816,  429,  482, 338, -404,
     -901, 566,  825, 989,  249,  -208, -937, 694,  -716, 666,  195, 741, -85,
     -552, -870, 898, 540,  747,  797,  710,  561,  -564, 364,  878},
    {-880, 404,  -764, 576,  -683, 793,  842, 742,  -591, 682,
     969,  -273, -177, -305, -296, -737, 803, -997, -298, 455,
     -73,  344,  -182, -468, 198,  980,  362, 736,  -806, -574,
     -202, -156, -178, -121, 799,  -113, 594, 522,  43,   -328,
     974,  336,  -69,  242,  425,  -48,  492, -609, 855,  682},
    {-818, -916, -250, 375, 373,  725,  221,  -259, -879, 924, -705, -678, -828,
     847,  619,  270,  948, 484,  51,   -272, -586, -390, 273, -790, -80,  841,
     786,  267,  -690, 862, -496, 16,   505,  -907, -294, 232, -427, 642,  -116,
     -936, 731,  445,  616, -78,  -848, -508, 231,  -14,  277, 434},
    {-736, -843, 249,  -864, 45,  -636, -563, -582, -802, -46,  102, 955,  240,
     -735, 745,  -457, -223, 732, -252, -96,  688,  907,  983,  647, -849, -446,
     563,  -770, -360, -56,  897, 110,  464,  605,  -542, 610,  903, 175,  -564,
     -133, 414,  139,  -860, 916, 268,  -130, -383, -5,   -931, 255},
    {-62,  347,  -604, -576, -997, -559, -730, 53,  -34,  -684,
     -965, -293, -909, 942,  -749, -339, 242,  421, -177, -467,
     -751, -940, 966,  602,  -472, -621, -680, 678, -521, 933,
     841,  874,  95,   278,  311,  126,  432,  421, 616,  178,
     -991, -781, 422,  814,  159,  975,  -177, -58, 668,  -952},
    {-645, 6,   -598, -97, -408, 775,  95,   -143, -904, 594,  -801, 48,   538,
     -711, 524, -727, 10,  361,  -389, -975, 212,  995,  -545, -405, 391,  -82,
     -500, 730, 907,  53,  666,  967,  251,  -405, 182,  336,  -676, -680, 899,
     -320, 496, -945, -74, 437,  396,  -812, -317, -569, -395, -837},
    {209,  -302, 223,  -552, -305, 332,  -682, 178, -480, -392, -65,  725, -53,
     717,  735,  -193, -420, 819,  -30,  750,  119, 516,  886,  -794, 877, -599,
     488,  941,  903,  490,  -946, 766,  225,  732, -718, -138, -513, 613, 853,
     -994, 742,  150,  243,  727,  -174, 23,   216, 789,  -173, 554},
    {-737, 557,  -969, 703, 668, 958, 967, 157,  -686, 39,  858,  697,  426,
     -299, -302, -423, 915, 287, 463, -39, 199,  -528, 221, 919,  -917, 4,
     710,  260,  365,  749, 552, -58, 352, 531,  177,  456, -260, -857, 872,
     -257, -817, 513,  532, 440, -30, 332, -451, -162, 574, 224},
    {349,  741,  -694, 762,  -440, 904,  400,  635,  -199, -418,
     -964, -1,   -568, 453,  -963, -886, -462, 791,  656,  -414,
     596,  442,  149,  28,   -179, 37,   215,  -322, 405,  -924,
     -159, -268, -568, -181, -338, 103,  360,  433,  -577, 528,
     183,  613,  453,  490,  -543, 473,  -612, 411,  -792, 433},
    {370,  147, 164,  -294, 411,  207,  -743, -348, 585,  -432, 560, 882, -93,
     -261, 966, 464,  -573, -770, 365,  660,  -171, -597, -817, 441, -17, 170,
     409,  197, -464, 754,  651,  -943, 90,   -561, 470,  -893, 322, 48,  -40,
     912,  507, -432, -779, -464, -600, 720,  415,  762,  -790, 750},
    {314,  -563, -137, 67,   -775, -538, 917,  -438, -263, -692,
     -354, 16,   -178, 522,  386,  -43,  -591, -807, 271,  -571,
     343,  -550, -733, 856,  -40,  -384, 258,  -997, -439, 194,
     880,  772,  -791, 473,  932,  107,  662,  -741, 171,  796,
     -95,  728,  -610, -248, -597, 555,  33,   378,  681,  -689},
    {-857, 198,  -341, 427,  -798, -344, 8,    826,  333,  -504,
     -466, -58,  -529, -298, -75,  166,  -821, 749,  -76,  -654,
     702,  -350, 917,  -307, 983,  209,  -286, -29,  846,  -865,
     -727, -297, -812, -674, 427,  248,  -329, -890, -885, -87,
     -527, 742,  532,  -481, 939,  -512, 108,  -165, 656,  -885},
    {219,  634,  -839, -565, -962, 215,  752, -873, 632,  -11,
     -227, 370,  -368, 821,  -787, -208, 575, 211,  -847, 987,
     -706, 870,  -240, 101,  -880, -934, -24, 482,  -887, -324,
     218,  -500, -367, 660,  -201, -121, -63, -883, 98,   -400,
     -442, 181,  350,  159,  -642, -298, 263, 595,  -33,  -96},
    {-678, 593,  220,  727,  -970, -201, -326, 41,   -461, -211,
     -538, -727, -688, 891,  612,  -503, -168, 270,  82,   767,
     -445, 254,  -337, 393,  -171, 750,  -632, 129,  -363, 413,
     -244, 123,  626,  -729, 752,  -843, 226,  -157, 450,  968,
     -30,  -672, 757,  -660, -393, -27,  -562, 267,  25,   68},
    {222, -282, -326, 695,  438, 786,  169,  -252, -718, -358, 447, 923,  -452,
     566, -710, 375,  518,  627, -790, -909, 461,  -209, 679,  822, 929,  -111,
     735, -877, -747, -257, -71, 237,  -829, -706, -530, 497,  688, -583, 739,
     939, -438, -469, -313, 145, 154,  -895, -217, -8,   -819, -344},
    {-939, -294, 463,  615, -326, -795, 238, -154, -505, 1,    -209, -988, -449,
     914,  491,  -542, 459, -60,  -835, -20, 474,  525,  856,  -690, -306, -288,
     -564, 194,  172,  5,   870,  -852, 674, -6,   -178, 68,   -775, 477,  662,
     36,   614,  543,  694, -891, -784, 20,  -133, 160,  -807, 462},
    {962,  -419, -872, -803, -807, 825, 850,  64,   285, 385,
     404,  -413, -960, -587, 321,  155, -140, -872, 790, 905,
     694,  -605, -702, -111, -401, -76, -616, 765,  965, -958,
     -195, 39,   550,  -998, -714, 204, 636,  -349, 994, -616,
     79,   332,  -533, 332,  -904, 390, 488,  -251, 853, 623},
    {880,  38,   -871, 648,  -324, -733, 814,  -427, -67,  -208, 142, 309, 612,
     -768, -7,   -80,  -996, -781, 493,  -311, 489,  80,   629,  500, 871, 678,
     -358, -934, -894, -154, 838,  188,  -180, -746, -195, 664,  196, 732, 961,
     -540, 490,  540,  695,  962,  -122, -125, -447, 773,  644,  -178},
    {-253, 641,  100,  -42, -634, -571, -547, -163, 157,  598,
     -782, 703,  -652, 487, -817, 430,  -678, -740, -244, 876,
     -739, -934, -15,  908, -459, 959,  -653, 929,  792,  -763,
     1000, 296,  -66,  412, -45,  70,   -771, -370, -693, 8,
     103,  870,  -102, 374, 654,  -412, -535, -215, -365, 819},
    {-440, 884,  694,  -370, -575, 468, -956, -239, -39,  -237,
     -885, -478, -156, -441, -79,  387, 718,  801,  -621, 969,
     36,   -481, 915,  -152, -744, 638, -392, -919, 190,  -440,
     895,  -482, -945, 852,  454,  463, 767,  -312, 528,  250,
     394,  516,  -389, 621,  -688, 479, -876, -552, -582, 325},
    {476, 871,  686,  -652, 718,  782,  -470, -296, -323, -375,
     210, 887,  -842, 366,  -503, -360, -134, -740, -664, -556,
     552, -340, 347,  67,   -861, 613,  -154, -752, 205,  305,
     646, -723, -415, -224, -102, -867, -607, 464,  -976, -360,
     470, -920, -751, -818, -826, -574, -682, 825,  -954, 942},
    {-238, -525, -136, -820, -238, 509,  792,  967,  542,  -836,
     -873, -482, -947, 765,  -143, -410, 756,  531,  -629, -7,
     792,  -522, -567, 195,  -95,  309,  386,  -726, 949,  406,
     432,  -606, 930,  -151, -230, 959,  -533, -398, 628,  -129,
     -647, -222, 315,  -734, 688,  -275, -551, -594, -412, 604},
    {-23, -25,  -32, -888, -310, -354, 169,  548,  242,  730,  -152, -226, -139,
     299, -322, 48,  -91,  -293, -123, -943, -169, -429, 295,  -552, -412, 645,
     648, -457, 865, -529, 383,  609,  -376, 34,   685,  -905, 78,   -582, -809,
     -92, -11,  979, 238,  774,  271,  -324, 893,  -925, 212,  -685},
    {-64,  150,  466,  -912, 276,  -197, -120, -598, 640,  147,  36,  88,   443,
     -139, -211, -611, 959,  709,  455,  -694, -975, 307,  109,  948, -611, 384,
     -421, 830,  73,   -467, -187, -485, -303, 655,  -407, -563, 199, -882, 53,
     -135, -315, -658, -563, -723, -883, -309, 669,  453,  154,  -630},
    {-222, -303, 671,  364,  991,  -445, 801,  -352, 641,  27,
     -111, 886,  102,  937,  -438, 773,  -484, 483,  -352, -829,
     831,  571,  -508, -360, 954,  -340, -658, 32,   -917, -869,
     -180, 419,  298,  56,   292,  610,  -798, -213, 638,  370,
     7,    761,  295,  -215, 750,  306,  40,   -650, 279,  -107},
    {-835, -954, 725,  350,  -789, 662,  -858, -862, 476, 985,  398,  1000, 371,
     641,  602,  862,  -774, -565, 64,   628,  -939, 699, -537, 334,  -202, 529,
     968,  504,  584,  -984, -346, -392, 172,  215,  508, 958,  -396, -81,  776,
     -127, -1,   -374, 633,  602,  233,  -862, -982, 369, -210, -134},
    {-639, 332,  405,  273,  904, -715, -94, 390, 559, 437,  -82,  798,  -235,
     823,  -743, -943, 788,  422, -11,  -16, 368, 17,  879,  248,  -196, 966,
     -38,  906,  684,  -863, 320, -332, 214, 18,  669, 202,  -409, 680,  267,
     -766, -414, 999,  405,  121, 739,  336, 634, 602, -460, 120},
    {-487, 374, -206, 663,  785,  -928, 777,  534,  832,  -899,
     108,  741, -484, 415,  124,  219,  -401, -179, 219,  -291,
     -641, 658, -40,  565,  475,  774,  742,  167,  71,   407,
     28,   422, -212, -737, -624, 912,  -620, -837, -371, 994,
     327,  136, -907, 196,  -42,  -16,  -583, -448, -56,  -109},
    {208,  133,  554,  -778, -553, 684,  222, 511,  845,  658, -223, 389, 203,
     -870, -468, 158,  431,  -505, -537, 203, -275, -557, 589, 166,  976, -985,
     -869, 451,  87,   735,  476,  -922, 233, -589, 117,  482, 15,   159, 931,
     913,  -953, -827, -808, -972, 635,  -86, -200, 47,   634, 695},
    {550,  -592, -235, -670, 583,  581, 147, 993,  323,  104, -320, -10,  368,
     -217, -504, -521, -460, -734, 664, 286, 540,  233,  975, 846,  429,  -116,
     -64,  70,   -274, -803, 620,  503, 688, -374, 369,  803, -328, -308, -505,
     -998, -752, -309, 162,  -330, 186, 277, 372,  -923, 77,  925},
    {-137, -216, -685, 423,  952,  -669, 323, -992, 71,   -413, -14,  140, -29,
     724,  -577, -879, -428, -688, 59,   -37, 520,  531,  -975, 52,   705, 565,
     -730, -534, -662, -22,  519,  -392, 491, 27,   672,  324,  -407, 336, -303,
     -502, 854,  901,  975,  333,  434,  -74, 877,  -721, 422,  -332},
    {-625, -23, -359, -673, -671, 370, 212,  183,  818,  -575,
     -531, 655, -184, 884,  -407, 679, -19,  376,  -492, 475,
     -772, 345, -331, -321, 767,  758, -188, -326, 948,  195,
     334,  589, -608, 562,  -537, 333, -357, 905,  446,  -768,
     -664, 8,   471,  738,  -194, 138, 478,  -937, 317,  -470},
    {61,   -65,  -805, -615, -878, -593, -484, -864, 94,   295,
     372,  504,  -526, -892, -398, 287,  926,  817,  903,  -427,
     729,  718,  -134, 908,  925,  792,  -283, -990, -453, -868,
     -315, -439, 117,  841,  708,  -293, -722, -541, -994, 511,
     614,  -952, 180,  576,  -274, 46,   -348, 676,  572,  650},
    {464,  595,  -260, -772, 54,   125,  -24,  -616, 514,  -1000,
     68,   -815, -291, 975,  -461, -89,  68,   -738, -550, 192,
     275,  -45,  850,  323,  -126, -926, -705, -285, 287,  688,
     -568, -851, 31,   -634, 107,  -243, 196,  -443, 178,  325,
     -701, -269, 605,  154,  961,  -213, -358, 733,  570,  282},
    {-543, 321,  138,  397, -871, -550, -739, 105, -732, 88,   -368, 718,  248,
     -255, -317, -663, 343, 910,  -470, 264,  799, 771,  -80,  385,  585,  -212,
     -479, -143, 947,  399, 738,  -307, 518,  266, 895,  900,  -866, -723, -583,
     77,   -949, 62,   210, -868, 743,  -68,  567, -180, -383, -328}};

float right[RANGE] = {
    130,  -410, -859, -216, 163,  -976, 18,   -390, -863, 885, 583,  210,  458,
    -520, -108, -474, -576, 87,   596,  516,  863,  584,  -17, -164, -659, -422,
    -285, -571, 797,  454,  813,  -286, -381, -733, 499,  414, 390,  -741, 430,
    -40,  -272, 555,  655,  -383, -473, 194,  694,  866,  286, 869};