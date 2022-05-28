// chateau gaillard
// this program is based on the following program
// http://www.atariarchives.org/adventure/chapter21.php
// Ben Grimer 04/04/2010

// version 1.4 (see file bughist.txt for bug history
// bug history now maintained on sourceforge project website

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <errno.h>
#ifdef WIN32
#include <windows.h>
#include <conio.h>
#else
#include <termios.h>
#endif

#define TRUE 1
#define FALSE 0

using namespace std;

enum Result_t {OK, LOST, WON};

void initialise(void);
int rollDice(int numSides);
int randomN(int n1);
Result_t roomDescriptions(void);
Result_t showAttributes(void);
void showObjects(void);
void fightRoutine(void);
void showCarrying(void);
void padTo(std::string &str, const size_t num, const char paddingChar = ' ');
int inkeyPlus(void);
void Tokenize(const string& str, vector<string>& token, const string& delimiters = " ");
void convertToUpperCase(char *sPtr);
void logger(const char *msg);
void processCommand(void);
void fnMovement(void);
void fnGetObjects(void);
void fnDropRoutine(void);
void fnUnlockDoors(void);
void fnOpenChest(void);
void fnReadScroll(void);
void fnDrinkPotion(void);
void fnBribeDwarf(void);
void finishGame(void);
void sleepFlush(int _i);
void Xsleep(int _i);
bool validVerb(string str1, string str2);
vector<string> &split(const string &s, char delim, vector<string> &elems);
vector<string> split(const string &s, char delim);
void showHelp();
void fnNotKnownResponse();
void fnOnlyOneWord();
void showObject(int _object);

// variables used in initialise

enum RoomAttributes { NORTH=1, SOUTH=2, EAST=3, WEST=4, UP=5, DOWN=6, OBJECT1=7, MONSTER=8, OBJECT2=9, OBJECT3=10 };  // up to here

int gRoomDATA[44][11] = {{0, 1,1,2,1,1,1,0,0,0,0 }       // :REM 1
                        ,{0, 0,29,3,1,0,0,17,0,0,0 }     // :REM 2
                        ,{0, 0,8,4,2,0,0,0,0,0,0 }       // :REM 3
                        ,{0, 0,9,5,3,0,0,0,0,0,0 }       // :REM 4
                        ,{0, 5,5,5,5,5,5,0,0,0,0 }       // :REM 5
                        ,{0, 0,11,7,30,0,0,0,0,0,0 }     // :REM 6
                        ,{0, 0,0,8,6,0,0,0,0,0,0 }       // :REM 7
                        ,{0, 3,0,0,7,0,0,99,0,0,0 }      // :REM 8
                        ,{0, 4,10,0,0,0,0,0,0,0,0 }      // :REM 9
                        ,{0, 9,0,0,0,0,39,0,0,0,0 }      // :REM 10
                        ,{0, 6,0,0,0,28,0,0,0,0,0 }      // :REM 11
                        ,{0, 0,16,13,0,0,0,0,0,0,0 }     // :REM 12
                        ,{0, 0,0,14,12,0,0,19,0,0,0 }    // :REM 13
                        ,{0, 0,18,0,13,0,0,0,0,0,0 }     // :REM 14
                        ,{0, 0,21,16,0,0,0,0,0,0,0 }     // :REM 15
                        ,{0, 12,20,19,15,0,0,0,1,0,0 }   // :REM 16
                        ,{0, 0,0,18,0,27,0,0,0,0,0 }     // :REM 17
                        ,{0, 14,19,31,17,0,0,0,0,0,0 }   // :REM 18
                        ,{0, 18,23,0,16,0,0,0,0,0,0 }    // :REM 19
                        ,{0, 16,25,0,0,0,0,0,0,0,0 }     // :REM 20
                        ,{0, 15,24,0,32,0,0,0,0,0,0 }    // :REM 21
                        ,{0, 0,26,23,0,0,0,0,0,0,0 }     // :REM 22
                        ,{0, 19,0,0,22,0,0,0,0,0,0 }     // :REM 23
                        ,{0, 21,0,0,0,0,0,0,0,0,0 }      // :REM 24
                        ,{0, 20,25,25,25,25,25,0,0,0,0 } // :REM 25
                        ,{0, 22,0,0,0,0,33,0,0,0,0 }     // :REM 26
                        ,{0, 0,0,0,0,0,17,0,0,0,0 }      // :REM 27  this is the start room
                        ,{0, 0,0,0,0,0,11,0,0,0,0 }      // :REM 28
                        ,{0, 29,29,29,29,29,29,0,0,0,0 } // :REM 29
                        ,{0, 30,30,30,30,30,30,0,0,0,0 } // :REM 30
                        ,{0, 31,31,31,31,31,31,0,0,0,0 } // :REM 31
                        ,{0, 32,32,32,32,32,32,0,0,0,0 } // :REM 32
                        ,{0, 43,42,40,0,26,0,0,0,0,0 }   // :REM 33
                        ,{0, 0,38,35,0,0,0,100,0,0,0 }   // :REM 34
                        ,{0, 0,43,36,34,0,0,0,0,0,0 }    // :REM 35
                        ,{0, 0,40,37,35,0,0,0,0,0,0 }    // :REM 36
                        ,{0, 37,37,37,37,37,37,0,0,0,0 } // :REM 37
                        ,{0, 34,0,43,39,0,0,0,0,0,0 }    // :REM 38
                        ,{0, 0,0,38,0,10,0,0,0,0,0 }     // :REM 39
                        ,{0, 36,41,44,33,0,0,20,0,0,0 }  // :REM 40
                        ,{0, 40,41,41,42,41,41,0,0,0,0 } // :REM 41
                        ,{0, 33,42,41,42,42,42,0,0,0,0 } // :REM 42
                        ,{0, 35,33,0,38,0,0,0,0,0,0 }    // :REM 43
                        ,{0, 0,0,0,40,0,0,18,0,0,0 }     // :REM 44
                      };
  int (*gRmDat)[11] = gRoomDATA;

// treasure

  char gRestart=FALSE;
  int gPack[5];  // PACK, list of what you are carrying (was DIM P(5) in BASIC) */
  int gTally[5]; // seems to record the amount of damage each weapon can inflict ( [T]ally per weapon) (was DIM T(5) in BASIC)

// objects (in BASIC was DIM O$(20) )

enum ObjectsEnum {          AXE=1,           SWORD=2,          DAGGER=3,          MACE=4,                QUARTERSTAFF=5
                           ,MORNING_STAR=6, FALCHION=7,       CRYSTALRALL=8,     AMULET=9,              EBONY_RING=10
                           ,GEM=11,         MYSTIC_SCROLL=12, HEALING_POTION=13, DILITHIUM_CRYSTALS=14, COPPER_PIECES=15
                           ,DIADEM=16,      SILVER_KEY=17,    GOLDEN_KEY=18,     CHEST_OF_STONE=19,     CHEST_OF_IRON=20
                           ,LOCKED_DOOR_1=99, LOCKED_DOOR_2=100};

  string gObjects[21] = {"","AXE",         "SWORD",         "DAGGER",        "MACE",              "QUARTERSTAFF"
                           ,"MORNING STAR","FALCHION",      "CRYSTALRALL",   "AMULET",            "EBONY RING"
                           ,"GEMS",        "MYSTIC SCROLL", "HEALING POTION","DILITHIUM CRYSTALS","COPPER PIECES"
                           ,"DIADEM",      "SILVER KEY",    "GOLDEN KEY",    "CHEST OF STONE",    "CHEST OF IRON"  };

  int gV[20] = { 0,0,0,0,0,0,0,99,247,166,462,195,231,162,27,141,0,0,0,0 };     /* this seems to be the object value */

