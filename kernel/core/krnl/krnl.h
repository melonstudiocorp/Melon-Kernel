#pragma once

// #########################################
// ========== SCREEN FUNCTIONS =============

/**
 * @brief Clear the screen (all lines).
 * 
 * Call this function from your main file.
 */
void clearline();

/**
 * @brief Print text on the screen.
 * 
 * @param msg Message string to print
 */
void outline(char *msg);

/**
 * @brief Delay execution.
 * 
 * @param count Delay value (the higher, the longer)
 */
void delay(int count);

// #########################################
// ========== UTILITY FUNCTIONS ============

/**
 * @brief Generate pseudo-random number.
 * 
 * Used in games.c for StarFall.
 */
uint32_t rand();

/**
 * @brief Compare two strings.
 * 
 * @param a First string
 * @param b Second string
 * @return int 0 if equal, nonzero otherwise
 */
int strcmp(const char *a, const char *b);

/**
 * @brief Get string length.
 * 
 * @param s Input string
 * @return int Length of the string
 */
int strlen(const char *s);

/**
 * @brief Copy string.
 * 
 * @param dest Destination buffer
 * @param src Source string
 */
void strcpy(char *dest, const char *src);

// NOTE: string.h is not supported in freestanding environment

// #########################################
// ========== KEYBOARD =====================

/**
 * @brief Get pressed key code from keyboard.
 * 
 * @return uint8_t Scancode of pressed key
 */
uint8_t get_key();

/**
 * @brief Convert keyboard scancode to ASCII.
 * 
 * @param code Keyboard scancode
 * @return char ASCII character
 */
char scancode_to_ascii(uint8_t code);

// #########################################
// ========== INPUT/OUTPUT =================

/**
 * @brief Read a line of input from keyboard.
 * 
 * @param buffer Buffer to store input
 * @param max_len Maximum length to read
 */
void readline(char *buffer, int max_len);

/**
 * @brief Write byte to port.
 * 
 * @param port Port address
 * @return uint8_t Read value
 */
static inline uint8_t inb(uint16_t port);

/**
 * @brief Print message (like echo command).
 * 
 * @param msg Message string
 */
void echo(char *msg);

// #########################################
// ========== SYSTEM =======================

/**
 * @brief Reboot the system via reboot command.
 */
void reboot();