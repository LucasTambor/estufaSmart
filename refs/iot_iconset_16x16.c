/*
Icon Set Name: IoT Icon set 16x16 bi-color
Version: 1.0.1
Origin URL:  http://engsta.com/iot-icon-set-for-i2c-oled-displays/
Author: Artur Funk
License: GNU General Public License v3


Description:
This icon set of 16x16 pixel icons was supports LCD's or OLED Displays.

Each icon will use 32 bytes of microcontroller flash. If you dont want
to waste you programm space, just delete or comment unused icons.

Tested on:
Used Library: Adafruit_SSD1306		https://github.com/adafruit/Adafruit_SSD1306
			  Adafruit-GFX-Library	https://github.com/adafruit/Adafruit-GFX-Library


How to use:
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


// Drawing an icon
display.drawBitmap(0, 34, home_icon16x16, 16, 16, 1);

*/

#include "iot_iconset_16x16.h"
/*
 unsigned char home_icon16x16[] =
{
	0b00000111, 0b11100000, //      ######
	0b00001111, 0b11110000, //     ########
	0b00011111, 0b11111000, //    ##########
	0b00111111, 0b11111100, //   ############
	0b01111111, 0b11111110, //  ##############
	0b11111111, 0b11111111, // ################
	0b11000000, 0b00000011, // ##            ##
	0b11000000, 0b00000011, // ##            ##
	0b11000000, 0b00000011, // ##            ##
	0b11001111, 0b11110011, // ##  ########  ##
	0b11001111, 0b11110011, // ##  ########  ##
	0b11001100, 0b00110011, // ##  ##    ##  ##
	0b11001100, 0b00110011, // ##  ##    ##  ##
	0b11001100, 0b00110011, // ##  ##    ##  ##
	0b11111100, 0b00111111, // ######    ######
	0b11111100, 0b00111111, // ######    ######
};
 unsigned char arrow_up_icon16x16[] =
{
	0b00000001, 0b10000000, //        ##
	0b00000011, 0b11000000, //       ####
	0b00000111, 0b11100000, //      ######
	0b00001111, 0b11110000, //     ########
	0b00011110, 0b01111000, //    ####  ####
	0b00111100, 0b00111100, //   ####    ####
	0b01111000, 0b00011110, //  ####      ####
	0b11111100, 0b00111111, // ######    ######
	0b11111100, 0b00111111, // ######    ######
	0b01111100, 0b00111110, //  #####    #####
	0b00011100, 0b00111000, //    ###    ###
	0b00011100, 0b00111000, //    ###    ###
	0b00011100, 0b00111000, //    ###    ###
	0b00011111, 0b11111000, //    ##########
	0b00011111, 0b11111000, //    ##########
	0b00001111, 0b11110000, //     ########
};

 unsigned char arrow_down_icon16x16[] =
{
	0b00001111, 0b11110000, //     ########
	0b00011111, 0b11111000, //    ##########
	0b00011111, 0b11111000, //    ##########
	0b00011100, 0b00111000, //    ###    ###
	0b00011100, 0b00111000, //    ###    ###
	0b00011100, 0b00111000, //    ###    ###
	0b01111100, 0b00111110, //  #####    #####
	0b11111100, 0b00111111, // ######    ######
	0b11111100, 0b00111111, // ######    ######
	0b01111000, 0b00011110, //  ####      ####
	0b00111100, 0b00111100, //   ####    ####
	0b00011110, 0b01111000, //    ####  ####
	0b00001111, 0b11110000, //     ########
	0b00000111, 0b11100000, //      ######
	0b00000011, 0b11000000, //       ####
	0b00000001, 0b10000000, //        ##
};

 unsigned char arrow_left_icon16x16[] =
{
	0b00000001, 0b10000000, //        ##
	0b00000011, 0b11000000, //       ####
	0b00000111, 0b11000000, //      #####
	0b00001111, 0b11111110, //     ###########
	0b00011111, 0b11111111, //    #############
	0b00111101, 0b11111111, //   #### #########
	0b01111000, 0b00000111, //  ####        ###
	0b11110000, 0b00000111, // ####         ###
	0b11110000, 0b00000111, // ####         ###
	0b01111000, 0b00000111, //  ####        ###
	0b00111101, 0b11111111, //   #### #########
	0b00011111, 0b11111111, //    #############
	0b00001111, 0b11111110, //     ###########
	0b00000111, 0b11000000, //      #####
	0b00000011, 0b11000000, //       ####
	0b00000001, 0b10000000, //        ##
};

 unsigned char arrow_right_icon16x16[] =
{
	0b00000001, 0b10000000, //        ##
	0b00000011, 0b11000000, //       ####
	0b00000011, 0b11100000, //       #####
	0b01111111, 0b11110000, //  ###########
	0b11111111, 0b11111000, // #############
	0b11111111, 0b10111100, // ######### ####
	0b11100000, 0b00011110, // ###        ####
	0b11100000, 0b00001111, // ###         ####
	0b11100000, 0b00001111, // ###         ####
	0b11100000, 0b00011110, // ###        ####
	0b11111111, 0b10111100, // ######### ####
	0b11111111, 0b11111000, // #############
	0b01111111, 0b11110000, //  ###########
	0b00000011, 0b11100000, //       #####
	0b00000011, 0b11000000, //       ####
	0b00000001, 0b10000000, //        ##
};

 unsigned char bat0_icon16x16[] =
{
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00111111, 0b11111000, //   ###########
	0b01111111, 0b11111100, //  #############
	0b11111111, 0b11111110, // ###############
	0b11100000, 0b00000110, // ###          ##
	0b11100000, 0b00000111, // ###          ###
	0b11100000, 0b00000111, // ###          ###
	0b11100000, 0b00000110, // ###          ##
	0b11111111, 0b11111110, // ###############
	0b01111111, 0b11111100, //  #############
	0b00111111, 0b11111000, //   ###########
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
};

 unsigned char bat1_icon16x16[] =
{
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00111111, 0b11111000, //   ###########
	0b01111111, 0b11111100, //  #############
	0b11111111, 0b11111110, // ###############
	0b11101100, 0b00000110, // ### ##       ##
	0b11101100, 0b00000111, // ### ##       ###
	0b11101100, 0b00000111, // ### ##       ###
	0b11101100, 0b00000110, // ### ##       ##
	0b11111111, 0b11111110, // ###############
	0b01111111, 0b11111100, //  #############
	0b00111111, 0b11111000, //   ###########
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
};

 unsigned char bat2_icon16x16[] =
{
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00111111, 0b11111000, //   ###########
	0b01111111, 0b11111100, //  #############
	0b11111111, 0b11111110, // ###############
	0b11101101, 0b10000110, // ### ## ##    ##
	0b11101101, 0b10000111, // ### ## ##    ###
	0b11101101, 0b10000111, // ### ## ##    ###
	0b11101101, 0b10000110, // ### ## ##    ##
	0b11111111, 0b11111110, // ###############
	0b01111111, 0b11111100, //  #############
	0b00111111, 0b11111000, //   ###########
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
};

 unsigned char bat3_icon16x16[] =
{
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00111111, 0b11111000, //   ###########
	0b01111111, 0b11111100, //  #############
	0b11111111, 0b11111110, // ###############
	0b11101101, 0b10110110, // ### ## ## ## ##
	0b11101101, 0b10110111, // ### ## ## ## ###
	0b11101101, 0b10110111, // ### ## ## ## ###
	0b11101101, 0b10110110, // ### ## ## ## ##
	0b11111111, 0b11111110, // ###############
	0b01111111, 0b11111100, //  #############
	0b00111111, 0b11111000, //   ###########
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
};

 unsigned char bat4_icon16x16[] =
{
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00111111, 0b11111000, //   ###########
	0b01111111, 0b11111100, //  #############
	0b11111111, 0b11111110, // ###############
	0b11100000, 0b00000110, // ###          ##
	0b11100000, 0b01100111, // ###      ##  ###
	0b11100111, 0b11110111, // ###  ####### ###
	0b11100011, 0b00000110, // ###   ##     ##
	0b11111111, 0b11111110, // ###############
	0b01111111, 0b11111100, //  #############
	0b00111111, 0b11111000, //   ###########
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
};

 unsigned char bluetooth_icon16x16[] =
{
	0b00000000, 0b00000000, //
	0b00000001, 0b10000000, //        ##
	0b00000001, 0b11000000, //        ###
	0b00000001, 0b01100000, //        # ##
	0b00001001, 0b00110000, //     #  #  ##
	0b00001101, 0b00110000, //     ## #  ##
	0b00000111, 0b01100000, //      ### ##
	0b00000011, 0b11000000, //       ####
	0b00000001, 0b10000000, //        ##
	0b00000011, 0b11000000, //       ####
	0b00000111, 0b01100000, //      ### ##
	0b00001101, 0b00110000, //     ## #  ##
	0b00001001, 0b00110000, //     #  #  ##
	0b00000001, 0b01100000, //        # ##
	0b00000001, 0b11000000, //        ###
	0b00000001, 0b10000000, //        ##
};

 unsigned char bulb_icon16x16[] =
{
	0b00000000, 0b00000000, //
	0b00000011, 0b11100000, //       #####
	0b00000100, 0b00010000, //      #     #
	0b00001000, 0b00001000, //     #       #
	0b00010000, 0b00000100, //    #         #
	0b00010000, 0b00000100, //    #         #
	0b00010000, 0b00000100, //    #         #
	0b00010000, 0b00000100, //    #         #
	0b00010000, 0b00000100, //    #         #
	0b00001000, 0b00001000, //     #       #
	0b00000100, 0b00010000, //      #     #
	0b00000011, 0b11100000, //       #####
	0b00000010, 0b00100000, //       #   #
	0b00000011, 0b11100000, //       #####
	0b00000010, 0b00100000, //       #   #
	0b00000011, 0b11100000, //       #####
};

 unsigned char bulb_on_icon16x16[] =
{
	0b00000000, 0b00000000, //
	0b00100011, 0b11100010, //   #   #####   #
	0b00010100, 0b00010100, //    # #     # #
	0b00001000, 0b00001000, //     #       #
	0b00010000, 0b00000100, //    #         #
	0b00010000, 0b00000100, //    #         #
	0b00010000, 0b00000100, //    #         #
	0b00010000, 0b00000100, //    #         #
	0b00010000, 0b00000100, //    #         #
	0b00001000, 0b00001000, //     #       #
	0b00010100, 0b00010100, //    # #     # #
	0b00100011, 0b11100010, //   #   #####   #
	0b00000010, 0b00100000, //       #   #
	0b00000011, 0b11100000, //       #####
	0b00000010, 0b00100000, //       #   #
	0b00000011, 0b11100000, //       #####
};

 unsigned char bulb_off_icon16x16[] =
{
	0b00000000, 0b00000000, //
	0b00000011, 0b11100000, //       #####
	0b00000111, 0b11110000, //      #######
	0b00001111, 0b11111000, //     #########
	0b00011111, 0b11111100, //    ###########
	0b00011111, 0b11111100, //    ###########
	0b00011111, 0b11111100, //    ###########
	0b00011111, 0b11111100, //    ###########
	0b00011111, 0b11111100, //    ###########
	0b00001111, 0b11111000, //     #########
	0b00000100, 0b00010000, //      #     #
	0b00000011, 0b11100000, //       #####
	0b00000010, 0b00100000, //       #   #
	0b00000011, 0b11100000, //       #####
	0b00000010, 0b00100000, //       #   #
	0b00000011, 0b11100000, //       #####
};

 unsigned char bullet_icon16x16[] =
{
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000011, 0b10000000, //       ###
	0b00001111, 0b11100000, //     #######
	0b00001111, 0b11100000, //     #######
	0b00011111, 0b11110000, //    #########
	0b00011111, 0b11110000, //    #########
	0b00011111, 0b11110000, //    #########
	0b00001111, 0b11100000, //     #######
	0b00001111, 0b11100000, //     #######
	0b00000011, 0b10000000, //       ###
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
};

 unsigned char cancel_icon16x16[] =
{
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00111000, 0b00001110, //   ###       ###
	0b00111100, 0b00011110, //   ####     ####
	0b00111110, 0b00111110, //   #####   #####
	0b00011111, 0b01111100, //    ##### #####
	0b00001111, 0b11111000, //     #########
	0b00000111, 0b11110000, //      #######
	0b00000011, 0b11100000, //       #####
	0b00000111, 0b11110000, //      #######
	0b00001111, 0b11111000, //     #########
	0b00011111, 0b01111100, //    ##### #####
	0b00111110, 0b00111110, //   #####   #####
	0b00111100, 0b00011110, //   ####     ####
	0b00111000, 0b00001110, //   ###       ###
	0b00000000, 0b00000000, //
};

 unsigned char check_icon16x16[] =
{
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000111, //              ###
	0b00000000, 0b00001111, //             ####
	0b00000000, 0b00011111, //            #####
	0b01110000, 0b00111110, //  ###      #####
	0b01111000, 0b01111100, //  ####    #####
	0b01111100, 0b11111000, //  #####  #####
	0b00011111, 0b11110000, //    #########
	0b00001111, 0b11100000, //     #######
	0b00000111, 0b11000000, //      #####
	0b00000011, 0b10000000, //       ###
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
};

 unsigned char fillstate1_icon16x16[] =
{
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b01111111, 0b11111110, //  ##############
	0b01111111, 0b11111110, //  ##############
	0b01111111, 0b11111110, //  ##############
};

 unsigned char fillstate2_icon16x16[] =
{
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b01111111, 0b11111110, //  ##############
	0b01111111, 0b11111110, //  ##############
	0b01111111, 0b11111110, //  ##############
	0b00000000, 0b00000000, //
	0b01111111, 0b11111110, //  ##############
	0b01111111, 0b11111110, //  ##############
	0b01111111, 0b11111110, //  ##############
};

 unsigned char fillstate3_icon16x16[] =
{
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b01111111, 0b11111110, //  ##############
	0b01111111, 0b11111110, //  ##############
	0b01111111, 0b11111110, //  ##############
	0b00000000, 0b00000000, //
	0b01111111, 0b11111110, //  ##############
	0b01111111, 0b11111110, //  ##############
	0b01111111, 0b11111110, //  ##############
	0b00000000, 0b00000000, //
	0b01111111, 0b11111110, //  ##############
	0b01111111, 0b11111110, //  ##############
	0b01111111, 0b11111110, //  ##############
};

 unsigned char fillstate4_icon16x16[] =
{
	0b00000000, 0b00000000, //
	0b01111111, 0b11111110, //  ##############
	0b01111111, 0b11111110, //  ##############
	0b01111111, 0b11111110, //  ##############
	0b00000000, 0b00000000, //
	0b01111111, 0b11111110, //  ##############
	0b01111111, 0b11111110, //  ##############
	0b01111111, 0b11111110, //  ##############
	0b00000000, 0b00000000, //
	0b01111111, 0b11111110, //  ##############
	0b01111111, 0b11111110, //  ##############
	0b01111111, 0b11111110, //  ##############
	0b00000000, 0b00000000, //
	0b01111111, 0b11111110, //  ##############
	0b01111111, 0b11111110, //  ##############
	0b01111111, 0b11111110, //  ##############
};

 unsigned char speak_icon16x16[] =
{
	0b00111111, 0b11111100, //   ############
	0b01111111, 0b11111110, //  ##############
	0b11111111, 0b11111111, // ################
	0b11110000, 0b00001111, // ####        ####
	0b11100000, 0b00000111, // ###          ###
	0b11100000, 0b00000111, // ###          ###
	0b11100000, 0b00000111, // ###          ###
	0b11100000, 0b00000111, // ###          ###
	0b11100000, 0b00000111, // ###          ###
	0b11100000, 0b00000111, // ###          ###
	0b11110000, 0b00001111, // ####        ####
	0b11110001, 0b11111110, // ####   ########
	0b01111011, 0b11111100, //  #### ########
	0b00111111, 0b11111000, //   ###########
	0b00011110, 0b00000000, //    ####
	0b00001100, 0b00000000, //     ##
};

 unsigned char heart_icon16x16[] =
{
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00111100, 0b01111000, //   ####   ####
	0b01111110, 0b11111100, //  ###### ######
	0b11111111, 0b11111110, // ###############
	0b11111111, 0b11111110, // ###############
	0b11111111, 0b11111110, // ###############
	0b11111111, 0b11111110, // ###############
	0b01111111, 0b11111100, //  #############
	0b01111111, 0b11111100, //  #############
	0b00111111, 0b11111000, //   ###########
	0b00011111, 0b11110000, //    #########
	0b00001111, 0b11100000, //     #######
	0b00000111, 0b11000000, //      #####
	0b00000011, 0b10000000, //       ###
	0b00000001, 0b00000000, //    	  #
};

 unsigned char nocon_icon16x16[] =
{
	0b00000000, 0b00000000, //
	0b00000011, 0b11100000, //       #####
	0b00001111, 0b11111000, //     #########
	0b00011111, 0b11111100, //    ###########
	0b00111110, 0b00111110, //   #####   #####
	0b00111000, 0b01111110, //   ###    ######
	0b01110000, 0b11111111, //  ###    ########
	0b01110001, 0b11110111, //  ###   ##### ###
	0b01110011, 0b11000111, //  ###  ####   ###
	0b01110111, 0b10000111, //  ### ####    ###
	0b00111111, 0b00001110, //   ######    ###
	0b00111110, 0b00011110, //   #####    ####
	0b00011111, 0b11111100, //    ###########
	0b00001111, 0b11111000, //     #########
	0b00000011, 0b11100000, //       #####
	0b00000000, 0b00000000, //
};
 unsigned char tool_icon16x16[] =
{
	0b00000000, 0b00000000, //
	0b00000000, 0b01100000, //          ##
	0b00000000, 0b11100000, //         ###
	0b00000001, 0b11000000, //        ###
	0b00000001, 0b11000000, //        ###
	0b00000001, 0b11100110, //        ####  ##
	0b00000011, 0b11111110, //       #########
	0b00000111, 0b11111100, //      #########
	0b00001111, 0b11111000, //     #########
	0b00011111, 0b11000000, //    #######
	0b00111111, 0b10000000, //   #######
	0b01111111, 0b00000000, //  #######
	0b11111110, 0b00000000, // #######
	0b11111100, 0b00000000, // ######
	0b11111000, 0b00000000, // #####
	0b01110000, 0b00000000, //  ###
};

 unsigned char plug_icon16x16[] =
{
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000110, 0b01100000, //      ##  ##
	0b00000110, 0b01100000, //      ##  ##
	0b00000110, 0b01100000, //      ##  ##
	0b00000110, 0b01100000, //      ##  ##
	0b00111111, 0b11111100, //   ############
	0b00111111, 0b11111100, //   ############
	0b00111111, 0b11111100, //   ############
	0b00111111, 0b11111100, //   ############
	0b00011111, 0b11111000, //    ##########
	0b00001111, 0b11110000, //     ########
	0b00000111, 0b11100000, //      ######
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
};

 unsigned char powerbutton_icon16x16[] =
{
	0b00000000, 0b00000000, //
	0b00000001, 0b11000000, //        ###
	0b00001101, 0b11011000, //     ## ### ##
	0b00011101, 0b11011100, //    ### ### ###
	0b00111101, 0b11011110, //   #### ### ####
	0b00111001, 0b11001110, //   ###  ###  ###
	0b01110001, 0b11000111, //  ###   ###   ###
	0b01110001, 0b11000111, //  ###   ###   ###
	0b01110001, 0b11000111, //  ###   ###   ###
	0b01110000, 0b00000111, //  ###         ###
	0b00111000, 0b00001110, //   ###       ###
	0b00111110, 0b00011110, //   #####    ####
	0b00011111, 0b11111100, //    ###########
	0b00001111, 0b11111000, //     #########
	0b00000011, 0b11100000, //       #####
	0b00000000, 0b00000000, //
};

 unsigned char wallplug_icon16x16[] =
{
	0b00000000, 0b00000000, //
	0b11111111, 0b11111111, // ################
	0b10000000, 0b00000001, // #              #
	0b10111111, 0b11111101, // # ############ #
	0b10100000, 0b00000101, // # #          # #
	0b10100000, 0b00000101, // # #          # #
	0b10100000, 0b00000101, // # #          # #
	0b10100000, 0b00000101, // # #          # #
	0b10100110, 0b01100101, // # #  ##  ##  # #
	0b10100110, 0b01100101, // # #  ##  ##  # #
	0b10100000, 0b00000101, // # #          # #
	0b10100000, 0b00000101, // # #          # #
	0b10100000, 0b00000101, // # #          # #
	0b10111111, 0b11111101, // # ############ #
	0b10000000, 0b00000001, // #              #
	0b11111111, 0b11111111, // ################
};
*/
 unsigned char wifi1_icon16x16[] =
{
	0b00000000, 0b00000000, //
	0b00000111, 0b11100000, //      ######
	0b00011111, 0b11111000, //    ##########
	0b00111111, 0b11111100, //   ############
	0b01110000, 0b00001110, //  ###        ###
	0b01100111, 0b11100110, //  ##  ######  ##
	0b00001111, 0b11110000, //     ########
	0b00011000, 0b00011000, //    ##      ##
	0b00000011, 0b11000000, //       ####
	0b00000111, 0b11100000, //      ######
	0b00000100, 0b00100000, //      #    #
	0b00000001, 0b10000000, //        ##
	0b00000001, 0b10000000, //        ##
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
};

 unsigned char wifi2_icon16x16[] =
{
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000111, 0b11100000, //      ######
	0b00001111, 0b11110000, //     ########
	0b00011000, 0b00011000, //    ##      ##
	0b00000011, 0b11000000, //       ####
	0b00000111, 0b11100000, //      ######
	0b00000100, 0b00100000, //      #    #
	0b00000001, 0b10000000, //        ##
	0b00000001, 0b10000000, //        ##
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
};
/*
 unsigned char clock_icon16x16[] =
{
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000011, 0b11100000, //       #####
	0b00000111, 0b11110000, //      #######
	0b00001100, 0b00011000, //     ##     ##
	0b00011000, 0b00001100, //    ##       ##
	0b00110000, 0b00000110, //   ##         ##
	0b00110000, 0b00000110, //   ##         ##
	0b00110000, 0b11111110, //   ##    #######
	0b00110000, 0b10000110, //   ##    #    ##
	0b00110000, 0b10000110, //   ##    #    ##
	0b00011000, 0b10001100, //    ##   #   ##
	0b00001100, 0b00011000, //     ##     ##
	0b00000111, 0b11110000, //      #######
	0b00000011, 0b11100000, //       #####
	0b00000000, 0b00000000, //
};

 unsigned char timer_icon16x16[] =
{
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000011, 0b11100000, //       #####
	0b00000111, 0b11110000, //      #######
	0b00001100, 0b10011000, //     ##  #  ##
	0b00011000, 0b00111100, //    ##     ####
	0b00110000, 0b01110110, //   ##     ### ##
	0b00110000, 0b11100110, //   ##    ###  ##
	0b00111001, 0b11001110, //   ###  ###  ###
	0b00110000, 0b10000110, //   ##    #    ##
	0b00110000, 0b00000110, //   ##         ##
	0b00011000, 0b00001100, //    ##       ##
	0b00001100, 0b10011000, //     ##  #  ##
	0b00000111, 0b11110000, //      #######
	0b00000011, 0b11100000, //       #####
	0b00000000, 0b00000000, //
};

 unsigned char water_tap_icon16x16[] =
{
	0b00000001, 0b10000000, //        ##
	0b00000111, 0b11100000, //      ######
	0b00000001, 0b10000000, //        ##
	0b00001111, 0b11110000, //     ########
	0b11111111, 0b11111110, // ###############
	0b11111111, 0b11111111, // ################
	0b11111111, 0b11111111, // ################
	0b11111111, 0b11111111, // ################
	0b00000000, 0b00001111, //             ####
	0b00000000, 0b00001111, //             ####
	0b00000000, 0b00000000, //
	0b00000000, 0b00001100, //             ##
	0b00000000, 0b00001100, //             ##
	0b00000000, 0b00000000, //
	0b00000000, 0b00001100, //             ##
	0b00000000, 0b00001100, //             ##
};

 unsigned char humidity_icon16x16[] =
{
	0b00000000, 0b00000000, //
	0b00000001, 0b10000000, //        ##
	0b00000011, 0b11000000, //       ####
	0b00000111, 0b11100000, //      ######
	0b00001110, 0b01110000, //     ###  ###
	0b00001100, 0b00110000, //     ##    ##
	0b00011100, 0b00111000, //    ###    ###
	0b00011000, 0b00011000, //    ##      ##
	0b00111000, 0b00011100, //   ###      ###
	0b00111000, 0b00011100, //   ###      ###
	0b00111000, 0b00011100, //   ###      ###
	0b00011100, 0b00111000, //    ###    ###
	0b00011111, 0b11111000, //    ##########
	0b00001111, 0b11110000, //     ########
	0b00000011, 0b11000000, //       ####
	0b00000000, 0b00000000, //
};

 unsigned char humidity2_icon16x16[] =
{
	0b00000000, 0b00000000, //
	0b00000001, 0b10000000, //        ##
	0b00000011, 0b11000000, //       ####
	0b00000111, 0b11100000, //      ######
	0b00001111, 0b11110000, //     ########
	0b00001111, 0b11110000, //     ########
	0b00011111, 0b11111000, //    ##########
	0b00011111, 0b11011000, //    ####### ##
	0b00111111, 0b10011100, //   #######  ###
	0b00111111, 0b10011100, //   #######  ###
	0b00111111, 0b00011100, //   ######   ###
	0b00011110, 0b00111000, //    ####   ###
	0b00011111, 0b11111000, //    ##########
	0b00001111, 0b11110000, //     ########
	0b00000011, 0b11000000, //       ####
	0b00000000, 0b00000000, //
};

 unsigned char sun_icon16x16[] =
{
	0b00000000, 0b00000000, //
	0b00100000, 0b10000010, //   #     #     #
	0b00010000, 0b10000100, //    #    #    #
	0b00001000, 0b00001000, //     #       #
	0b00000001, 0b11000000, //        ###
	0b00000111, 0b11110000, //      #######
	0b00000111, 0b11110000, //      #######
	0b00001111, 0b11111000, //     #########
	0b01101111, 0b11111011, //  ## ######### ##
	0b00001111, 0b11111000, //     #########
	0b00000111, 0b11110000, //      #######
	0b00000111, 0b11110000, //      #######
	0b00010001, 0b11000100, //    #   ###   #
	0b00100000, 0b00000010, //   #           #
	0b01000000, 0b10000001, //  #      #      #
	0b00000000, 0b10000000, //         #
};

 unsigned char temperature_icon16x16[] =
{
	0b00000001, 0b11000000, //        ###
	0b00000011, 0b11100000, //       #####
	0b00000111, 0b00100000, //      ###  #
	0b00000111, 0b11100000, //      ######
	0b00000111, 0b00100000, //      ###  #
	0b00000111, 0b11100000, //      ######
	0b00000111, 0b00100000, //      ###  #
	0b00000111, 0b11100000, //      ######
	0b00000111, 0b00100000, //      ###  #
	0b00001111, 0b11110000, //     ########
	0b00011111, 0b11111000, //    ##########
	0b00011111, 0b11111000, //    ##########
	0b00011111, 0b11111000, //    ##########
	0b00011111, 0b11111000, //    ##########
	0b00001111, 0b11110000, //     ########
	0b00000111, 0b11100000, //      ######
};

 unsigned char noninverted_icon16x16[] =
{
	0b00000000, 0b00000000, //
	0b01111111, 0b11111110, //  ##############
	0b01111111, 0b11111110, //  ##############
	0b01011111, 0b11111110, //  # ############
	0b01001111, 0b11111110, //  #  ###########
	0b01000111, 0b11111110, //  #   ##########
	0b01000011, 0b11111110, //  #    #########
	0b01000001, 0b11111110, //  #     ########
	0b01000000, 0b11111110, //  #      #######
	0b01000000, 0b01111110, //  #       ######
	0b01000000, 0b00111110, //  #        #####
	0b01000000, 0b00011110, //  #         ####
	0b01000000, 0b00001110, //  #          ###
	0b01000000, 0b00000110, //  #           ##
	0b01111111, 0b11111110, //  ##############
	0b00000000, 0b00000000, //
};

 unsigned char inverted_icon16x16[] =
{
	0b00000000, 0b00000000, //
	0b01111111, 0b11111110, //  ##############
	0b01100000, 0b00000010, //  ##           #
	0b01110000, 0b00000010, //  ###          #
	0b01111000, 0b00000010, //  ####         #
	0b01111100, 0b00000010, //  #####        #
	0b01111110, 0b00000010, //  ######       #
	0b01111111, 0b00000010, //  #######      #
	0b01111111, 0b10000010, //  ########     #
	0b01111111, 0b11000010, //  #########    #
	0b01111111, 0b11100010, //  ##########   #
	0b01111111, 0b11110010, //  ###########  #
	0b01111111, 0b11111010, //  ############ #
	0b01111111, 0b11111110, //  ##############
	0b01111111, 0b11111110, //  ##############
	0b00000000, 0b00000000, //
};

 unsigned char lock_closed_icon16x16[] =
{
	0b00111111, 0b11111100, //   ############
	0b00111111, 0b11111100, //   ############
	0b00111000, 0b00011100, //   ###      ###
	0b00111000, 0b00011100, //   ###      ###
	0b00111000, 0b00011100, //   ###      ###
	0b01111111, 0b11111110, //  ##############
	0b01111111, 0b11111110, //  ##############
	0b01111111, 0b11111110, //  ##############
	0b01111111, 0b11111110, //  ##############
	0b01111110, 0b01111110, //  ######  ######
	0b01111110, 0b01111110, //  ######  ######
	0b01111110, 0b01111110, //  ######  ######
	0b01111110, 0b01111110, //  ######  ######
	0b01111111, 0b11111110, //  ##############
	0b01111111, 0b11111110, //  ##############
	0b00000000, 0b00000000, //
};

 unsigned char lock_open_icon16x16[] =
{
	0b00111111, 0b11111100, //   ############
	0b00111111, 0b11111100, //   ############
	0b00111000, 0b00011100, //   ###      ###
	0b00111000, 0b00000000, //   ###
	0b00111000, 0b00000000, //   ###
	0b01111111, 0b11111110, //  ##############
	0b01111111, 0b11111110, //  ##############
	0b01111111, 0b11111110, //  ##############
	0b01111111, 0b11111110, //  ##############
	0b01111110, 0b01111110, //  ######  ######
	0b01111110, 0b01111110, //  ######  ######
	0b01111110, 0b01111110, //  ######  ######
	0b01111110, 0b01111110, //  ######  ######
	0b01111111, 0b11111110, //  ##############
	0b01111111, 0b11111110, //  ##############
	0b00000000, 0b00000000, //
};

 unsigned char person_icon16x16[] =
{
	0b00000111, 0b11100000, //      ######
	0b00001111, 0b11110000, //     ########
	0b00001111, 0b11110000, //     ########
	0b00011111, 0b11111000, //    ##########
	0b00011111, 0b11111000, //    ##########
	0b00011111, 0b11111000, //    ##########
	0b00011111, 0b11111000, //    ##########
	0b00001111, 0b11110000, //     ########
	0b00001111, 0b11110000, //     ########
	0b00000111, 0b11100000, //      ######
	0b00000111, 0b11100000, //      ######
	0b00111111, 0b11111100, //   ############
	0b01111111, 0b11111110, //  ##############
	0b11111111, 0b11111111, // ################
	0b11111111, 0b11111111, // ################
	0b11111111, 0b11111111, // ################
};
 unsigned char window_icon16x16[] =
{
	0b01111111, 0b11111111, //  ###############
	0b01111111, 0b11111111, //  ###############
	0b01100001, 0b10001111, //  ##    ##   ####
	0b01100001, 0b10011011, //  ##    ##  ## ##
	0b01100001, 0b10110011, //  ##    ## ##  ##
	0b01111111, 0b10110011, //  ######## ##  ##
	0b01111111, 0b10110011, //  ######## ##  ##
	0b01100001, 0b10110011, //  ##    ## ##  ##
	0b01100001, 0b10110011, //  ##    ## ##  ##
	0b01100001, 0b10110011, //  ##    ## ##  ##
	0b01100001, 0b10110011, //  ##    ## ##  ##
	0b01100001, 0b10110011, //  ##    ## ##  ##
	0b01100001, 0b10110011, //  ##    ## ##  ##
	0b01100001, 0b10110011, //  ##    ## ##  ##
	0b01111111, 0b11111111, //  ###############
	0b01111111, 0b11111111, //  ###############
};
 unsigned char door_icon16x16[] =
{
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00001111, 0b11111000, //     #########
	0b00001111, 0b11111000, //     #########
	0b00001011, 0b11111000, //     # #######
	0b00001000, 0b11111000, //     #   #####
	0b00001000, 0b00111000, //     #     ###
	0b00001000, 0b00111000, //     #     ###
	0b00001000, 0b00111000, //     #     ###
	0b00001000, 0b10111000, //     #   # ###
	0b00001000, 0b10111000, //     #   # ###
	0b00001000, 0b00111000, //     #     ###
	0b00001000, 0b00111000, //     #     ###
	0b00001100, 0b00111000, //     ##    ###
	0b00000011, 0b00100000, //       ##  #
	0b00000000, 0b11100000, //         ###
};
 unsigned char face_icon16x16[] =
{
	0b00000000, 0b00000000, //
	0b00000001, 0b11000000, //        ###
	0b00001111, 0b11111000, //     #########
	0b00011101, 0b11011000, //    ### ### ##
	0b00011000, 0b00001100, //    ##       ##
	0b00010000, 0b00000100, //    #         #
	0b00101111, 0b11111010, //   # ######### #
	0b01111111, 0b01111111, //  ####### #######
	0b01100111, 0b01111011, //  ##  ### #### ##
	0b01100111, 0b01110011, //  ##  ### ###  ##
	0b00100000, 0b10000010, //   #     #     #
	0b00010000, 0b00100000, //    #         #
	0b00001011, 0b11101000, //     # ##### #
	0b00000100, 0b00010000, //      #     #
	0b00000011, 0b11100000, //       #####
	0b00000000, 0b00000000, //
};
 unsigned char siren_icon16x16[] =
{
	0b10000000, 0b10000001, // #       #      #
	0b01000000, 0b10000010, //  #      #     #
	0b00100000, 0b10000100, //   #     #    #
	0b00010011, 0b11101000, //    #  ##### #
	0b00000111, 0b11110000, //      #######
	0b00001111, 0b11111000, //     #########
	0b00001111, 0b10111000, //     ##### ###
	0b00011111, 0b10011100, //    ######  ###
	0b00011111, 0b10011100, //    ######  ###
	0b00011111, 0b10001100, //    ######   ##
	0b00111111, 0b10001110, //   #######   ###
	0b00111111, 0b10001110, //   #######   ###
	0b01111111, 0b11111111, //  ###############
	0b01111111, 0b11111111, //  ###############
	0b01111111, 0b11111111, //  ###############
	0b00000000, 0b00000000, //
};
 unsigned char warning_icon16x16[] =
{
	0b00000000, 0b10000000, //         #
	0b00000001, 0b11000000, //        ###
	0b00000001, 0b11000000, //        ###
	0b00000011, 0b11100000, //       #####
	0b00000011, 0b01100000, //       ## ##
	0b00000111, 0b01110000, //      ### ###
	0b00000110, 0b00110000, //      ##   ##
	0b00001110, 0b10111000, //     ### # ###
	0b00001100, 0b10011000, //     ##  #  ##
	0b00011100, 0b10011100, //    ###  #  ###
	0b00011000, 0b10001100, //    ##   #   ##
	0b00111000, 0b00001110, //   ###       ###
	0b00110000, 0b10000110, //   ##    #    ##
	0b01111111, 0b11111111, //  ###############
	0b01111111, 0b11111111, //  ###############
	0b00000000, 0b00000000, //
};
 unsigned char plus_icon16x16[] =
{
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000001, 0b10000000, //        ##
	0b00000001, 0b10000000, //        ##
	0b00000001, 0b10000000, //        ##
	0b00000001, 0b10000000, //        ##
	0b00011111, 0b11111000, //    ##########
	0b00011111, 0b11111000, //    ##########
	0b00000001, 0b10000000, //        ##
	0b00000001, 0b10000000, //        ##
	0b00000001, 0b10000000, //        ##
	0b00000001, 0b10000000, //        ##
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
};
 unsigned char minus_icon16x16[] =
{
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00011111, 0b11111000, //    ##########
	0b00011111, 0b11111000, //    ##########
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
};
 unsigned char mobile_icon16x16[] =
{
	0b00000000, 0b00000000, //
	0b00000000, 0b00110000, //           ##
	0b00000000, 0b00110000, //           ##
	0b00001111, 0b11111000, //     #########
	0b00001111, 0b11111000, //     #########
	0b00001100, 0b00011000, //     ##     ##
	0b00001100, 0b00011000, //     ##     ##
	0b00001100, 0b00011000, //     ##     ##
	0b00001100, 0b00011000, //     ##     ##
	0b00001111, 0b11111000, //     #########
	0b00001111, 0b11111000, //     #########
	0b00001111, 0b11111000, //     #########
	0b00001111, 0b11111000, //     #########
	0b00001111, 0b11111000, //     #########
	0b00001111, 0b11111000, //     #########
	0b00001111, 0b11111000, //     #########
};
 unsigned char signal1_icon16x16[] =
{
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b01000000, 0b00000000, //  #
	0b11000000, 0b00000000, // ##
	0b11000000, 0b00000000, // ##
};
 unsigned char signal2_icon16x16[] =
{
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000100, 0b00000000, //      #
	0b00001100, 0b00000000, //     ##
	0b00011100, 0b00000000, //    ###
	0b00011100, 0b00000000, //    ###
	0b01011100, 0b00000000, //  # ###
	0b11011100, 0b00000000, // ## ###
	0b11011100, 0b00000000, // ## ###
};
 unsigned char signal3_icon16x16[] =
{
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //
	0b00000000, 0b01000000, //          #
	0b00000000, 0b11000000, //         ##
	0b00000001, 0b11000000, //        ###
	0b00000001, 0b11000000, //        ###
	0b00000101, 0b11000000, //      # ###
	0b00001101, 0b11000000, //     ## ###
	0b00011101, 0b11000000, //    ### ###
	0b00011101, 0b11000000, //    ### ###
	0b01011101, 0b11000000, //  # ### ###
	0b11011101, 0b11000000, // ## ### ###
	0b11011101, 0b11000000, // ## ### ###
};
 unsigned char signal4_icon16x16[] =
{
	0b00000000, 0b00000000, //
	0b00000000, 0b00000100, //              #
	0b00000000, 0b00001100, //             ##
	0b00000000, 0b00011100, //            ###
	0b00000000, 0b00011100, //            ###
	0b00000000, 0b01011100, //          # ###
	0b00000000, 0b11011100, //         ## ###
	0b00000001, 0b11011100, //        ### ###
	0b00000001, 0b11011100, //        ### ###
	0b00000101, 0b11011100, //      # ### ###
	0b00001101, 0b11011100, //     ## ### ###
	0b00011101, 0b11011100, //    ### ### ###
	0b00011101, 0b11011100, //    ### ### ###
	0b01011101, 0b11011100, //  # ### ### ###
	0b11011101, 0b11011100, // ## ### ### ###
	0b11011101, 0b11011100, // ## ### ### ###
};





*/