// monsters (basic DIM M$(20) )

enum MonsterEnum   { NO_MONSTER=0
                   , DWARF=1, MONOCEROS=2, PARADRUS=3, VAMPYRE=4, WRNACH=5
                   , GIOLLA_DACKER=6, KRAKEN=7, FENRIS_WOLF=8, CALOPUS=9, BASILISK=10
                   , GRIMOIRE=11, FLYING_BUFFALO=12, BERSERKOID=13, WYRM=14, CROWTHERWOOD=15
                   ,GYGAX=16, RAGNAROK=17, FOMORINE=18, HAFGYGR=19, GRENDEL=20 };

  string gMonsters[21] = {"", "DWARF",        "MONOCEROS",      "PARADRUS"   , "VAMPYRE", "WRNACH"
                            , "GIOLLA DACKER","KRAKEN"   ,      "FENRIS WOLF", "CALOPUS", "BASILISK"
                            , "GRIMOIRE",     "FLYING BUFFALO", "BERSERKOID",  "WYRM",    "CROWTHERWOOD"
                            , "GYGAX",        "RAGNAROK",       "FOMORINE",    "HAFGYGR", "GRENDEL"};

// rooms

  string gRooms[44] = {
     /*1*/"You are out on the battlements of the chateau. There is only one way back"
    ,/*2*/"This is an eerie room, where once magicians convorted with evil sprites and werebeasts...\n"
           "Exits lead in three directions\nAn evil smell comes from the south"
    ,/*3*/"An old straw mattress lies in one corner...it has been ripped apart to find any treasure which was hidden in it.\n"
           "Light comes fitfully from a window to the north, and around the doors to south, east and west."
    ,/*4*/"This wooden-panelled room makes you feel damp and uncomfortable\tA mouse scampers across the floor\t\n"
           "A bat flits across the ceiling\tThere are three doors leading from this room, one made of iron.\n"
           "Your sixth sense warns you to choose carefully..."
    ,/*5*/"You ignore your intuition...\nA Spell of Living Stone, primed to trap the first intruder has been set on you..."
          "with your last seconds of life you have time only to feel profound regret..."
    ,/*6*/"You are in an L-shaped room\nHeavy parchment lines the walls\nYou can see through an archway to the east..."
          "but that is not the only exit from this room"
    ,/*7*/"There is an archway to the west, leading to an L-shaped room\na door leads in the opposite direction\n"
    ,/*8*/"This must be the Chateau's main kitchen but any food left here has long rotted away...\n\n"
          "A door leads to the north, and there is one to the west\n"
    ,/*9*/"You find yourself in a small, room...which makes you feel claustrophobic...\n\n"
          "There is a picture of a black dragon painted on the north wall, above the door...\n"
    ,/*10*/"A stairwell ends in this room, which is more of a landing than a real room.\n"
           "The door to the north is made of iron, which has rusted over the centuries...\n"
    ,/*11*/"There is a stone archway to the north, You are in a very long room.\n\n"
           "Fresh air blows down some stairs and rich red drapes cover the walls...You can see doors to the south and east"
    ,/*12*/"You have entered a room filled with swirling, choking smoke.\n\n"
           "you must leave quickly to remain healthy enough to continue your chosen quest..."
    ,/*13*/"There is a mirror in the corner you glance at it, and feel suddenly very ill.\n\n"
           "You realise the looking-glass has been enfused with a Spell of Charisma Reduction...oh dear...\n"
    ,/*14*/"This room is richly finished, with a white marble floor. Strange footprints lead to the two doors from this room...\n"
           "Dare you follow them?"
    ,/*15*/"You are in a long, long hallway, lined on each side with rich, red drapes...\n\n"
           "They are parted halfway down the east wall where there is a door"
    ,/*16*/"Someone has spent a long time painting this room a bright yellow...\n\n"
           "You remember reading that yellow Is the Ancient Oracle's Color of Warning..."
    ,/*17*/"As you stumble down the ladder you fall into the room. The ladder crashes down behind you..."
           "there is now no way back...\n\nA small door leads east from this very cramped room..."
    ,/*18*/"You find yourself in a Hall of Mirrors...and see yourself reflected a hundred times or more..."
           "Through the bright glare you can make out doors in all directions..."
           "You notice the mirrors around the east door are heavily tarnished..."
    ,/*19*/"You find yourself in a long corridor\n\tYour footsteps echo as you walk\n"
    ,/*20*/"You feel as you've been wandering around this chateau for ever...\nand you begin to despair of ever escaping...\n"
           "Still, you can't get too depressed, but must struggle on. Looking around, you see you are in a room which"
           " has a heavy timbered ceiling, and white roughly-finished walls...\n\nThere are two doors...\n"
    ,/*21*/"You are in a small alcove. You look around...but can see nothing in gloom..."
           "perhaps if you wait a while your eyes will adjust to the murky dark of this alcove...\n"
    ,/*22*/"A dried-up fountain stands in the center of this courtyard, which once held beautiful flowers...but have long-since died..."
    ,/*23*/"The scent of dying flowers fills this brightly-lit room...\n\nThere are two exits from it.."
    ,/*24*/"This is a round stone cavern off the side of the alcove to your north..."
    ,/*25*/"You are in an enormous circular room, which looks as if it was used as a games room. "
           "Rubble covers the floor, partially blocking the only exit..."
    ,/*26*/"Through the dim mustiness of this small potting shed you can see a stairwell..."
    ,/*27*/"You begin this Adventure in a small wood outside the Chateau...\t\n\n"
           "While out walking one day, you come across a small, ramshackle shed in the woods.\nEntering it, you see a hole in one corner..."
           "an old ladder leads down from the hole..."
    ,/*28*/"How wonderful! Fresh air, sunlight...\n\t\nBirds are singing...you are free at last....\n\n"
    ,/*29*/"The smell came from bodies rotting in huge traps...\t\nOne springs shut on you, trapping you forever\n"
    ,/*30*/"You fall into a pit of flames...\n"
    ,/*31*/"Aaaaahhh...you have fallen into\t\na pool of acid...now you know - too late - why the mirrors were so badly tarnished\n"
    ,/*32*/"It's too bad you chose that exit from the alcove...\t\nA giant Funnel-Web Spider leaps on you..."
           "and before you can react bites you on the neck...you have 10 seconds to live...\n"
    ,/*33*/"A stairwell leads into this room, a poor and common hovel with many doors and exits..."
    ,/*34*/"It is hard to see in this room, and you slip slightly on the uneven, rocky floor..."
    ,/*35*/"Horrors! This room was once the torture chamber of the Chateau..\n\n"
           "Skeletons lie on the floor, still with chains around the bones..."
    ,/*36*/"Another room with very unpleasant memories...\t\n\nThis foul hole was used as the Chateau dungeon....\n"
    ,/*37*/"Oh no, this is a Gargoyle's lair...\t\nIt has been held prisoner here for three hundred years...\t\n\n"
           "In his frenzy he thrashes out at you...\t    and...\t\n...breaks your neck!!\n"
    ,/*38*/"This was the Lower Dancing Hall...\n"
           "With doors to the north, the east and to the west, you would seem to be able to flee any danger...\n"
    ,/*39*/"This is a dingy pit at the foot of some extremely dubious-looking stairs. A door leads to the east..."
    ,/*40*/"Doors open to each compass point from the Trophy Room of the Chateau...\n\n"
           "The heads of strange creatures shot by the ancestral owners are mounted high up on each wall..."
    ,/*41*/"You have stumbled on a secret room...\t\n\nDown here, eons ago, the ancient Necromancers of Thorin plied their evil craft..."
           "and the remnant of their spells hangs heavy on the air...\n"
    ,/*42*/"Cobwebs brush your face as you make your way through the gloom of this room of shadows..."
    ,/*43*/"This gloomy passage lies at the intersection of three rooms..."
    ,/*44*/"You are in the rear turret room, below the extreme western wall of the ancient chateau..."
     };
     
  // character attributes  
  int gST;  // strength
  int gCH;  // charisma
  int gDE;  // dexterity
  int gIT;  // intelligence
  int gWI;  // wisdom
  int gCO;  // constitution

  // monster attributes (as above)
  int gS1;
  int gH1;    // charisma is H as other dup. with CO
  int gD1;
  int gI1;
  int gW1;
  int gC1;

  bool gKnownWord = false;     // (KW in BASIC version)  1=Understood

  int gCash=0;
  int giRoom=27;      // STARTING ROOM is 27, current room Nbr
  float gQuit=1;      // END OF GAME FLAG (BASIC QU)
  int gMonKill=0;          // MONSTERS KILLED (BASIC MK)
  int gBOX=0;         // CHEST FLAG
