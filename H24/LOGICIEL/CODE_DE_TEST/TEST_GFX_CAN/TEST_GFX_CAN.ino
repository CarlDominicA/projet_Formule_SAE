//
// NB! This is a file generated from the .4Dino file, changes will be lost
//     the next time the .4Dino file is built
//
/*
Programme : TEST_GFX_CAN.4Dino
Auteur :    Marc-�tienne Gendron-Fontaine
Date :      13 mars 2024
Brief :     Ce fichier contient un code de test pour recevoir des trames CAN avec le ESP32-S3 de l'�cran.
            Ce code ne fait qu'afficher la partie data de la trame CAN avec la fonction "gfx.print()". Les
            trames CAN sont envoy�es au ESP32-S3 de l'�cran avec un autre ESP32.

Mat�rielle: ESP32-S3 (x2), TJA1050 (x2)
Encironement: Visual Studio Code V 1.86.2
Syst�me d�exploitation�: Windows 10 V22H2
*/



#include "gfx4desp32_gen4_ESP32_70CT.h"

gfx4desp32_gen4_ESP32_70CT gfx = gfx4desp32_gen4_ESP32_70CT();

#include "TEST_GFX_CANConst.h"    // Note. This file will not be created if there are no generated graphics

#include "ID_CAPT.h"
#include "CAN_FCT.h"
#include "CONST_AFF.h"
#include "CONST_AFF_BAT.h"
#include "CAN_FCT.h"

// GPIO par d�faut pour la communication CAN (s�rie)
#define CAN_TX    12
#define CAN_RX    13

CanFrame rxFrame;


void clear();
void affiche_message(String msg);



void setup()
{
  gfx.begin();
  gfx.Cls();
  gfx.ScrollEnable(false);
  gfx.BacklightOn(true);
  gfx.Orientation(LANDSCAPE);
  gfx.SmoothScrollSpeed(5);
  gfx.TextColor(WHITE, BLACK); gfx.Font(2);  gfx.TextSize(1);
  gfx.Open4dGFX("TEST_GFX_CAN"); // Opens DAT and GCI files for read using filename without extension.
  gfx.touch_Set(TOUCH_ENABLE);                // Global touch enabled

  // CAN -----------------------------------

  // Initialisation des GPIO pour recevoir/transmettre des trames CAN.
  ESP32Can.setPins(CAN_TX, CAN_RX);

  // Initialise la vitesse de communication du CAN.
  ESP32Can.setSpeed(ESP32Can.convertSpeed(500));

  // D�mare les driver TWAI
  if(ESP32Can.begin())
      gfx.println("CAN bus started!");
  else
      gfx.println("CAN bus failed!");

} // end Setup **do not alter, remove or duplicate this line**

void loop()
{

     String msg = "";

     msg = read_CAN(rxFrame);

     affiche_message(msg);






  // put your main code here, to run repeatedly:
  int itouched, val ;
  if(gfx.touch_Update())
  {
    itouched = gfx.imageTouched() ;
    switch (itouched)
    {                                                         // start touched selection **do not alter, remove or duplicate this line**
      // case statements for Knobs and Sliders go here
      default :                                               // end touched selection **do not alter, remove or duplicate this line**
        int button = gfx.ImageTouchedAuto();    // use default for keyboards and buttons
        val = gfx.getImageValue(button);
        switch (button)
        {                                                     // start button selection **do not alter, remove or duplicate this line**
          // case, one for each button or keyboard, default should end up as -1
        }                                                     // end button selection **do not alter, remove or duplicate this line**
    }
  }
}





void clear()
{
   gfx.RectangleFilled(0, 0, 800, 415, BLACK);

}



void affiche_message(String msg)
{

   gfx.MoveTo(150, 150);
   gfx.print(msg);


}
