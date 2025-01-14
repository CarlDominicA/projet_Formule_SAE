//
// NB! This is a file generated from the .4Dino file, changes will be lost
//     the next time the .4Dino file is built
//
/*
Programme : TEST_CAN_AFF.4Dino
Auteur :    Marc-Etienne Gendron-Fontaine, Felix-Antoine Guimont
Date :      10 avril 2024
Brief :     Ceci est le code pour la d�mo pour l'�v�nement Osentreprendre.

Materielle: ESP32-S3 (x1), Ecran 7" de 4d systeme, TJA1050 (x2)
Encironement: Workshop 4 V4.9.0.9,
Systeme d'exploitation: Windows 10 V22H2.
*/


#include "gfx4desp32_gen4_ESP32_70CT.h"

gfx4desp32_gen4_ESP32_70CT gfx = gfx4desp32_gen4_ESP32_70CT();

#include "TEST_CAN_AFFConst.h"    // Note. This file will not be created if there are no generated graphics

#include <ESP32-TWAI-CAN.hpp>



#define CAN_TX    43
#define CAN_RX    44

// VARIALBLE GLOBALE
CanFrame rxFrame;   // Pour la trame CAN


void setup()
{
  gfx.begin();
  gfx.Cls();
  gfx.ScrollEnable(false);
  gfx.BacklightOn(true);
  gfx.Orientation(LANDSCAPE);
  gfx.SmoothScrollSpeed(5);
  gfx.TextColor(WHITE, BLACK); gfx.Font(2);  gfx.TextSize(1);
  gfx.Open4dGFX("TEST_CAN_AFF"); // Opens DAT and GCI files for read using filename without extension.
  gfx.touch_Set(TOUCH_ENABLE);                // Global touch enabled

  // CAN -----------------------------------


  ESP32Can.setPins(CAN_TX, CAN_RX);                 // Initialisation des Pin RX et TX
  ESP32Can.setSpeed(ESP32Can.convertSpeed(1000));    // Initialisation de la vitesse de transmission

  // Initialisation du Queue size a 1.
  ESP32Can.setRxQueueSize(1);
  ESP32Can.setTxQueueSize(1);

  // regarde si les driver CAN sont demarre
  if(ESP32Can.begin())
  {
      gfx.println("CAN bus started!");
      delay(2000);
  }
  else
  {
      gfx.println("CAN bus failed!");
      while(1);
  }



  // Initialisation des widgets
  //gfx.UserImages(iAngularmeter1,0);
  gfx.UserImage(iLeddigits1);

}

void loop()
{

    // Si on recoit une trame CAN, on met a jour les widgets.
    // Sinon, on affiche "EN ATTENTE DE DONNEES...". Bloque a�
    // chaque 50 ms.
    if(ESP32Can.readFrame(rxFrame, 50))
    {
        // Efface  "EN ATTENTE DE DONNEES..."
        gfx.MoveTo(250,250);
        gfx.print("                            ");


        // Convertis les donnees recues (en ASCII) en INTEGER.
        int mil = ((int)rxFrame.data[4] - 48) * 1000;
        int cent = ((int)rxFrame.data[5] - 48) * 100;
        int diz = ((int)rxFrame.data[6] - 48) * 10;
        int uni = (int)rxFrame.data[7] - 48;
        int total = mil + cent + diz + uni;


        // Mets a jour les widgets
        //gfx.UserImages(iAngularmeter1, total);
        gfx.LedDigitsDisplay(total, iiLeddigits1, 4, 3, 53, 0);


    }
    else
    {
        gfx.Cls();  // Efface l'ecran

        // Mets le curseur au position X et Y.
        // Print ensuite "EN ATTENTE DE DONNEES..."
        gfx.MoveTo(250,250);
        gfx.print("EN ATTENTE DE DONNEES...");
    }

  // put your main code here, to run repeatedly:
  /*int itouched, val ;
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
  } */
}