#ifdef WIN32
  float gScore=0;
#else
  int gScore=0; // SCORE
#endif
  int gCarryingObject=0;      // indicates if YOU are carrying something
  char *gCurMonster;    // monster in the CURRENT room (BASIC G$)
//  string gC$;   // first word user types
  string gObject1$;   // 1st object in current room (BASIC D$)
  string gObject2$;   // 2nd object in current room (BASIC E$)
  string gObject3$;   // 3rd object in current room (BASIC F$)
  int giDropped;      // (BASIC D)
  char gInput[256];   // what the user types in (BASIC A$)
//  string gB$;   // left$3 of gInput (see function process commands)
  vector<string> token;   // holds input string as array of words

  int gMT=0;       // monster tally
  int gHT=0;       // Human tally
  int gFearFactor; // Danger Level (Fear Factor ?)
//  int gM;        // size of command entered
  

main()
{
  initialise();
  while (TRUE)   // 40  (main loop)
  {
    sleepFlush(1);

    int result = roomDescriptions();   // line 70 gosub 3300
    if (LOST == result) break;
    else if (WON == result) {
      printf("CONGRATULATIONS! You have completed THE ADVENTURE\n");   // 2560
      gScore=100;
      break;
    }

    int *lRmDat = gRmDat[giRoom-1];    // current room data

    if (lRmDat[OBJECT1] != 0 || lRmDat[OBJECT2] != 0 || lRmDat[OBJECT3] != 0) showObjects();   // 80 (gosub 6600)

    if (lRmDat[OBJECT1] >= LOCKED_DOOR_1) printf("One of the doors is locked preventing you from exploring further\n");

    if (lRmDat[MONSTER] != NO_MONSTER) {
      const char *lMonster = gMonsters[lRmDat[MONSTER]].c_str();

      printf("\t\tLOOK OUT!\nTHERE IS A %s HERE!", lMonster );

      if ( rollDice(10) > 7 && lRmDat[MONSTER] != DWARF ) {      // if there's a monster then 30% chance it attacks
         printf("THE %s ATTACKS!\n", lMonster );
         gKnownWord = true;
         fightRoutine();   // gosub 1400
         continue;     // go the the top of the main loop (goto 40)
      }
    } 

    if (gST<1) gST=0; else if (rollDice(6)>5) gST--;  // one in six chance of each character attribute reducing
    if (gCH<1) gCH=0; else if (rollDice(6)>5) gCH--;
    if (gDE<1) gDE=0; else if (rollDice(6)>5) gDE--;
    if (gIT<1) gIT=0; else if (rollDice(6)>5) gIT--;
    if (gWI<1) gWI=0; else if (rollDice(6)>5) gWI--;
    if (gCO<1) gCO=0; else if (rollDice(6)>5) gCO--;

    if (rollDice(6)>5 && giRoom==16 && lRmDat[MONSTER]==DWARF) {
      printf("\nYou hear a whispered voice warning you:\n\n'You must do something about the dwarf'");
    }

    if (LOST == showAttributes() ) break;  // if any of your attributes hit zero then you lose  (180-220)

    showCarrying();   // 230-330

    gKnownWord = false;  // known word. false = not understood, true = understood (was 0 and 1 in BASIC version)
    Xsleep(1);

    bool continueInput=TRUE;
    while (continueInput) {                     // 390
      
      cout << "\nWhat do you want to do ? ";    // 390
      cin.getline(gInput, sizeof(gInput) );

      if (strlen(gInput)==0) continue;

      convertToUpperCase(gInput);
      if (token.size() > 0) token.clear();
      split(gInput, ' ', token);

      string first3$ = token[0].substr(0,3);
      switch (token.size()) {
      case 0:
        continue;
      case 1:
        if ("HEL" == first3$ ) {   // 450
          showHelp();
          gRestart = TRUE;                           // goto 40
          break;
        } else if ("QUI" == first3$ ) {              // 460
          gQuit = 4;
          break;                                     // goto 2530
        } else {  // it must be an invalid commant   // 500
          fnOnlyOneWord();
          continue;                                  // goto 390
        }
        break;

      case 2:
        processCommand();
        continueInput=FALSE;
        break;

      default:
        cout << "'" << gInput << "' IS MORE THAN 2 WORDS\n";
        break;
      }

      if (4==gQuit || 3==gQuit /* not able to bribe dwarf */) break;
      if (gRestart) break;   // exit prompt loop

      if (!gKnownWord) fnNotKnownResponse();

    } // end while (continue input)

    if (4==gQuit  || 3==gQuit) break;
    if (gRestart) continue;   // goto top of main loop
  } // end while (main loop)

  finishGame();    // lines 2590-2630

} // end main


//------------------------------------------------------
void fnOnlyOneWord()
{
  if (rollDice(6) > 3) {   // 500
    cout << "BY ITSELF, " << token[0] << " CAN'T BE ACTED ON\n";    // 510
  } else {
    cout << token[0] << " IS JUST ONE WORD I NEED TWO\n";  // 520
  }
}

//------------------------------------------------------
void fnNotKnownResponse()
{

  static string lResponses[] = {"IT WOULD NOT BE WISE TO ",
                          "ONLY A FOOL WOULD TRY TO ",
                          "I DON'T UNDERSTAND "  };
  static int lSize = sizeof(lResponses)/sizeof(string);
  int lrand1 = rollDice(lSize)-1;

  if (lrand1<lSize)
    cout << lResponses[lrand1] << gInput << "\n";
  else
    cout << "This should never happen!\n";

  Xsleep(2);
}

