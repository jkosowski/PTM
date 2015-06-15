/**
 *  Defines for your entire project at one place
 * 
 *	@author 	Tilen Majerle
 *	@email		tilen@majerle.eu
 *	@website	http://stm32f4-discovery.com
 *	@version 	v1.0
 *	@ide		Keil uVision 5
 *	@license	GNU GPL v3
 *	
 * |----------------------------------------------------------------------
 * | Copyright (C) Tilen Majerle, 2014
 * | 
 * | This program is free software: you can redistribute it and/or modify
 * | it under the terms of the GNU General Public License as published by
 * | the Free Software Foundation, either version 3 of the License, or
 * | any later version.
 * |  
 * | This program is distributed in the hope that it will be useful,
 * | but WITHOUT ANY WARRANTY; without even the implied warranty of
 * | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * | GNU General Public License for more details.
 * | 
 * | You should have received a copy of the GNU General Public License
 * | along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * |----------------------------------------------------------------------
 */
#ifndef TM_DEFINES_H
#define TM_DEFINES_H

/* Put your global defines for all libraries here used in your project */

//RS - Register select pin
#define TM_HD44780_RS_PORT		GPIOE
#define TM_HD44780_RS_PIN		GPIO_PIN_4
//E - Enable pin
#define TM_HD44780_E_PORT		GPIOE
#define TM_HD44780_E_PIN		GPIO_PIN_5
//D4 - Data 4 pin
#define TM_HD44780_D4_PORT		GPIOE
#define TM_HD44780_D4_PIN		GPIO_PIN_0
//D5 - Data 5 pin
#define TM_HD44780_D5_PORT		GPIOE
#define TM_HD44780_D5_PIN		GPIO_PIN_1
//D6 - Data 6 pin
#define TM_HD44780_D6_PORT		GPIOE
#define TM_HD44780_D6_PIN		GPIO_PIN_2
//D7 - Data 7 pin
#define TM_HD44780_D7_PORT		GPIOE
#define TM_HD44780_D7_PIN		GPIO_PIN_3

/* Number of maximal supported buttons */
#ifndef BUTTON_MAX_BUTTONS
#define BUTTON_MAX_BUTTONS        1
#endif

/* Number of milliseconds for normal press detection */
#ifndef BUTTON_NORMAL_PRESS_TIME
#define BUTTON_NORMAL_PRESS_TIME  100
#endif

/* Number of milliseconds for long press detection */
#ifndef BUTTON_LONG_PRESS_TIME
#define BUTTON_LONG_PRESS_TIME   3000
#endif

#endif
