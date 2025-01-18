/*
 * H7SEG_config.h
 *
 *  Created on: Dec 6, 2024
 *      Author: Ola Saadeh
 */

#ifndef H7SEG_CONFIG_H_
#define H7SEG_CONFIG_H_

// Define the starting pin and port for segments (a to g)
#define SEGMENT_PORT PORTB
#define SEGMENT_START_PIN PIN2

// Define the control pins for enabling 7-Segment
#define SEGMENT_ENABLE_PORT PORTB
#define SEGMENT_ENABLE_PIN_1 PIN9
#define SEGMENT_ENABLE_PIN_2 PIN10

/*
 * options :choose displayType
 * 1- COMMON_CATHODE
 * 2- COMMON_ANODE
 * */
#define DISPLAYTYPE COMMON_CATHODE


#endif /* H7SEG_CONFIG_H_ */