//------------------------------------------------------
void showHelp()
{
  static string lHelpText[] = {/* "NO HELP FOR MORTALS IN THIS GAME! ...although reading and drinking may help...\n" */
          "The computer is programmed to recognize and act on two-word sentences.\n"
          "The two words must be a verb first, followed by a noun.\n"
          "The computer, for example, can understand the instruction GO NORTH\n"
          "(or even RUN NORTH, MOVE NORTH, CLIMB NORTH, or WALK NORTH).\n\n"
          "You'll find it is far more satisfying to \"TALK\" to your computer in this way\n"
          "than it is to communicate simply by touching a key.\n\n",

          "Some of the pleasure of Adventure programs comes from trying to work out which\n"
          "words it will understand, and which it will reject.\n",

          "All the objects you encounter within the chateau can be manipulated-at least\n"
          "to the extent of being picked up or put down.\n"
          "Some objects (such as the MYSTIC SCROLL) can be read and others can be drunk.\n\n",

          "This game is based on: http://www.atariarchives.org/adventure/chapter21.php\n",
          "HIT ANY KEY TO CONTINUE..\n" };
  static int lSize = sizeof(lHelpText)/sizeof(string);

  cout << lSize;
  for (int i=0; i<lSize; i++) {
    cout << lHelpText[i];
  }

  fflush(stdout);
  inkeyPlus();
  Xsleep(2);
}


//------------------------------------------------------
void finishGame(void)
{
  gScore = (gScore + 20*gCash + 47*gMonKill + gST + 2*gCH + 3*gDE + 4 + gIT + 5*gWI + 6*gCO)/gQuit;
  if (gMonKill>0) {
    cout << "You killed " << gMonKill << " Monsters\n";
    if (gCash>0) cout << "and\n";
  }
  cout << "\nYOU FOUND $" << gCash << " WORTH OF TREASURE\n";
  cout << "Your score for this Adventure is " << gScore;
  cout << "\n\nThe End.\n\n";
  cout << "PRESS ANY KEY TO EXIT\n";

  fflush(stdout);
  inkeyPlus();

}

//-----------------------------------------------
bool validVerb(string str1, string str2)
{
  return(-1 != str1.find(str2) );
}

//-----------------------------------------------
void processCommand(void)
{
    string VALIDFIGHTVERBS = "STA|KIL|FIG|KIC|PUN|SLA|ATT";  // stab, kill, fight, kick, punch, slay, attack
    string VALIDMOVEVERBS  = "GO |MOV|CLI|RUN|WAL";          // go, move, climb, run, walk
    string VALIDTAKEVERBS  = "TAK|GET|STE|LIF";              // take, get, steal, lift
    string VALIDDROPVERBS  = "DRO|PUT|THR|BRE";              // drop, put, throw, break ?

    string prefix1 = token[0].substr(0,3);                // 1st 3 chars of first input word

    if (giRoom==8 || giRoom==34) {

      if (validVerb(VALIDFIGHTVERBS, prefix1) ) {
        gKnownWord = true;
        fightRoutine();                                    // GOSUB 1400
      }

      if ( gRmDat[giRoom-1][OBJECT1]>= LOCKED_DOOR_1 && prefix1=="UNL" ) {
        printf("** The doors are locked **");
        gRestart = TRUE;                                  // goto 40
      }
    } else {                                              // 560

      if ( validVerb(VALIDFIGHTVERBS, prefix1)) {
        gKnownWord = true;
        fightRoutine();                                 // GOSUB 1400
      } else if ( validVerb(VALIDMOVEVERBS, prefix1)) {
        gKnownWord = true;
        fnMovement();                                   // GOSUB 740
      } else if ( validVerb(VALIDTAKEVERBS, prefix1)) {
        gKnownWord = true;
        fnGetObjects();                                 // GOSUB 950
      } else if ( validVerb(VALIDDROPVERBS, prefix1)) {
        gKnownWord = true;
        fnDropRoutine();                                // GOSUB 1160
      } else if (prefix1 == "UNL") {
        gKnownWord = true;
        fnUnlockDoors();                                // GOSUB 2360 
      } else if (prefix1 == "OPE") {
        gKnownWord = true;
        fnOpenChest();                                  // GOSUB 2660
      } else if (prefix1 == "REA") {
        gKnownWord = true;
        fnReadScroll();                                 // GOSUB 2750
      } else if ( validVerb("DRI|SWA", prefix1)) {
        gKnownWord = true;
        fnDrinkPotion();                                // GOSUB 2870
      } else if ( validVerb("BRI|PAY", prefix1)) {
        gKnownWord = true;
        fnBribeDwarf();                                 // GOSUB 3000
      }
   }
}

//---------------------------------------------------
// right pads to string to total length num
void padTo(std::string &str, const size_t num, const char paddingChar /* = ' '*/)
{
    if(num > str.size()) {
        printf("size is %i num is %i\n", str.size(), num );
        str.append(num - str.size(), paddingChar);
    }
}

//---------------------------------------------------
Result_t showAttributes(void)
{
    printf("\n\nYour attributes are:\n");
    printf("    Strength  - %.2i  Charisma     - %.2i\n", gST, gCH);
    printf("    Dexterity - %.2i  Intelligence - %.2i\n", gDE, gIT);
    printf("    Wisdom    - %.2i  Constitution - %.2i\n", gWI, gCO);
    if (gST*gCH*gDE*gIT*gWI*gCO==0) {
      printf("You are exhausted...\nso this adventure must end");
      gQuit=2;
      return LOST;  // aka goto 2590
    }
    return OK;
}


