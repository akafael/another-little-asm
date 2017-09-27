#ifndef YLA_ASSEMBLER_H_
#define YLA_ASSEMBLER_H_

#define DEBUG_ASSEMBLER 0


typedef enum{
    SECTION_NONE = 0,
    SECTION_TEXT = 1,
    SECTION_DATA = 2
} SectionMode;

/**
 * Montador
 *
 * @author Rafael e João Pedro Franch
 */
int assembler(int argc, char * argv[]);

#endif