//---------------------------------------------------
void fightRoutine(void)    // 1400
{
  int lM = gRmDat[giRoom-1][MONSTER];    // lM = Monster in current room
  if ( lM==1 ) {   // 1410
    printf("The dwarf refuses to fight and his magic protects him\n");
    return;
  }

  if (lM != 0) {
    gCurMonster = (char *) gMonsters[lM].c_str();                         // 1470
    gS1 = rollDice(6) + rollDice(6) + rollDice(6) + 3;
    gH1 = rollDice(6) + rollDice(6) + rollDice(6) + 3;
    gD1 = rollDice(6) + rollDice(6) + rollDice(6) + 3;
    gI1 = rollDice(6) + rollDice(6) + rollDice(6) + 3;
    gW1 = rollDice(6) + rollDice(6) + rollDice(6) + 3;
    gC1 = rollDice(6) + rollDice(6) + rollDice(6) + 3;
    printf("------------------------------------------\n");
    printf("YOUR OPPONENT IS A %s\n", gCurMonster );
    gMT = 0;
    gHT = 0; // REM MONSTER TALLY, HUMAN TALLY
    gFearFactor = gS1 * rollDice(6);  // gS1 = Monster Strength
    printf("\n---------------------------------------\n");
    printf("THE %s'S DANGER LEVEL IS %i\n", gCurMonster, gFearFactor);    // line 1590

    // this is setting the Tally for each weapon in the pack which, coincidentally, has the same strength as the number
    // used to identify the weapon (i.e. falchion (most powerful weapon), axe (weakest)
    sleepFlush(5);
    for (int j1=0; j1<5; j1++) {
      gTally[j1]=0;
      if ( gPack[j1]==1 ) { printf("YOUR AXE COULD BE HANDY\n"); gTally[j1]=1; }
      if ( gPack[j1]==2 ) { printf("YOUR SKILL WITH THE SWORD MAY STAND YOU IN GOOD STEAD\n"); gTally[j1]=2; }
      if ( gPack[j1]==3 ) { printf("YOUR DAGGER IS USEFUL AGAINST %sS\n", gCurMonster ); gTally[j1]=3; }
      if ( gPack[j1]==4 ) { printf("THE MACE WILL MAKE SHORT WORK OF IT"); gTally[j1]=4; }
      if ( gPack[j1]==5 ) { printf("YOUR QUARTERSTAFF WILL GIVE IT NO QUARTER...\n"); gTally[j1]=5; }
      if ( gPack[j1]==6 ) { printf("SWINGING YOUR MORNING STAR MAY INFLICT HEAVY WOUNDS ON THE %s\n", gCurMonster ); gTally[j1]=6; }
      if ( gPack[j1]==7 ) { printf("A FALCHION IS A USEFUL WEAPON\n"); gTally[j1]=7; }
    }   // line 1700

    // the gTally at this point holds the tally for each item in the pack.
    // based on the above, any item that is NOT a weapon will have a tally of 0.
    // therefore counting the number of entries with tally > 0 is effectively the same as counting the number of weapons

    int iFlag=0;                                      // line 1710
    for (int j1=0; j1<5; j1++) {
      if ( gTally[j1] != 0 ) iFlag++;
    }

    if (0 == iFlag) {   // line 1750
      printf("YOU MUST FIGHT THE %s WITH YOUR BARE HANDS\n", gCurMonster );  // GOTO 1910
    } else if (!(iFlag > 1)) {  // 1760

      for (int j1=0; j1<5; j1++) {
        if ( gTally[j1] != 0 ) iFlag = gTally[j1];
      }
      printf("YOU MUST FIGHT WITH YOUR %s\n", gObjects[iFlag].c_str() );    // 1800
      gFearFactor == gFearFactor*2/iFlag;

    } else {                                              // line 1830
      printf("CHOOSE YOUR WEAPON:\n");
      for (int j1=0; j1<5; j1++) {
        if ( gPack[j1] != 0 ) printf("%i -%s\n", j1, gObjects[gPack[j1]].c_str() );
      }
      int j2;
      int i1;
      while (TRUE /* no valid weapon entered */) {  // 1870
        printf("Enter the number to choose :");   // note: no \n as prompt (input)
        j2 = inkeyPlus();
        printf("%c\n", j2);  // display character typed
        if (j2 < '0' || j2 > '4') {
          printf("You must enter a number between 0 and 4!\n");
          continue;
        }
        i1 = j2 - '0';      // potential bug if non number entered
        if (gPack[i1]!=0)                 // BASIC 1880
          break;
        else
          printf("YOU DO NOT HAVE THE %s\n", gObjects[gPack[i1]].c_str() );
      }

      printf("RIGHT, SO YOU CHOOSE TO FIGHT WITH THE %s\n", gObjects[gPack[i1]].c_str() );
      gFearFactor = gFearFactor*2/j2;  // 1900
    }

    sleepFlush(2);   // line 1910

    printf("THE %s HAS THE FOLLOWING ATTRIBUTES:\n", gCurMonster );
    printf("1 - Strength  %.2i  2 - Charisma     %.2i\n", gS1, gH1);
    printf("3 - Dexterity %.2i  4 - Intelligence %.2i\n", gD1, gI1);
    printf("5 - Wisdom    %.2i  6 - Constitution %.2i\n", gW1, gC1);
    printf("\nYOUR ATTRIBUTES ARE:\n");
    printf("1 - Strength  %.2i  2 - Charisma     %.2i\n", gST, gCH);
    printf("3 - Dexterity %.2i  4 - Intelligence %.2i\n", gDE, gIT);
    printf("5 - Wisdom    %.2i  6 - Constitution %.2i\n", gWI, gCO);
    printf("\nWhich attributes will you fight with (2)");   // note prompt

    int gZ=0, gQ=0;
    char input[256];
    while (TRUE ) {  // no valid attributes entered, 2010

//      printf(":");
      cout << ":";
      cin.getline (input, sizeof(input) );
      sscanf (input,"%d,%d", &gZ, &gQ);
      if ( gZ<1 || gQ<1 || gZ>6 || gQ>6 || gZ==gQ ) {
        printf("DO NOT FOOL AROUND WHEN A %s IS IN THE ROOM WITH YOU!\n(type numbers 1-6 separated by a comma)\n", gCurMonster );    // 2020
        continue;   // :GOTO 2010
      } else break;
    }

    if ( gZ==1 || gQ==1) { gMT = gMT + gS1; gHT = gHT + gST; }   // 2030
    if ( gZ==2 || gQ==2) { gMT = gMT + gH1; gHT = gHT + gCH; }
    if ( gZ==3 || gQ==3) { gMT = gMT + gD1; gHT = gHT + gDE; }
    if ( gZ==4 || gQ==4) { gMT = gMT + gI1; gHT = gHT + gIT; }
    if ( gZ==5 || gQ==5) { gMT = gMT + gW1; gHT = gHT + gWI; }
    if ( gZ==6 || gQ==6) { gMT = gMT + gC1; gHT = gHT + gCO; }   // 2080

    if ( gHT==gMT )
      printf("          You are evenly matched\n");   // GOTO 2130
    else {
      printf("IT LOOKS LIKE THE ODDS\nARE IN FAVOR OF ");
      if (gHT > gMT)
        printf("YOU\n");
      else
        printf("THE %s\n", gCurMonster );
    }

    int lK = rollDice(7)-1;   // 2130
    sleepFlush(5);   // wait for the dice to roll

    printf("THE %s - %i\n", gCurMonster, gMT);
    printf("YOU - %i\n", gHT);

    switch (lK) {
    case 0:
      printf("You struck a splendid blow!\n");       // 2170
      gMT = gMT-1;
      break;
    case 1:
      printf("THE %s STRIKES OUT\n", gCurMonster );
      gHT=gHT-3;
      gST=gST-1;
      gCH=gCH-1;
      break;
    case 2:
      printf("YOU DRAW THE %s'S BLOOD\n", gCurMonster );
      gMT = gMT-1;
      break;
    case 3:
      printf("You are wounded!!\n");
      // gHT=gHT-INT(RND(1)*3)-1;   todo
      gDE=gDE-1;
      break;
    case 4:
      printf("THE %s IS TIRING\n", gCurMonster );
      gMT = gMT-1;
      break;
    case 5:
      printf("You are bleeding...\n");
      gHT=gHT-2;
      gWI=gWI-1;
      gCO=gCO-1;
      break;
    case 6:
      printf("YOU WOUND THE %s\n", gCurMonster );       // 2230
      gMT = gMT-1;
      break;
    default:
      printf("THIS SHOULD NEVER HAPPEN !!!!\n");
      break;
    }
    sleepFlush(0);

    if ( rollDice(4) > 1 && gHT > 0 && gMT > 0 ) Xsleep(5);   // 2240

    if ( gHT > gMT ) {
      printf("YOU HAVE SLAIN THE %s\n", gCurMonster );
      gMonKill=gMonKill+1;
      gRmDat[giRoom-1][MONSTER] = 0;  // goto 2330 remove monster from room (then goto 2330, ie. return)

    } else {
      printf("THE %s GOT THE BETTER OF\nYOU THAT TIME...\n", gCurMonster );
      if (gZ==1 || gQ==1 ) gST=4*gST/5;    // 2270
      if (gZ==2 || gQ==2 ) gCH=3*gCH/4;
      if (gZ==3 || gQ==3 ) gDE=6*gDE/7;      // todo  work out what the int stuff was doing
      if (gZ==4 || gQ==4 ) gIT=2*gIT/3;
      if (gZ==5 || gQ==5 ) gWI=5*gWI/6;
      if (gZ==6 || gQ==6 ) gCO=gCO/2;       // 2320

      gRmDat[giRoom-1][MONSTER] = 0;  // the monster seems to disappear regardless, see above 
    }

  } else if ( rollDice(6) < 4 )
//    printf("There is nothing to fight here\n");    // 1440
    cout << "There is nothing to fight here\n";    // 1440
  else
//    printf("You can't fight empty air!\n");        // 1450
    cout << "You can't fight empty air!\n";        // 1450

  return;   // 2330
}   // 1460


//---------------------------------------------------
void showCarrying(void)
{
    gCarryingObject=FALSE;
    for (int j=0; j<5; j++) {
      if (gPack[j]!=0) { gCarryingObject = TRUE; break; }
    }
    if (gCarryingObject) {  // if you are carrying something
      gCash = 0;
      printf("\nYou are carrying:  ");
      for (int j=0; j<5; j++) {
        if (gPack[j]!=0) {
          printf("%s  ", gObjects[gPack[j]].c_str() );
          gCash += gV[gPack[j]];
        }
      }
      printf("\n");
      if (gCash>0) printf("Total value - $%i\n", gCash);
    }
    return;
}


//---------------------------------------------------
void showObjects(void)
{
  int *lRmDat = gRmDat[giRoom-1];

  printf("\n");
  if (lRmDat[OBJECT1] >= LOCKED_DOOR_1 && lRmDat[OBJECT2]==0 && lRmDat[OBJECT3]==0) return;   // 6680

  printf("you can see: ");
  showObject(lRmDat[OBJECT1]);
  showObject(lRmDat[OBJECT2]);  // 6720
  showObject(lRmDat[OBJECT3]);  // 6740
/*
  if (lRmDat[OBJECT1]<LOCKED_DOOR_1)
    if (lRmDat[OBJECT1]!=0) printf("%s  ", gObjects[lRmDat[OBJECT1]].c_str() );

  if (lRmDat[OBJECT2]<LOCKED_DOOR_1)  // 6720
    if (lRmDat[OBJECT2]!=0) printf("%s  ", gObjects[lRmDat[OBJECT2]].c_str() );

  if (lRmDat[OBJECT3]<LOCKED_DOOR_1)  // 6740
    if (lRmDat[OBJECT3]!=0) printf("%s  ", gObjects[lRmDat[OBJECT3]].c_str() );
*/
  printf("\n");
  sleepFlush(2);
  return;
}

void showObject(int _object)
{
  if (_object<LOCKED_DOOR_1 && _object!=0)
    cout << gObjects[_object] << "  ";
}


//---------------------------------------------------
Result_t roomDescriptions(void)
{
  char *lRoom$ = (char *)gRooms[giRoom-1].c_str();
  vector<string> tokenTmp;   // holds input string as array of words
  switch (giRoom) {
  case 4:
    split(lRoom$, '\t', tokenTmp );
    cout << tokenTmp[0] << "\n";
    cout << ((rollDice(2) > 1) ? tokenTmp[1] : tokenTmp[2]) << "\n";
    cout << tokenTmp[3] << "\n";

    break;
  case 5:
    cout << lRoom$ << "\n";
    gScore = 50;
    return LOST;     // you lost, exit and show score
    break;
  case 28:
  case 29:
  case 31:
  case 32:
    split(lRoom$, '\t', tokenTmp );
    cout << tokenTmp[0] << "\n";
    sleepFlush(5);
    cout << tokenTmp[1] << "\n";
    if (28==giRoom) { return WON; }
    else if (29==giRoom) { gQuit = 3.5; }
    else if (31==giRoom) { gQuit = 3; gScore=20; }
    else if (32==giRoom) {
      for (int i=10; i>0; i--) {
        for (int j=0; j<i; j++) printf(".");
        cout << i << "\n";
        sleepFlush(1);
      }
      cout << "\n";
      gQuit = 5;
      gScore=3;
    }
    return LOST;     // you lost, exit and show score
    break;
  case 13:
    cout << lRoom$ << "\n";
    gCH--;  // charisma goes down by 1
    break;
  case 19:
  case 27:
  case 36:
  case 41:
    split(lRoom$, '\t', tokenTmp );
    cout << tokenTmp[0] << "\n";
    sleepFlush(5);
    cout << tokenTmp[1] << "\n";
    break;
  case 30:
    do {
      cout << lRoom$;
      sleepFlush(1);
    } while (rollDice(10) > 7);
    gScore = 10;
    gQuit = 3.4;
    return LOST;     // you lost, exit and show score
    break;
  case 20:
  case 38:
    cout << lRoom$ << "\n";
    sleepFlush(2);
    break;
  case 37:
    split(lRoom$, '\t', tokenTmp );
    for (int i=0; i<tokenTmp.size(); i++) {
      cout << tokenTmp[i] << "\n";
      sleepFlush(5);
    }
    gScore=0;
    gQuit=3;
    return LOST;     // you lost, exit and show score
    break;
  case 21:
    cout << lRoom$ << "\n";
    sleepFlush(5);
    break;
  default:
    cout << lRoom$ << "\n";
    break;
  }
  return OK;
}


//---------------------------------------------------
void initialise(void)
{
//  gN = 0;
  cout << "\n\nChateau Gaillard - version 1.4.4";
#ifdef WIN32
  cout << " (Windows)\n";
#else
  cout << " (Linux/OSX)\n";
#endif
  cout << "\nPRESS ANY KEY TO START THE ADVENTURE\n";
  fflush(stdout);
  inkeyPlus();

//6870 CLS
// temp  system("clear");

  cout << "\nPlease stand by...";
  sleepFlush(2);

  gST = rollDice(6) + rollDice(6) + rollDice(6) + 3;
  gCH = rollDice(6) + rollDice(6) + rollDice(6) + 3;
  gDE = rollDice(6) + rollDice(6) + rollDice(6) + 3;
  gIT = rollDice(6) + rollDice(6) + rollDice(6) + 3;
  gWI = rollDice(6) + rollDice(6) + rollDice(6) + 3;
  gCO = rollDice(6) + rollDice(6) + rollDice(6) + 3;

  // set up certain additional objects

  gRmDat[8-1] [OBJECT1] = LOCKED_DOOR_1;      // LOCKED DOOR i * note arrays in C start with 0 *
  gRmDat[34-1][OBJECT1] = LOCKED_DOOR_2;
  gRmDat[40-1][OBJECT1] = CHEST_OF_IRON;
  gRmDat[13-1][OBJECT1] = CHEST_OF_STONE;
  gRmDat[16-1][MONSTER] = DWARF;

  int z1;
  for (int q1=0; q1 < 16; q1++) {
    do
    {
      z1 = randomN(44);
    } while ( z1==5-1 || z1==17-1 || z1==27-1 || z1==29-1 || z1==30-1
           || z1==31-1 || z1==32-1 || z1==37-1 || gRmDat[z1][OBJECT1] != 0 );

    gRmDat[z1][OBJECT1] = q1;
  }

  cout << "\n   Just a few moments more...\n";
  sleepFlush(2);

  // distribute monsters
  for (int j1=1; j1 < 20; j1++) {   // note 1st col. is skipped above
    do {
      z1 = randomN(44);

    } while (z1==5-1 || z1==17-1 || z1==27-1 || z1==29-1 || z1==30-1
         || z1==31-1 || z1==32-1 || z1==37-1 || gRmDat[z1][MONSTER] != 0);

    gRmDat[z1][MONSTER] = j1;
  }

}   // this is the end of initialise()


//------------------------------------------------------
// generates a random number between 0 and n-1
int randomN(int n1)
{
  return rand() % n1;
}


//------------------------------------------------------
// returns random number from 1 to 6
int rollDice(int numSides)
{
  static char init=FALSE;

  if (!init) {
    init=TRUE;
    /* initialize random seed: */
    srand ( time(NULL) );
  }

  /* generate secret number: */
  return rand() % numSides + 1;
}


//------------------------------------------------------
// this function does the equivalent of atari basic's inkey$ function
// this function pushes back the char if it is not right,up,left or down arrow

#ifdef WIN32
int inkeyPlus(void) {
//  getchar();

  while( !_kbhit() ) {    // Display full stop until key is pressed.
    _cputs(".");
	Xsleep(1);
  }
  _getch();  // use _getch to throw key away.
}
#else
int inkeyPlus(void) {
  struct termios oldt,
                 newt;
  int            ch=0, ch2, ch3;
  tcgetattr( STDIN_FILENO, &oldt );
  newt = oldt;
  newt.c_lflag &= ~( ICANON | ECHO );
  tcsetattr( STDIN_FILENO, TCSANOW, &newt );
  ch = getchar();
//printf("[%u]\n", ch);
  tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
  return ch;
}
#endif

//------------------------------------------------------
// this version of inkey is designed to deal with arrow keys, NOT FINISHED

#ifndef WIN32
int inkeyPlus2(void) {
  struct termios oldt,
                 newt;
  int            ch=0, ch2, ch3;
  tcgetattr( STDIN_FILENO, &oldt );
  newt = oldt;
  newt.c_lflag &= ~( ICANON | ECHO );
  tcsetattr( STDIN_FILENO, TCSANOW, &newt );
  ch = getchar();
  if (27 == ch) {      // 27 = ESC char
    int ch2 = getchar();
    if ('[' == ch2)
    {
      int ch3 = getchar();
      if (ch3 >= 'A' || ch3 <= 'D') ch = -(ch3-64);
    }
  } else {
    ungetc(ch, stdin);
    printf("%c", ch);
  }

//printf("ch is %u, ch2 is %u %u\n", ch, ch2, ch3);
  tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
  return ch;
}
#endif

//------------------------------------------------------
// this function converts an input string into a vector of individual strings
void Tokenize(const string& str, vector<string>& token, const string& delimiters)
{
    // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        token.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}


//------------------------------------------------------
// convert a c string to uppercase
void convertToUpperCase(char *sPtr)
{
  while(*sPtr != '\0') {
    *sPtr = toupper((unsigned char)*sPtr);
    sPtr++;
  }
}

//------------------------------------------------------
void logger(const char *msg)
{
  static int count1=1;

  printf("logger (%i), >%s<\n", count1++, msg);
}


//------------------------------------------------------
void fnMovement(void)
{
  int *lRmDat = gRmDat[giRoom-1];
  if (giRoom==16 && gRmDat[16-1][MONSTER]==1) {
    printf("\nThe dwarf refuses to let\nyou proceed...\n");
    Xsleep(1);
  } else {
    char c1 = token[1].c_str()[0];   // direction
    switch (c1) {
    case 'N':
      if ( 0==lRmDat[NORTH] ) printf("You cannot go that way\n"); else giRoom = lRmDat[NORTH];
      break;
    case 'S':
      if ( 0==lRmDat[SOUTH] ) printf("There is no exit south\n"); else giRoom = lRmDat[SOUTH];
      break;
    case 'E':
      if ( 0==lRmDat[EAST] ) printf("I see nowhere to the east to go\n"); else giRoom = lRmDat[EAST];
      break;
    case 'W':
      if ( 0==lRmDat[WEST] ) printf("Even you cannot walk through walls\n"); else giRoom = lRmDat[WEST];
      break;
    case 'U':
      if ( 0==lRmDat[UP] ) printf("There is no way to move up\n"); else giRoom = lRmDat[UP];
      break;
    case 'D':
      if ( 0==lRmDat[DOWN] ) printf("You cannot descend from here\n"); else giRoom = lRmDat[DOWN];
      break;
    }
  }
}


//------------------------------------------------------
void fnGetObjects(void)
{
  char lObjectCount=0; // number of objects being carried
  int *lRmDat = gRmDat[giRoom-1];                                 // gRmDat = gRoomDATA, lRmDat = current room data
  string lSecond3=token[1].substr(0,3);                   // lSecond3 is 2nd word user typed
  int l7=lRmDat[OBJECT1], l9=lRmDat[OBJECT2], l10=lRmDat[OBJECT3];               // values at positions 7, 9 and 10 . 7=object, 9 object, 10 object

  for (int j=0; j<5; j++) {
//printf("object %i is %i\n", j, gPack[j]);
    if (gPack[j]!=0) lObjectCount++;
  }
//printf("lFlag is %i\n", lFlag);
  if (lObjectCount==5) { printf("You are already carrying your\nmaximum of five objects\n"); return; }

  if ("CHE" == lSecond3) { printf("It is far too heavy to lift\n"); return; }   // CHE = CHEST

  if (l7==0 && l9==0 && l10==0) { printf("I see nothing to pick up\n"); return; }

  gObject1$ = gObjects[l7].substr(0,3);
  gObject2$ = gObjects[l9].substr(0,3);
  gObject3$ = gObjects[l10].substr(0,3);
//printf("gObject1$ is %s, gObject2$ is %s, gObject3$ is %s\n", gObject1$.c_str(), gObject2$.c_str(), gObject3$.c_str());
  int lN=0; // default picked up object is nothing bug 31/03/12
//printf("(orig.) lN is %i\n", lN);
  if (lSecond3==gObject1$) { lN=l7;  lRmDat[OBJECT1]=0; }
  if (lSecond3==gObject2$) { lN=l9;  lRmDat[OBJECT2]=0; }
  if (lSecond3==gObject3$) { lN=l10; lRmDat[OBJECT3]=0; }
/// it did not go into the above three--------------------------------
//printf("lN is %i\n", lN);

  for (int j=0; j<5; j++) {
    if (gPack[j]==0) { gPack[j]=lN;  break; }
  }
  if (lN>0) printf(">->YOU NOW HAVE THE %s\n", gObjects[lN].c_str() );
  return;
}


//------------------------------------------------------
void fnDropRoutine(void)
{
  char lFlag=FALSE;
  int *lRmDat = gRmDat[giRoom-1];
  string lSecond3=token[1].substr(0,3);
  int l7=lRmDat[OBJECT1], l9=lRmDat[OBJECT2], l10=lRmDat[OBJECT3];

  for (int j=0; j<5; j++) {
    if (gPack[j]!=0) { lFlag=TRUE; }
  }
  if (!lFlag) { printf("You are not carrying anything\n"); return; }

  if (l7!=0 && l9!=0 && l10!=0) { printf("This room already holds its maximum objects\n"); return; }

  gObject1$="";
  giDropped=0;
  for (int j=0; j<CHEST_OF_IRON; j++) {
    if (gObjects[j].substr(0,3) == lSecond3) { gObject1$=gObjects[j]; giDropped=j; }
  }

  if (gObject1$=="") { printf("How can you when you're\nnot holding it?\n"); }
//printf("object dropped is %i\n", giDropped);
  for (int j=0; j<5; j++) {
    if (gPack[j]==giDropped) { gPack[j]=0; }
  }

  if (l7==0) {
    lRmDat[OBJECT1]=giDropped;
  } else if (l9==0) {
    lRmDat[OBJECT2]=giDropped;
  } else if (l10==0)
    lRmDat[OBJECT3]=giDropped;
  else printf("fnDropRoutine() This should never happen !\n");

  const char *lObjDesc = gObject1$.c_str();
  if ( lSecond3=="DRO") printf("YOU HAVE DROPPED THE %s\n", lObjDesc );
  if ( lSecond3=="PUT") printf("YOU HAVE PUT THE %s DOWN\n", lObjDesc );
  if ( lSecond3=="THR") printf("WITH A MIGHTY HEAVE, YOU\nTHROW THE %s AWAY\n", lObjDesc );
  if ( lSecond3=="BRE") printf("YOU HAVE BROKEN THE %s\n", lObjDesc );
  return;
}


//------------------------------------------------------
void fnUnlockDoors(void)
{
  if (giRoom!=8 && giRoom!=34) { printf("There is no locked door in this room\n"); return; }
  
  char lFlag=0, lT=0;
  for (int j=0; j<5; j++)
  {
    if (gPack[j]==17) { lFlag=1; lT=j; }  // silver key
    if (gPack[j]==18) { lFlag=2; lT=j; }  // gold key
  }
  if (lFlag==0)
    { printf("You do not have a key!\n"); return; }

  if ( (lFlag==2 && giRoom==8) || (lFlag==1 && giRoom==34) )
    { printf("That key does not fit this door!\n"); return; }
  
  printf("There is a creak as the key turns\n");
  Xsleep(1);
  printf(".....THE DOOR IS NOW UNLOCKED...\n");
  gRmDat[giRoom-1][OBJECT1]=0;
  gPack[lT]=0;  // key is destroyed
  return;
}


//------------------------------------------------------
void fnOpenChest(void)
{
  string lSecond3=token[1].substr(0,3);

  if (lSecond3 != "CHE") {
    printf("THAT WOULD NOT BE WISE\n");
  } else if (giRoom!=13 && giRoom!=40) {
    printf("I CANNOT SEE ANYTHING TO OPEN HERE\n");
  } else if (gBOX==1) {
    if (rollDice(10) > 6) printf("It holds nothing but dust...\n");
  } else if (giRoom==13 || gBOX==1) {
    printf("IT IS EMPTY\n");
  } else if (gBOX==0) {
    printf("INSIDE YOU FIND A PARCHMENT, WITH\nTHE FOLLOWING MESSAGE: 'A little\nman can be bound by gold'\n");
    gBOX=1;
  }
  return;
}


//------------------------------------------------------
void fnReadScroll(void)
{
  char lFlag = FALSE;
  for (int j=0; j<5; j++) {
    if (gPack[j]==12) lFlag=TRUE;
  }

  if (!lFlag) { printf("You are not holding anything which you can read\n"); return; }

  int lR=rollDice(3);
  if (1==lR)
    printf("It says 'THE LOCKS NEED SPECIAL KEYS'\n");
  else if (2==lR)
    printf("The scroll reads:'CHESTS CAN CONTAIN AID'\n");
  else if (3==lR)
    printf("It says 'THE AMULET IS IMPORTANT'\n");

  return;
}

//------------------------------------------------------
void fnDrinkPotion(void)
{
  char lFlag = 0;
  for (int j=0; j<5; j++) {
    if (gPack[j]==13) lFlag=j;  // 13 = healing potion
    break;
  }
  if (lFlag==0) { printf("YOU CAN'T DRINK %s\n", token[1].c_str() ); return; }
  
  printf("You are instantly filled with\nhealing, and your strength is restored\n");
  printf("The bottle holding the potion\nmagically fades from view...\n");
  gST=20;
  gPack[lFlag]=0;
  return;
}

//------------------------------------------------------
void fnBribeDwarf(void)
{
  int *lRmDat = gRmDat[giRoom-1];   // lRmDat contains the room data
//printf("lRmDat[MONSTER] is %i\n", lRmDat[MONSTER] );

  if (lRmDat[MONSTER]==NO_MONSTER) {  // if there is no monster
    printf("THERE IS NOBODY HERE TO BRIBE !\n"); return;
  } else if (lRmDat[MONSTER]!=DWARF) { printf("YOU SHOULDN'T TRY THAT WITH A '%s'\n", gMonsters[lRmDat[MONSTER]].c_str() ); return; }

  printf("He demands the amulet!\n");
  int lFlagDie=FALSE;
  int lFlag=0;
  for (int j=0; j<5; j++) {
    if (gPack[j]==9) lFlag=j;   // 9 must be the Amulet
  }
  
  if (lFlag==0) {
    printf("YOU DO NOT HAVE IT...\n");
    Xsleep(2);
    if (rollDice(2)<2) {

      printf("HE DECIDES, HOWEVER, TO ACCEPT\n");
      printf("A 'GIFT' OF ");

      for (int j=0; j<5; j++) {
        if (gPack[j]!=0) lFlag=j;
      }

      if (lFlag==0) {
        printf("ANYTHING VALUABLE\n");   // 3200 
        lFlagDie=TRUE;
      } else {
        printf("THE %s\n", gObjects[lFlag].c_str() );
        gPack[lFlag]=0;
      }

    } else {
      printf("HE WOULD ACCEPT ANYTHING\nTHAT HE REALLY WANTS\n");  // 3100
      lFlagDie=TRUE;
    }

    if (lFlagDie==TRUE) {
      printf("BUT YOU HAVE NOTHING\n");  // 3210
      printf("AND SO HE KILLS YOU!!\n");
      gScore=100;
      gQuit=3;   // effectively GOTO 2570
    }

  } else {    // 3250
    printf("Lucky for you that you had it!\n");
    gPack[lFlag]=0;
    lRmDat[MONSTER]=NO_MONSTER;
  }
  return;
}

//-------------------------------------------------
// this function replaces Tokenize
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while(std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    return split(s, delim, elems);
}

//-------------------------------------------------
void sleepFlush(int _i)
{
  fflush(stdout);
  Xsleep(_i);   // windows version
}

#ifdef WIN32
void Xsleep(int _i)
{
  Sleep(_i*1000);   // window version
}
#else
void Xsleep(int _i)
{
  cout << ".";
//  sleep(_i);        // linux version is seconds
}
#endif
