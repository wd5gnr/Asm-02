/*
 *******************************************************************
 *** This software is copyright 2021 by Michael H Riley          ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/
#define MAIN

#include <time.h>
//moved sys/time.h to header.h

#include "header.h"

typedef struct {
  char opcode[8];
  byte typ;
  byte byte1;
  } OPCODE;

#define OT_0ARG    0
#define OT_1ARG    1
#define OT_LBR     2
#define OT_DB      3
#define OT_DS      4
#define OT_NARG    5
#define OT_EQU     6
#define OT_ORG     7
#define OT_680ARG  8
#define OT_681ARG  9
#define OT_68NARG 10
#define OT_682ARG 11
#define OT_END    12
#define OT_SBR    13
#define OT_MACRO  19
#define OT_PUBLIC 20
#define OT_EXTRN  21
#define OT_PROC   22
#define OT_ENDP   23
#define OT_VER    24
#define OT_EVER   25
#define OT_EEVER  26
#define OT_DF     27

#define OP_LOW  0x94
#define OP_HIGH 0x93
#define OP_SGN  0x92
#define OP_ABS  0x91
#define OP_DOT  0x80
#define OP_MUL  0x70
#define OP_DIV  0x71
#define OP_MOD  0x72
#define OP_ADD  0x60
#define OP_SUB  0x61
#define OP_SHR  0x50
#define OP_SHL  0x51
#define OP_AND  0x40
#define OP_OR   0x41
#define OP_XOR  0x42
#define OP_NOT  0x43
#define OP_EQ   0x30
#define OP_NE   0x31
#define OP_LT   0x32
#define OP_GT   0x33
#define OP_LTE  0x34
#define OP_GTE  0x35
#define OP_LAND 0x20
#define OP_LOR  0x21
#define OP_CP   0x10
#define OP_OP   0x02
#define OP_END  0x01
#define OP_NUM  0x00

OPCODE opcodes[] = {
  { "adc",   OT_0ARG,   ADC   },
  { "adci",  OT_1ARG,   ADCI  },
  { "add",   OT_0ARG,   ADD   },
  { "adi",   OT_1ARG,   ADI   },
  { "and",   OT_0ARG,   AND   },
  { "ani",   OT_1ARG,   ANI   },
  { "b1",    OT_SBR,    B1    },
  { "b2",    OT_SBR,    B2    },
  { "b3",    OT_SBR,    B3    },
  { "b4",    OT_SBR,    B4    },
  { "bdf",   OT_SBR,    BDF   },
  { "bge",   OT_SBR,    BDF   },
  { "bpz",   OT_SBR,    BDF   },
  { "bn1",   OT_SBR,    BN1   },
  { "bn2",   OT_SBR,    BN2   },
  { "bn3",   OT_SBR,    BN3   },
  { "bn4",   OT_SBR,    BN4   },
  { "bnf",   OT_SBR,    BNF   },
  { "bl",    OT_SBR,    BNF   },
  { "bm",    OT_SBR,    BNF   },
  { "bnq",   OT_SBR,    BNQ   },
  { "bnz",   OT_SBR,    BNZ   },
  { "bq",    OT_SBR,    BQ    },
  { "br",    OT_SBR,    BR    },
  { "bz",    OT_SBR,    BZ    },
  { "db",    OT_DB,     'B'   },
  { "df",    OT_DF,     0     },
  { "dw",    OT_DB,     'W'   },
  { "dd",    OT_DB,     'D'   },
  { "ds",    OT_DS,     0     },
  { "dec",   OT_NARG,   DEC   },
  { "dis",   OT_0ARG,   DIS   },
  { "equ",   OT_EQU,    0     },
  { "ghi",   OT_NARG,   GHI   },
  { "glo",   OT_NARG,   GLO   },
  { "idl",   OT_0ARG,   IDL   },
  { "inc",   OT_NARG,   INC   },
  { "inp",   OT_NARG,   INP   },
  { "irx",   OT_0ARG,   IRX   },
  { "lda",   OT_NARG,   LDA   },
  { "lbdf",  OT_LBR,    LBDF  },
  { "lbnf",  OT_LBR,    LBNF  },
  { "lbnq",  OT_LBR,    LBNQ  },
  { "lbnz",  OT_LBR,    LBNZ  },
  { "lbq",   OT_LBR,    LBQ   },
  { "lbr",   OT_LBR,    LBR   },
  { "lbz",   OT_LBR,    LBZ   },
  { "ldi",   OT_1ARG,   LDI   },
  { "ldn",   OT_NARG,   LDN   },
  { "ldx",   OT_0ARG,   LDX   },
  { "ldxa",  OT_0ARG,   LDXA  },
  { "lsdf",  OT_0ARG,   LSDF  },
  { "lsie",  OT_0ARG,   LSIE  },
  { "lskp",  OT_0ARG,   NLBR  },
  { "lsnf",  OT_0ARG,   LSNF  },
  { "lsnq",  OT_0ARG,   LSNQ  },
  { "lsnz",  OT_0ARG,   LSNZ  },
  { "lsq",   OT_0ARG,   LSQ   },
  { "lsz",   OT_0ARG,   LSZ   },
  { "mark",  OT_0ARG,   MARK  },
  { "nbr",   OT_0ARG,   NBR   },
  { "nlbr",  OT_0ARG,   NLBR  },
  { "nop",   OT_0ARG,   NOP   },
  { "or",    OT_0ARG,   OR    },
  { "ori",   OT_1ARG,   ORI   },
  { "out",   OT_NARG,   OUT   },
  { "phi",   OT_NARG,   PHI   },
  { "plo",   OT_NARG,   PLO   },
  { "req",   OT_0ARG,   REQ   },
  { "ret",   OT_0ARG,   RET   },
  { "sav",   OT_0ARG,   SAV   },
  { "sd",    OT_0ARG,   SD    },
  { "sdb",   OT_0ARG,   SDB   },
  { "sdi",   OT_1ARG,   SDI   },
  { "sdbi",  OT_1ARG,   SDBI  },
  { "sep",   OT_NARG,   SEP   },
  { "seq",   OT_0ARG,   SEQ   },
  { "sex",   OT_NARG,   SEX   },
  { "shl",   OT_0ARG,   SHL   },
  { "shlc",  OT_0ARG,   SHLC  },
  { "rshl",  OT_0ARG,   SHLC  },
  { "shr",   OT_0ARG,   SHR   },
  { "shrc",  OT_0ARG,   SHRC  },
  { "rshr",  OT_0ARG,   SHRC  },
  { "skp",   OT_0ARG,   NBR   },
  { "sm",    OT_0ARG,   SM    },
  { "smb",   OT_0ARG,   SMB   },
  { "smbi",  OT_1ARG,   SMBI  },
  { "smi",   OT_1ARG,   SMI   },
  { "str",   OT_NARG,   STR   },
  { "stxd",  OT_0ARG,   STXD  },
  { "xor",   OT_0ARG,   XOR   },
  { "xri",   OT_1ARG,   XRI   },
  { "org",   OT_ORG,    0     },
  { "rldi",  OT_68NARG, 0xc0  },
  { "rlxa",  OT_68NARG, 0x60  },
  { "rsxd",  OT_68NARG, 0xa0  },
  { "dbnz",  OT_682ARG, 0x20  },
  { "rnx",   OT_68NARG, 0xb0  },
  { "dadd",  OT_680ARG, 0xf4  },
  { "dadi",  OT_681ARG, 0xfc  },
  { "dadc",  OT_680ARG, 0x74  },
  { "daci",  OT_681ARG, 0x7c  },
  { "dsm",   OT_680ARG, 0xf7  },
  { "dsmi",  OT_681ARG, 0xff  },
  { "dsmb",  OT_680ARG, 0x77  },
  { "dsbi",  OT_681ARG, 0x7f  },
  { "bci",   OT_681ARG, 0x3e  },
  { "bxi",   OT_681ARG, 0x3f  },
  { "ldc",   OT_680ARG, 0x06  },
  { "gec",   OT_680ARG, 0x08  },
  { "stpc",  OT_680ARG, 0x00  },
  { "dtc",   OT_680ARG, 0x01  },
  { "stm",   OT_680ARG, 0x07  },
  { "scm1",  OT_680ARG, 0x05  },
  { "scm2",  OT_680ARG, 0x03  },
  { "spm1",  OT_680ARG, 0x04  },
  { "spm2",  OT_680ARG, 0x02  },
  { "etq",   OT_680ARG, 0x09  },
  { "xie",   OT_680ARG, 0x0a  },
  { "xid",   OT_680ARG, 0x0b  },
  { "cie",   OT_680ARG, 0x0c  },
  { "cid",   OT_680ARG, 0x0d  },
  { "dsav",  OT_680ARG, 0x76  },
  { "scal",  OT_682ARG, 0x80  },
  { "sret",  OT_680ARG, 0x90  },
  { "end",   OT_END,    0x00  },
  { "public",OT_PUBLIC, 0x00  },
  { "extrn", OT_EXTRN,  0x00  },
  { "proc",  OT_PROC,   0x00  },
  { "endp",  OT_ENDP,   0x00  },
  { "ver",   OT_VER,    0x00  },
  { "ever",  OT_EVER,   0x00  },
  { "eever", OT_EEVER,  0x00  },
  { "",      0,         0     },
  };

char sourceLine[1024];
word lstCount;

void list(char* message) {
  if (passNumber != 2) return;
  if (showList != 0) printf("%s",message);
  if ( createLst != 0) fprintf(lstFile, "%s",message);
  }

char* lineNo() {
  static char buffer[10];
  if (fileNumber == 0) sprintf(buffer, "[%05d]",lineNumber[fileNumber]);
    else sprintf(buffer, "<%05d>",lineNumber[fileNumber]);
  return buffer;
  }

char* trim(char* line) {
  while (*line == ' ' || *line == '\t') line++;
  return line;
  }

char* strip(char* line) {
  char* pchar;
  int quoted = 0;
  while (*line == ' ' || *line == '\t') line++;
  for (pchar = line; *pchar != 0; pchar++) {
    if (*pchar == '\'' || *pchar == '"') {
      quoted = !quoted;
      }
    else if (*pchar == ';' && !quoted) {
        *pchar++ = ' ';
        *pchar = '\0';
        break;
      }
    }
    return line;
  }

int isAlpha(char c) {
  if (c >= 'a' && c <= 'z') return -1;
  if (c >= 'A' && c <= 'Z') return -1;
  if (c >= '0' && c <= '9') return -1;
  if (c >= '_') return -1;
  return 0;
  }

int isRReg(char* line) {
  if (*line != 'r' && *line != 'R') return 0;
  line++;
  if ((*line >= '2' && *line <= '9') ||
      (*line >= 'a' && *line <= 'f') ||
      (*line >= 'A' && *line <= 'F')) {
    line++;
    if (*line >= '0' && *line <= '9') return 0;
    if (*line >= 'a' && *line <= 'z') return 0;
    if (*line >= 'A' && *line <= 'Z') return 0;
    return -1;
    }
  if (*line == '1') {
    line++;
    if (*line >= '0' && *line <= '5') {
      line++;
      if (*line >= '0' && *line <= '9') return 0;
      if (*line >= 'a' && *line <= 'z') return 0;
      if (*line >= 'A' && *line <= 'Z') return 0;
      return -1;
      }
    if (*line >= '0' && *line <= '9') return 0;
    if (*line >= 'a' && *line <= 'z') return 0;
    if (*line >= 'A' && *line <= 'Z') return 0;
    return -1;
    }
  return 0;
  }

void addLabel(char* label, word value) {
  int i;
  if (passNumber == 2) return;
  for (i=0; i<numLabels; i++)
    if (strcasecmp(label, labels[i]) == 0 &&
        strcasecmp(module, labelProcs[i]) == 0) {
      printf("***ERROR: Duplicate label: %s\n",label);
      printf("          %s\n",sourceLine);
      errors++;
      return;
      }
  numLabels++;
  if (numLabels == 1) {
    labels = (char**)malloc(sizeof(char*));
    labelValues = (word*)malloc(sizeof(word));
    labelProcs = (char**)malloc(sizeof(char*));
    }
  else {
    labels = (char**)realloc(labels, sizeof(char*) * numLabels);
    labelValues = (word*)realloc(labelValues, sizeof(word) * numLabels);
    labelProcs = (char**)realloc(labelProcs, sizeof(char*) * numLabels);
    }
  labels[numLabels-1] = (char*)malloc(strlen(label) + 1);
  strcpy(labels[numLabels-1], label);
  labelProcs[numLabels-1] = (char*)malloc(strlen(module) + 1);
  strcpy(labelProcs[numLabels-1], module);
  labelValues[numLabels-1] = value;
  }

word getLabel(char* label) {
  int i;
  if (passNumber == 1) {
    for (i=0; i<numLabels; i++)
      if (strcasecmp(label, labels[i]) == 0 &&
          strcasecmp(module, labelProcs[i]) == 0)
        return labelValues[i];
    for (i=0; i<numLabels; i++)
      if (strcasecmp(label, labels[i]) == 0 &&
          (strcasecmp("*", labelProcs[i]) == 0 ||
           strcasecmp(" ", labelProcs[i]) == 0))
        return labelValues[i];
    return 0;
    }
  for (i=0; i<numLabels; i++)
    if (strcasecmp(label, labels[i]) == 0 &&
        strcasecmp(module, labelProcs[i]) == 0)
      return labelValues[i];
  for (i=0; i<numLabels; i++)
    if (strcasecmp(label, labels[i]) == 0 &&
        (strcasecmp(" ", labelProcs[i]) == 0 ||
         strcasecmp("*", labelProcs[i]) == 0))
      return labelValues[i];
  printf("***ERROR: Label not found: %s\n",label);
  printf("%s\n",sourceLine);
  errors++;
  return 0;
  }

int findLabel(char* label) {
  int i;
  if (passNumber == 1) {
    for (i=0; i<numLabels; i++)
      if (strcasecmp(label, labels[i]) == 0 &&
          strcasecmp(module, labelProcs[i]) == 0) {
        return i;
        }
    for (i=0; i<numLabels; i++)
      if (strcasecmp(label, labels[i]) == 0 &&
          (strcasecmp(" ", labelProcs[i]) == 0 ||
           strcasecmp("*", labelProcs[i]) == 0)) {
        return i;
        }
    return 0;
    }
  for (i=0; i<numLabels; i++)
    if (strcasecmp(label, labels[i]) == 0 &&
          strcasecmp(module, labelProcs[i]) == 0) {
      return i;
      }
  for (i=0; i<numLabels; i++)
    if (strcasecmp(label, labels[i]) == 0 &&
          (strcasecmp(" ", labelProcs[i]) == 0 ||
           strcasecmp("*", labelProcs[i]) == 0)) {
      return i;
      }
  printf("***ERROR: Label not found: %s\n",label);
  printf("%s\n",sourceLine);
  errors++;
  return -1;
  }

void setLabel(char* label, word value) {
  int i;
  for (i=0; i<numLabels; i++)
    if (strcasecmp(label, labels[i]) == 0) {
      labelValues[i] = value;
      return;
      }
  printf("***ERROR: Label not found: %s\n",label);
  errors++;
  }

int isExternal(int v) {
  int i;
  for (i=0; i<numExternals; i++)
    if (externals[i] == v) return v;
  return -1;
  }

void writeOutput() {
  int i;
  byte checksum;
  char outLine[80];
  char temp[16];
  if (outMode == 'R') {
    sprintf(outLine,":%04x",outAddress);
    for (i=0; i<outCount; i++) {
      sprintf(temp," %02x",outBuffer[i]);
      strcat(outLine,temp);
      }
    sprintf(temp,"%s",lineEnding);
    strcat(outLine,temp);
    write(outFile, outLine, strlen(outLine));
    }
  if (outMode == 'I') {
    checksum = outCount;
    sprintf(outLine,":%02x",outCount);
    checksum += (outAddress / 256);
    checksum += (outAddress & 0xff);
    sprintf(temp,"%04x00",outAddress);
    strcat(outLine,temp);
    for (i=0; i<outCount; i++) {
      checksum += outBuffer[i];
      sprintf(temp,"%02x",outBuffer[i]);
      strcat(outLine,temp);
      }
    checksum = (checksum ^ 0xff) + 1;
    sprintf(temp,"%02x",checksum);
    strcat(outLine, temp);
    sprintf(temp,"%s",lineEnding);
    strcat(outLine,temp);
    write(outFile, outLine, strlen(outLine));
    }
  if (outMode == 'B') {
//    write(outFile, outBuffer, outCount);
    }
  }

void output(byte value) {
  char tmp[4];
  if (compMode == 'A' && (address < ramStart || address > ramEnd)) {
    printf("***ERROR: Address exceeded available RAM");
    errors++;
    }
  if (compMode == 'O' && (address < romStart || address > romEnd)) {
    printf("***ERROR: Address exceeded available ROM");
    errors++;
    }
  if (passNumber == 1) {
    if (address > highest) highest = address;
    }
  if (passNumber == 2) {
    codeGenerated++;
    if (outMode == 'B') {
      if (address < lowAddress) lowAddress = address;
      if (address > highAddress) highAddress = address;
      memory[address] = value;
      }
    else {
      if (suppression == 0) {
        outBuffer[outCount++] = value;
        if (outCount == 16) {
          writeOutput();
          outCount = 0;
          outAddress = address+1;
          }
        }
      }
    if (createLst != 0 || showList != 0) {
      if (lstCount == 4) {
        strcat(listLine, sourceLine);
        strcat(listLine, "\n");
        list(listLine);
        strcpy(listLine,"              ");
        }
      else if (lstCount > 4 && (lstCount % 4) == 0) {
        strcat(listLine, "\n");
        list(listLine);
        strcpy(listLine,"              ");
        }
      sprintf(tmp, "%02x ", value);
      strcat(listLine, tmp);
      lstCount++;
      }
    }
  address++;
  }

char* asm_convertNumber(char* buffer, dword* value, byte* success) {
  byte ishex;
  byte neg;
  dword val1,val2;
  ishex = 0;
  val1 = 0;
  val2 = 0;
  neg = 0;
  if (*buffer == '\'' && *(buffer+2) == '\'') {
    buffer++;
    *value = *buffer;
    buffer += 2;
    *success = 0xff;
    return buffer;
    }
  if (*buffer == '"' && *(buffer+2) == '"') {
    buffer++;
    *value = *buffer;
    buffer += 2;
    *success = 0xff;
    return buffer;
    }
  if (*buffer == '%') {
    buffer++;
    while (*buffer == '1' || *buffer == '0' || *buffer == '_') {
      if (*buffer != '_')
        val1 = (val1 << 1) | (*buffer - '0');
      buffer++;
      }
    *value = val1;
    *success = 0xff;
    return buffer;
    }
  if (*buffer == '$') {
    buffer++;
    if ((*buffer >= '0' && *buffer <= '9') ||
        (*buffer >= 'a' && *buffer <= 'f') ||
        (*buffer >= 'A' && *buffer <= 'F'))
      ishex = 0xff;
    else {
      *value = asmAddress;
      *success = 0xff;
      return buffer;
      }
    }
  if (*buffer == '-' && *(buffer+1) >= '0' && *(buffer+1) <= '9') {
    neg = 0xff;
    buffer++;
    }
  if (ishex == 0 && (*buffer < '0' || *buffer > '9')) {
    *success = 0;
    return buffer;
    }
  while ((*buffer >= '0' && *buffer <= '9') ||
         (*buffer >= 'a' && *buffer <= 'f') ||
         (*buffer >= 'A' && *buffer <= 'F')) {
      if (*buffer >= '0' && *buffer <= '9') {
        val1 = (val1 * 10) + (*buffer - '0');
        val2 = (val2 << 4) | (*buffer - '0');
        }
      if (*buffer >= 'a' && *buffer <= 'f')
        val2 = (val2 << 4) | (*buffer - 87);
      if (*buffer >= 'A' && *buffer <= 'F')
        val2 = (val2 << 4) | (*buffer - 55);
      buffer++;
    }
  if (*buffer == 'h' || *buffer == 'H') {
    ishex = 0xff;
    buffer++;
    }
  if (neg != 0) {
    val1 = (val1 ^ 0xffff) + 1;
    val2 = (val2 ^ 0xffff) + 1;
    }
  *success = 0xff;
  *value = (ishex != 0) ? val2 : val1;
  return buffer;
  }




char* evaluate(char *pos, dword* result) {
  int i;
  int numbers[256];
  byte ops[256];
  int  nstack;
  int  ostack;
  int  op;
  int  flag;
  int  p;
  char term;
  byte success;
  dword number;
  char token[64];
  nstack = 0;
  ostack = 0;
  op = 0;
  usedReference = -1;
  usedLocal = -1;
  while (*pos  != 0 && op != OP_END) {

    flag = -1;
    while (flag) {
      flag = 0;
      if (*pos == '(') {
        ops[ostack++] = OP_OP;
        flag = -1;
        }
      else if (strncasecmp(pos, "abs(", 4) == 0) {
        ops[ostack++] = OP_ABS;
        ops[ostack++] = OP_OP;
        pos += 3;
        flag = -1;
        }
      else if (strncasecmp(pos, "sgn(", 4) == 0) {
        ops[ostack++] = OP_SGN;
        ops[ostack++] = OP_OP;
        pos += 3;
        flag = -1;
        }
      else if (strncasecmp(pos, "high ", 5) == 0) {
        ops[ostack++] = OP_HIGH;
        pos += 3;
        flag = -1;
        }
      else if (strncasecmp(pos, "low ", 4) == 0) {
        ops[ostack++] = OP_LOW;
        pos += 2;
        flag = -1;
        }
      else if (strncasecmp(pos, "[month]", 7) == 0) {
        pos += 6;
        numbers[nstack++] = buildMonth;
        }
      else if (strncasecmp(pos, "[day]", 5) == 0) {
        pos += 4;
        numbers[nstack++] = buildDay;
        }
      else if (strncasecmp(pos, "[year]", 6) == 0) {
        pos += 5;
        numbers[nstack++] = buildYear;
        }
      else if (strncasecmp(pos, "[hour]", 6) == 0) {
        pos += 5;
        numbers[nstack++] = buildHour;
        }
      else if (strncasecmp(pos, "[minute]", 8) == 0) {
        pos += 7;
        numbers[nstack++] = buildMinute;
        }
      else if (strncasecmp(pos, "[second]", 8) == 0) {
        pos += 7;
        numbers[nstack++] = buildSecond;
        }
      else if (strncasecmp(pos, "[build]", 7) == 0) {
        pos += 6;
        numbers[nstack++] = buildNumber;
        }

      else {
        term = 0;
        pos = asm_convertNumber(pos, &number, &success);
        if (success != 0) {
          numbers[nstack++] = number;
          term = -1;
          pos--;
          }

        if (term == 0) {
          if ((*pos >= 'a' && *pos <= 'z') ||
              (*pos >= 'A' && *pos <= 'Z')) {
            p = 0;
            while ((*pos >= 'a' && *pos <= 'z') ||
                   (*pos >= 'A' && *pos <= 'Z') ||
                   (*pos >= '0' && *pos <= '9') ||
                    *pos == '_' || *pos == '!') {
              token[p++] = *pos++;
              }
            token[p] = 0;
            numbers[nstack++] = getLabel(token);
            term = -1;
            pos--;
            i = findLabel(token);
            if (i >= 0) {
              usedReference = isExternal(i);
              if (usedReference >= 0) {
                referenceType = 'W';
                referenceLowOffset = labelValues[i] & 0xff;
                }
              else if (inProc != 0 && strcasecmp(labelProcs[i],module) == 0) {
                 usedLocal = 1;
                 referenceType = 'W';
                 referenceLowOffset = labelValues[i] & 0xff;
                 }
              }
            }
          }
        if (term == 0) {
          printf("Non-number found\n");
          printf("  %s\n",sourceLine);
          return 0;
          }
        }

      if (*pos != 0) pos++;
      pos = trim(pos);
      }
    flag = -1;
    while (flag) {
      flag = 0;
      op = 0;
      switch (*pos) {
        case 0  : op = OP_END; break;
        case ',': op = OP_END; break;
        case '.': op = OP_DOT; break;
        case '*': op = OP_MUL; break;
        case '/': op = OP_DIV; break;
        case '%': op = OP_MOD; break;
        case '+': op = OP_ADD; break;
        case '-': op = OP_SUB; break;
        case '^': op = OP_XOR; break;
        case ')': op = OP_CP ; break;
        case '&':
             if (*(pos+1) == '&') { op = OP_LAND; pos++; }
               else op = OP_AND;
             break;
        case '|':
             if (*(pos+1) == '|') { op = OP_LOR; pos++; }
               else op = OP_OR;
             break;
        case '=':
             if (*(pos+1) == '=') { op = OP_EQ; pos++; }
               else op = OP_EQ;
             break;
        case '!':
             if (*(pos+1) == '=') { op = OP_NE; pos++; }
             else op = OP_NOT;
             break;
        case '<':
             if (*(pos+1) == '<') { op = OP_SHL; pos++; }
             else if (*(pos+1) == '=') { op = OP_LTE; pos++; }
             else op = OP_LT;
             break;
        case '>':
             if (*(pos+1) == '>') { op = OP_SHR; pos++; }
             else if (*(pos+1) == '=') { op = OP_GTE; pos++; }
             else op = OP_GT;
             break;
        }
      if (op == 0) { printf("Invalid OP %c (%02x)\n",*pos, *pos); return 0; }
      while (ostack > 0 && (ops[ostack-1] & 0xf0) >= (op & 0xf0)) {
        nstack--;
        ostack--;
        switch (ops[ostack]) {
          case OP_MUL : numbers[nstack-1] *= numbers[nstack]; break;
          case OP_DIV : numbers[nstack-1] /= numbers[nstack]; break;
          case OP_MOD : numbers[nstack-1] %= numbers[nstack]; break;
          case OP_ADD : numbers[nstack-1] += numbers[nstack]; break;
          case OP_SUB : numbers[nstack-1] -= numbers[nstack]; break;
          case OP_SHL : numbers[nstack-1] <<= numbers[nstack]; break;
          case OP_SHR : numbers[nstack-1] >>= numbers[nstack]; break;
          case OP_AND : numbers[nstack-1] &= numbers[nstack]; break;
          case OP_OR  : numbers[nstack-1] |= numbers[nstack]; break;
          case OP_NOT : numbers[nstack] = !numbers[nstack]; break;
          case OP_LAND: numbers[nstack-1] &= numbers[nstack]; break;
          case OP_LOR : numbers[nstack-1] |= numbers[nstack]; break;
          case OP_XOR : numbers[nstack-1] ^= numbers[nstack]; break;
          case OP_EQ  : numbers[nstack-1] = (numbers[nstack-1] == numbers[nstack]); break;
          case OP_NE  : numbers[nstack-1] = (numbers[nstack-1] != numbers[nstack]); break;
          case OP_LT  : numbers[nstack-1] = (numbers[nstack-1] <  numbers[nstack]); break;
          case OP_GT  : numbers[nstack-1] = (numbers[nstack-1] >  numbers[nstack]); break;
          case OP_LTE : numbers[nstack-1] = (numbers[nstack-1] <= numbers[nstack]); break;
          case OP_GTE : numbers[nstack-1] = (numbers[nstack-1] >= numbers[nstack]); break;
          case OP_ABS : numbers[nstack]   = abs(numbers[nstack]); break;
          case OP_HIGH:
               numbers[nstack]   = (numbers[nstack] >> 8) & 0xff;
               referenceType = 'H';
               break;
          case OP_LOW :
               numbers[nstack]   = numbers[nstack] & 0xff;
               referenceType = 'L';
               break;
          case OP_DOT :
               if (numbers[nstack] & 1) {
                 numbers[nstack-1] = (numbers[nstack-1] >> 8) & 0xff;
                 referenceType = 'H';
                 }
               else {
                 numbers[nstack-1] = numbers[nstack-1] & 0xff;
                 referenceType = 'L';
                 }
               break;
          case OP_SGN:
               if (numbers[nstack] > 0) numbers[nstack] = 1;
               else if (numbers[nstack] < 0) numbers[nstack] = -1;
               else numbers[nstack] = 0;
               break;
          }
        if (ops[ostack] >= 0x90) nstack++;
        }
      if (op != OP_END) {
        if (op == OP_CP) {
          if (usedLocal >= 0 || usedReference >= 0) 
            referenceLowOffset = numbers[nstack-1] & 0xff;
          if (ops[ostack-1] != OP_OP) {
            printf("Expression error, ) without (\n");
            return 0;
            }
          ostack--;
          flag = -1;
          }
        else
          ops[ostack++] = op;
        pos++;
        while (*pos == ' ') pos++;
        pos = trim(pos);
        }
      }
    }
  if (nstack == 0) { printf("nstack empty\n"); return pos; }
  if (nstack != 1) {
     printf("Did not reduce to 1 term: %d\n",nstack);
     return pos;
     }
  *result = numbers[0];
  return pos;
  }

dword processArgs(char* args) {
  dword result;
  args = evaluate(args, &result);
  return result;
  }

void processDb(char* args,char typ) {
  dword num;
  char buffer[256];
  args = trim(args);
  while (*args != 0) {
    if (*args == '\'' && *(args+2) != '\'') {
      args++;
      while (*args != 0 && *args != '\'')
        output(*args++);
      if (*args == '\'') args++;
      }
    else if (*args == '"' && *(args+2) != '"') {
      args++;
      while (*args != 0 && *args != '"')
        output(*args++);
      if (*args == '"') args++;
      }
    else if (*args == '{') {
      args++;
      while (*args != 0 && *args != '{')
        output(*args++);
      if (*args == '{') args++;
      }
    else {
      args = evaluate(args, &num);
      if (typ == 'B') {
        if (passNumber == 2 && usedReference >= 0) {
          if (referenceType == 'W' || referenceType == 'L')
            sprintf(buffer,"\\%s %04x\n",labels[usedReference],address);
          else
            sprintf(buffer,"/%s %04x\n",labels[usedReference],address);
          write(outFile, buffer, strlen(buffer));
          }
        if (passNumber == 2 && usedLocal >= 0) {
          fixups[numFixups] = address;
          fixupTypes[numFixups] = referenceType;
          if (referenceType == 'H')
            fixupLowOffset[numFixups] = referenceLowOffset;
          else
            fixupLowOffset[numFixups] = 0;
          numFixups++;
          }
        output(num & 0xff);
        }
      else if (typ == 'W') {
        if (passNumber == 2 && usedReference >= 0) {
          sprintf(buffer,"?%s %04x\n",labels[usedReference],address);
          write(outFile, buffer, strlen(buffer));
          }
        if (passNumber == 2 && usedLocal >= 0) {
          fixups[numFixups] = address;
          fixupTypes[numFixups] = 'W';
          numFixups++;
          }
        output(((num & 0x0000FF00) >> 8) & 0xff);
        output(num & 0xff);
        }
      else {
        output(((num & 0xff000000) >> 24) & 0xff);
        output(((num & 0x00ff0000) >> 16) & 0xff);
        output(((num & 0x0000FF00) >> 8) & 0xff);
        output(num & 0xff);
        }
      }
    args = trim(args);
    if (*args == ',') {
      args++;
      args = trim(args);
      }
    }
  }

void processDf(char* args) {
  dword num;
  char buffer[256];
  int  pos;
  FTOI ftoi;
  args = trim(args);
  while (*args != 0) {
    pos = 0;
    while (*args > ' ' && *args != ',' && *args != ';') {
      buffer[pos++] = *args++;
      }
    buffer[pos] = 0;
    ftoi.f = atof(buffer);
    num = ftoi.i;
    output(((num & 0xff000000) >> 24) & 0xff);
    output(((num & 0x00ff0000) >> 16) & 0xff);
    output(((num & 0x0000FF00) >> 8) & 0xff);
    output(num & 0xff);
    args = trim(args);
    if (*args == ',') {
      args++;
      args = trim(args);
      }
    }
  }

void processDs(word arg) {
  address += arg;
  if (passNumber == 2 && outCount > 0) {
    writeOutput();
    }
  if (passNumber == 2) {
    sprintf(buffer,">%04x\n",arg);
    write(outFile, buffer, strlen(buffer));
    }
  outAddress = address;
  outCount = 0;
  }

void processOrg(word arg) {
  if (passNumber == 2 && outCount > 0) writeOutput();
  outCount = 0;
  address = arg;
  outAddress = address;
  }

void compileOp(char* line) {
  char op[32];
  char args[32];
  char trans[1024];
  char *oline;
  int  pos;
  oline = line;
  line = trim(line);
  if (*line != '"') {
    printf("Invalid .op format: %s\n",oline);
    exit(1);
    }
  line++;
  line = trim(line);
  pos = 0;
  while (*line != '"' && *line != 0) {
    if ((*line >= 'a' && *line <= 'z') ||
        (*line >= 'A' && *line <= 'Z') ||
        (*line >= '0' && *line <= '9') ||
         *line == '_') {
      op[pos++] = *line++;
      }
    else {
      printf("Invalid character in opcode name: %s\n",oline);
      exit(1);
      }
    }
  op[pos] = 0;
  if (*line != '"') {
    printf("Invalid .op format: %s\n",oline);
    exit(1);
    }
  line++;
  line = trim(line);
  if (*line != ',') {
    printf("Invalid .op format: %s\n",oline);
    exit(1);
    }
  line++;
  line = trim(line);
  if (*line != '"') {
    printf("Invalid .op format: %s\n",oline);
    exit(1);
    }
  line++;
  pos = 0;
  while (*line == 'n' || *line == 'N' ||
         *line == 'b' || *line == 'B' ||
         *line == 'w' || *line == 'W' ||
         *line == 'r' || *line == 'R') {
    args[pos++] = *line++;
    }
  args[pos] = 0;
  if (*line != '"') {
    printf("Invalid .op format: %s\n",oline);
    exit(1);
    }
  line++;
  line = trim(line);
  if (*line != ',') {
    printf("Invalid .op format: %s\n",oline);
    exit(1);
    }
  line++;
  line = trim(line);
  if (*line != '"') {
    printf("Invalid .op format: %s\n",oline);
    exit(1);
    }
  line++;
  pos = 0;
  while (*line != '"' && *line != 0) {
    trans[pos++] = *line++;
    }
  trans[pos] = 0;
  if (*line != '"') {
    printf("Invalid .op format: %s\n",oline);
    exit(1);
    }
  numOps++;
  if (numOps == 1) {
    ops = (char**)malloc(sizeof(char*));
    arglist = (char**)malloc(sizeof(char*));
    translation = (char**)malloc(sizeof(char*));
    }
  else {
    ops = (char**)realloc(ops, sizeof(char*) * numOps);
    arglist = (char**)realloc(arglist, sizeof(char*) * numOps);
    translation = (char**)realloc(translation, sizeof(char*) * numOps);
    }
  ops[numOps-1] = (char*)malloc(strlen(op) + 1);
  strcpy(ops[numOps-1], op);
  arglist[numOps-1] = (char*)malloc(strlen(args) + 1);
  strcpy(arglist[numOps-1], args);
  translation[numOps-1] = (char*)malloc(strlen(trans) + 1);
  strcpy(translation[numOps-1], trans);
  }


// ************************************************************************
// *****                    Start of preprocessor                     *****
// ************************************************************************

void addDefine(char* define, char* value) {
  int i;
  for (i=0; i<numDefines; i++)
    if (strcasecmp(define, defines[i]) == 0) {
      printf("***ERROR: Duplicate define: %s\n",define);
      errors++;
      return;
      }
  numDefines++;
  if (numDefines == 1) {
    defines = (char**)malloc(sizeof(char*));
    defineValues = (char**)malloc(sizeof(char*));
    }
  else {
    defines = (char**)realloc(defines, sizeof(char*) * numDefines);
    defineValues = (char**)realloc(defineValues, sizeof(char*) * numDefines);
    }
  defines[numDefines-1] = (char*)malloc(strlen(define) + 1);
  strcpy(defines[numDefines-1], define);
  defineValues[numDefines-1] = (char*)malloc(strlen(value) + 1);
  strcpy(defineValues[numDefines-1], value);
  }

char* findDefine(char* define) {
  int i;
  for (i=0; i<numDefines; i++)
    if (strcasecmp(define, defines[i]) == 0) {
      return defineValues[i];
      }
  return NULL;
  }

void delDefine(char* define) {
  int pos;
  int i;
  pos = -1;
  for (i=0; i<numDefines; i++)
    if (strcasecmp(define, defines[i]) == 0) pos = i;
  if (pos < 0) return;
  free(defines[pos]);
  free(defineValues[pos]);
  for (i=pos; i<numDefines-1; i++) {
    defines[i] = defines[i+1];
    defineValues[i] = defineValues[i+1];
    }
  numDefines--;
  if (numDefines == 0) {
    free(defines);
    free(defineValues);
    }
  else {
    defines = (char**)realloc(defines, sizeof(char*) * numDefines);
    defineValues = (char**)realloc(defineValues, sizeof(char*) * numDefines);
    }
  }

void defReplace(char* line) {
  char  buffer[1024];
  char *pchar;
  byte  flag;
  int i;
  for (i=0; i<numDefines; i++) {
    flag = 0xff;
    while (flag) {
      pchar = strstr(line, defines[i]);
      if (pchar == NULL) flag = 0;
      else if (isAlpha(*(pchar-1)) != 0 ||
               isAlpha(*(pchar+strlen(defines[i]))) != 0) flag = 0;
      if (flag) {
        strncpy(buffer,line,pchar-line);
        buffer[pchar-line] = 0;
        strcat(buffer,defineValues[i]);
        strcat(buffer,pchar+strlen(defines[i]));
        strcpy(line,buffer);
        }
      }
    }
  }

char* nextLine(char* line) {
  char* ret;
  int   flag;
  char  buffer[1024];
  char  path[2048];
  int   pos;
  char *pchar;
  word  value;
  dword dvalue;
  int   i;
  flag = -1;
  while (flag) {
    ret = fgets(line, 1024, sourceFile[fileNumber]);
    if (ret != NULL) {
      while (strlen(ret) > 0 && line[strlen(ret)-1] <= ' ')
        line[strlen(ret)-1] = 0;
      strcpy(sourceLine, line);
      linesAssembled++;
      lineNumber[fileNumber]++;
      flag = 0;
      ret = trim(ret);
      if (*ret == '#') {

        if (nests[numNests] != 'I') {

          if (nests[numNests] == 'Y') {

            if (strncmp(ret,"#include ",9) == 0) {
              ret += 9;
              while (*ret == ' ' || *ret == '\t') ret++;
              pos = 0;
              while (*ret != 0 && *ret > ' ')
                buffer[pos++] = *ret++;
              buffer[pos] = 0;
              fileNumber++;
              lineNumber[fileNumber] = 0;
              sourceFile[fileNumber] = fopen(buffer,"r");
              if (sourceFile[fileNumber] == NULL) {
                i = 0;
                while (i < numIncPath) {
                  strcpy(path, incPath[i]);
                  if (path[strlen(path)-1] != '/') strcat(path,"/");
                  strcat(path, buffer);
                  sourceFile[fileNumber] = fopen(path, "r");
                  if (sourceFile[fileNumber] != NULL) i = numIncPath;
                  i++;
                  }
                if (sourceFile[fileNumber] == NULL) {
                  printf("***ERROR: Could not open: %s\n",buffer);
                  fileNumber--;
                  errors++;
                  }
                }
              }

            if (strncmp(ret,"#define ",8) == 0) {
              ret += 8;
              while (*ret == ' ' || *ret == '\t') ret++;
              pos = 0;
              while (*ret != 0 && *ret > ' ')
                buffer[pos++] = *ret++;
              buffer[pos] = 0;
              ret = strip(ret);
              if (*ret == 0) addDefine(buffer,"1");
                else addDefine(buffer, ret);
              }

            if (strncasecmp(ret,"#error",6) == 0) {
              ret += 6;
              ret = trim(ret);
              printf("***ERROR: %s\n",ret);
              errors++;
              }

            if (strncasecmp(ret,"#undef",6) == 0) {
              ret += 6;
              ret = trim(ret);
              delDefine(ret);
              }

            }

          if (strncmp(ret,"#ifdef ",7) == 0) {
            if (nests[numNests] == 'N') {
              numNests++;
              nests[numNests] = 'I';
              }
            else {
              ret += 7;
              while (*ret == ' ' || *ret == '\t') ret++;
              pos = 0;
              while (*ret != 0 && *ret > ' ')
                buffer[pos++] = *ret++;
              buffer[pos] = 0;
              pchar = findDefine(buffer);
              numNests++;
              if (pchar != NULL) nests[numNests] = 'Y';
                else nests[numNests] = 'N';
              }
            }

          if (strncmp(ret,"#ifndef ",8) == 0) {
            if (nests[numNests] == 'N') {
              numNests++;
              nests[numNests] = 'I';
              }
            else {
              ret += 8;
              while (*ret == ' ' || *ret == '\t') ret++;
              pos = 0;
              while (*ret != 0 && *ret > ' ')
                buffer[pos++] = *ret++;
              buffer[pos] = 0;
              pchar = findDefine(buffer);
              numNests++;
              if (pchar != NULL) nests[numNests] = 'N';
                else nests[numNests] = 'Y';
              }
            }

          if (strncmp(ret,"#if ",4) == 0) {
            if (nests[numNests] == 'N') {
              numNests++;
              nests[numNests] = 'I';
              }
            else {
              ret += 4;
              while (*ret == ' ' || *ret == '\t') ret++;
              defReplace(ret);
              evaluate(ret, &dvalue);
              value = dvalue;
              numNests++;
              if (value != 0) nests[numNests] = 'Y';
                else nests[numNests] = 'N';
              }
            }

          if (strncmp(ret,"#else",5) == 0) {
            if (numNests > 0)
              nests[numNests] = (nests[numNests] == 'Y') ? 'N' : 'Y';
            else {
              printf("***Error: Unmatched #else\n");
              errors++;
              }
            }

          }

        if (strncmp(ret,"#endif",6) == 0) {
          if (numNests > 0) numNests--;
          else {
            printf("***Error: Unmatched #endif\n");
            errors++;
            }
          }

        if (nests[numNests] == 'Y') {
          if (fileNumber == 0)
            sprintf(listLine,"[%05d] ",lineNumber[fileNumber]);
          else
            sprintf(listLine,"<%05d> ",lineNumber[fileNumber]);
          while (strlen(listLine) < 24) strcat(listLine," ");
          strcat(listLine,"  ");
          strcat(listLine,sourceLine);
          if (passNumber == 2) {
            if (showList != 0) printf("%s\n",listLine);
            if (createLst != 0) fprintf(lstFile,"%s\n",listLine);
            }
          }

        flag = -1;
        }

      else if (nests[numNests] != 'Y') {
        flag = -1;
        }
      else {
        defReplace(ret);
        }
      }
    else {
      if (fileNumber == 0) flag = 0;
      else {
        fclose(sourceFile[fileNumber]);
        fileNumber--;
        flag = -1;
        }
      }
    }
  if (fileNumber == 0)
    sprintf(listLine,"[%05d] ",lineNumber[fileNumber]);
  else
    sprintf(listLine,"<%05d> ",lineNumber[fileNumber]);
  return ret;
  }

// ************************************************************************
// *****                    End of preprocessor                       *****
// ************************************************************************


void Asm(char* line) {
  int   pos;
  char  qt;
  char *orig;
  char  label[32];
  char  opcode[32];
  char  args[128];
  word  operands[32];
  char  operandsEType[32];
  int   operandsERef[32];
  byte  isreg[32];
  char  *opline;
  int   opcount;
  char *pargs;
  char  buffer[256];
  dword  value;
  int    macro;
  byte  flag;
  byte  c;
  int   i,j;
  byte  b;
  byte valid;
  char  lst[1024];
  usedReference = -1;
  orig = sourceLine;
  if (*line == '.') {
    sprintf(lst, "                  %s\n", orig);
    strcat(listLine, lst);
    list(listLine);
    if (strncasecmp(line,".align ",7) == 0) {
      if (passNumber == 2 && outCount > 0) writeOutput();
      outCount = 0;
      line += 7;
      line = trim(line);
      if (strncasecmp(line,"word",4) == 0) address = (address+1) & 0xfffe;
      if (strncasecmp(line,"dword",5) == 0) address = (address+3) & 0xfffc;
      if (strncasecmp(line,"qword",5) == 0) address = (address+7) & 0xfff8;
      if (strncasecmp(line,"para",4) == 0) address = (address+15) & 0xfff0;
      if (strncasecmp(line,"32",2) == 0) address = (address+31) & 0xffe0;
      if (strncasecmp(line,"64",2) == 0) address = (address+63) & 0xffc0;
      if (strncasecmp(line,"128",3) == 0) address = (address+127) & 0xff80;
      if (strncasecmp(line,"page",4) == 0) address = (address+255) & 0xff00;
      outAddress = address;
      return;
      }
    if (strncasecmp(line,".1805",5) == 0) {
      use1805 = 0xff;
      return;
      }
    if (strncasecmp(line,".list",5) == 0) {
      showList = 0xff;
      return;
       }
    if (strncasecmp(line,".sym",4) == 0) {
      showSymbols = 0xff;
      return;
      }
    if (strncasecmp(line,".op ",4) == 0) {
      compileOp(line+4);
      return;
      }
    if (strncasecmp(line,".intel",6) == 0) {
      outMode = 'I';
      return;
      }
    if (strncasecmp(line,".rcs",4) == 0) {
      outMode = 'R';
      return;
      }
    if (strncasecmp(line,".binary",7) == 0) {
      outMode = 'B';
      return;
      }
    if (strncasecmp(line,".arch=melf",10) == 0) {
      ramStart = 0x0000;
      ramEnd = 0x7fff;
      romStart = 0x8000;
      romEnd = 0xffff;
      }
    if (strncasecmp(line,".arch=pev",9) == 0) {
      ramStart = 0x0000;
      ramEnd = 0x7fff;
      romStart = 0x8000;
      romEnd = 0xffff;
      }
    if (strncasecmp(line,".arch=pev2",10) == 0) {
      ramStart = 0x0000;
      ramEnd = 0x7fff;
      romStart = 0x8000;
      romEnd = 0xffff;
      }
    if (strncasecmp(line,".arch=elf2k",11) == 0) {
      ramStart = 0x0000;
      ramEnd = 0x7fff;
      romStart = 0x8000;
      romEnd = 0xffff;
      }
    if (strncasecmp(line,".arch=mclo",10) == 0) {
      ramStart = 0x0000;
      ramEnd = 0x7fff;
      romStart = 0x8000;
      romEnd = 0xffff;
      }
    if (strncasecmp(line,".arch=mchi",10) == 0) {
      ramStart = 0x8000;
      ramEnd = 0xffff;
      romStart = 0x0000;
      romEnd = 0x7fff;
      }
    if (strncasecmp(line,".arch=mchip",11) == 0) {
      ramStart = 0x8000;
      ramEnd = 0xffff;
      romStart = 0x0000;
      romEnd = 0x7fff;
      }
    if (strncasecmp(line,".link ",6) == 0) {
      line += 6;
      while (*line == ' ' || *line == '\t') line++;
      if (passNumber == 2 && outMode == 'R') {
        sprintf(buffer,"%s\n",line);
        write(outFile, buffer, strlen(buffer));
        }
      return;
      }
    }

  if (strncasecmp(line,".suppress",9) == 0) {
    suppression = -1;
    return;
    }

  asmAddress = address;
  strcpy(label,"");
  strcpy(opcode,"");
  strcpy(args,"");
  if ((*line >= 'a' && *line <= 'z') ||
      (*line >= 'A' && *line <= 'Z')) {
    pos = 0;
    while ((*line >= 'a' && *line <= 'z') ||
           (*line >= 'A' && *line <= 'Z') ||
           (*line >= '0' && *line <= '9') ||
           *line == '_' || *line == '!') {
      label[pos++] = *line++;
      }
    label[pos] = 0;
    if (*line != ':') {
      printf("***ERROR: Invalid label");
      printf("%s\n",orig);
      errors++;
      sprintf(lst, "%7s                   %s\n",lineNo(), orig); list(lst);
      return;
      }
    line++;
    }

  line = trim(line);
  if ((*line >= 'a' && *line <= 'z') ||
      (*line >= 'A' && *line <= 'Z')) {
    pos = 0;
    while ((*line >= 'a' && *line <= 'z') ||
           (*line >= 'A' && *line <= 'Z') ||
           (*line >= '0' && *line <= '9')) {
      opcode[pos++] = *line++;
      }
    opcode[pos] = 0;
    }
  line = trim(line);
  pos = 0;
  qt = 0;
  while (((qt == 0 && *line != ';') || qt) && *line != 0) {
    if (*line == '\'') qt = 1 - qt;
    args[pos++] = *line++;
    }
  args[pos] = 0;
  if (passNumber == 1 && strlen(label) > 0) {
    addLabel(label, address);
    }
  if (strlen(opcode) > 0) {
    macro = -1;
    if (passNumber == 2) {
      sprintf(buffer,"%04x: ",address);
      strcat(listLine, buffer);
      }

    lstCount = 0;
    i = 0;
    pos = -1;
    while (pos < 0 && opcodes[i].opcode[0] != 0) {
      if (strcasecmp(opcode, opcodes[i].opcode) == 0) pos = i;
      i++;
      }
    opline = trim(args);
    if (pos < 0 && numOps > 0) {
      opcount = 0;
      while (*opline != 0) {
        isreg[opcount] = isRReg(opline);
        opline = evaluate(opline, &value);
        operands[opcount++] = value;
        operandsEType[opcount-1] = ' ';
        if (usedReference >= 0) {
          operandsEType[opcount-1] = referenceType;
          operandsERef[opcount-1] = usedReference;
          }
        opline = trim(opline);
        if (*opline != 0 && *opline != ',') {
          printf("ERROR: Invalid operand list: %s\n",orig);
          exit(1);
          }
        if (*opline == ',') opline++;
        opline = trim(opline);
        }
      for (i=0; i<numOps; i++)
        if (strcasecmp(opcode, ops[i]) == 0 && strlen(arglist[i]) == opcount) {
          flag = 0xff;
          for (j=0; j<strlen(arglist[i]); j++) {
            if (arglist[i][j] == 'N' || arglist[i][j] == 'n')
              if (operands[j] > 15) flag = 0;
            if (arglist[i][j] == 'B' || arglist[i][j] == 'b')
              if (operands[j] > 255) flag = 0;
            if (arglist[i][j] == 'R' || arglist[i][j] == 'r')
              if (isreg[j] == 0 || operands[j] > 15) flag = 0;
            }
          if (flag) {
            macro = i;
            i = numOps+1; 
            }
          }
      }
    if (pos < 0 && macro == -1) {
      printf("***ERROR: Unknown opcode: %s\n",opcode);
      errors++;
      sprintf(lst, "%7s                   %s\n",lineNo(), orig); list(lst);
      return;
      }
    linesAssembled++;
    while (*args != 0 && args[strlen(args)-1] <= ' ')
      args[strlen(args)-1] = 0;
    if (macro >= 0) {
      b = 0;
      i = 0;
      valid = 0;
      while ((c = translation[macro][i]) != 0) {

        if (c == ' ') {
          if (valid) output(b);
          b = 0;
          valid = 0;
          }
        if (c >= '0' && c <='9') { b = (b << 4) | (c - '0'); valid = 0xff; }
        if (c >= 'A' && c <='F') { b = (b << 4) | (c - 55); valid = 0xff; }
        if (c >= 'a' && c <='f') { b = (b << 4) | (c - 87); valid = 0xff; }
        if (c == '$') {
          i++;
          c = translation[macro][i] - '1';
          b = (b << 4) | (operands[c] & 0xf);
          valid = 0xff;
          }

        if (c == 'w' || c == 'W') {
          i++;
           if (passNumber == 2 && usedLocal >= 0) {
             fixups[numFixups] = address;
             fixupTypes[numFixups] = 'W';
             numFixups++;
             }
          if (valid) output(b);
          c = translation[macro][i] - '1';
          if (passNumber == 2 && operandsEType[c] != ' ') {
            sprintf(buffer,"?%s %04x\n",labels[operandsERef[c]],address);
            write(outFile, buffer, strlen(buffer));
            }
          if (c >= 0 && c<= 9) {
            b = ((operands[c] >> 8) & 0xff);
            output(b);
            b = (operands[c] & 0xff);
            output(b);
            }
          valid = 0;
          }

        if (c == 'l' || c == 'L') {
          i++;
           if (passNumber == 2 && usedLocal >= 0) {
             fixups[numFixups] = address;
             fixupTypes[numFixups] = 'L';
             numFixups++;
             }
          if (valid) output(b);
          c = translation[macro][i] - '1';
          if (passNumber == 2 && operandsEType[c] != ' ') {
            sprintf(buffer,"\\%s %04x\n",labels[operandsERef[c]],address);
            write(outFile, buffer, strlen(buffer));
            }
          if (c >= 0 && c<= 9) b = (operands[c] & 0xff);
          valid = 0xff;
          }

        if (c == 'h' || c == 'H') {
          i++;
           if (passNumber == 2 && usedLocal >= 0) {
             fixups[numFixups] = address;
             fixupTypes[numFixups] = 'H';
             fixupLowOffset[numFixups] = ((operands[translation[macro][i] - '1'] & 0xff) - referenceLowOffset) & 0xff;
             numFixups++;
             }
          if (valid) output(b);
          c = translation[macro][i] - '1';
          if (passNumber == 2 && operandsEType[c] != ' ') {
            sprintf(buffer,"/%s %04x %02x\n",labels[operandsERef[c]],address,operands[c] & 0xff);
            write(outFile, buffer, strlen(buffer));
            }
          b = ((operands[c] >> 8) & 0xff);
          valid = 0xff;
          }
        i++;
        }
      if (valid) output(b);
      }
    else {
      switch (opcodes[pos].typ) {
        case OT_0ARG:
             if (strlen(args) > 0 && passNumber == 2) {
               printf("WARNING: %s does not take operands\n",opcodes[pos].opcode);
               }
             output(opcodes[pos].byte1);
             break;
        case OT_1ARG:
             output(opcodes[pos].byte1);
             output(processArgs(args) & 0xff);
             if (passNumber == 2 && usedReference >= 0) {
               if (referenceType == 'W' || referenceType == 'L')
                 sprintf(buffer,"\\%s %04x\n",labels[usedReference],address-1);
               else {
                 if (referenceLowOffset == 0)
                   sprintf(buffer,"/%s %04x\n",labels[usedReference],address-1);
                 else
                   sprintf(buffer,"/%s %04x %02x\n",labels[usedReference],address-1,referenceLowOffset);
                 }
               write(outFile, buffer, strlen(buffer));
               }
             if (passNumber == 2 && usedLocal >= 0) {
               fixups[numFixups] = address-1;
               fixupTypes[numFixups] = referenceType;
               if (referenceType == 'H')
                 fixupLowOffset[numFixups] = referenceLowOffset;
               else
                 fixupLowOffset[numFixups] = 0;
               numFixups++;
               }
             break;
        case OT_SBR:
             output(opcodes[pos].byte1);
             value = processArgs(args);
             if (passNumber == 2 && (value & 0xff00) != (address & 0xff00)) {
               if (fileNumber == 0)
                 printf("[%05d]: Short branch out of page\n",lineNumber[fileNumber]);
               else
                 printf("<%05d>: Short branch out of page\n",lineNumber[fileNumber]);
               errors++;
               }
             output(value & 0xff);
             break;
        case OT_NARG:
             output(opcodes[pos].byte1 | (processArgs(args) & 0xf));
             break;
        case OT_DB:
             processDb(args,opcodes[pos].byte1);
             break;
        case OT_DF:
             processDf(args);
             break;
        case OT_DS:
             processDs(processArgs(args));
             break;
        case OT_ORG:
             if (inProc == 0) {
               value = processArgs(args);
               processOrg(processArgs(args));
               }
             else {
               printf("!!!WARNING!!! ORG not allowed inside of PROC\n");
               }
             break;
        case OT_EQU:
             value = processArgs(args);
             setLabel(label, value);
             break;
        case OT_LBR:
             value = processArgs(args);
             output(opcodes[pos].byte1);
             if (passNumber == 2 && usedReference >= 0) {
               sprintf(buffer,"?%s %04x\n",labels[usedReference],address);
               write(outFile, buffer, strlen(buffer));
               }
             if (passNumber == 2 && usedLocal >= 0) {
               fixups[numFixups] = address;
               fixupTypes[numFixups] = referenceType;
               numFixups++;
               }
             output(value/256);
             output(value%256);
             break;
        case OT_680ARG:
             if (use1805 == 0) {
               printf("***ERROR: 1805 Instruction used while not in 1805 mode\n");
               errors++;
               }
             output(0x68);
             output(opcodes[pos].byte1);
             break;
        case OT_681ARG:
             if (use1805 == 0) {
               printf("***ERROR: 1805 Instruction used while not in 1805 mode\n");
               errors++;
               }
             output(0x68);
             output(opcodes[pos].byte1);
             output(processArgs(args) & 0xff);
             break;
        case OT_682ARG:
             if (use1805 == 0) {
               printf("***ERROR: 1805 Instruction used while not in 1805 mode\n");
               errors++;
               }
             output(0x68);
             pargs = evaluate(args, &value);
             output(opcodes[pos].byte1 | (value & 0xf));
             pargs = trim(pargs);
             if (*pargs == ',') {
               pargs++;
               pargs = trim(pargs);
               pargs = evaluate(pargs, &value);
               output((value & 0xff00) >> 8);
               output(value & 0xff);
               }
             else {
               printf("***ERROR: Missing argument\n");
               errors++;
               }
             break;
        case OT_68NARG:
             if (use1805 == 0) {
               printf("***ERROR: 1805 Instruction used while not in 1805 mode\n");
               errors++;
               }
             output(0x68);
             output(opcodes[pos].byte1 | (processArgs(args) & 0xf));
             break;
        case OT_END:
             if (passNumber == 1) {
               execAddr = processArgs(args) & 0xffff;
               }
             break;
        case OT_PUBLIC:
             if (passNumber == 2) {
               i = findLabel(args);
               if (i >= 0) {
                 if (outMode == 'R') {
                   sprintf(buffer,"=%s %04x\n",labels[i], labelValues[i]);
                   write(outFile, buffer, strlen(buffer));
                   }
                 }
               }
             break;
        case OT_EXTRN:
             if (passNumber == 1) {
               addLabel(args, 0);
               i = findLabel(args);
               numExternals++;
               if (numExternals == 1)
                 externals = (int*)malloc(sizeof(int));
               else
                 externals = (int*)realloc(externals,sizeof(int)*numExternals);
               externals[numExternals-1] = i;
               }
             break;
        case OT_PROC:
             inProc = -1;
             strcpy(module,args);
             if (passNumber == 2 && outCount > 0) {
               writeOutput();    
               outCount = 0;
               }
             address = 0;
             outAddress = 0;
             if (passNumber == 1) {
               addLabel(args, 0);
               }
             if (outMode == 'R' && passNumber == 2) {
               sprintf(buffer,"{%s\n",args);
               write(outFile, buffer, strlen(buffer));
               }
             numFixups = 0;
             break;
        case OT_ENDP:
             if (inProc == 0) {
               printf("***ERROR: ENDP encountered outside PROC\n");
               errors++;
               }
             if (passNumber == 2 && outCount > 0) {
               writeOutput();    
               outCount = 0;
               outAddress = address;
               }
             if (outMode == 'R' && passNumber == 2) {
               for (i=0; i<numFixups; i++) {
                 if (fixupTypes[i] == 'W')
                   sprintf(buffer,"+%04x\n",fixups[i]);
                 if (fixupTypes[i] == 'H') {
                   if (fixupLowOffset[i] != 0)
                     sprintf(buffer,"^%04x %02x\n",fixups[i],fixupLowOffset[i]);
                   else
                     sprintf(buffer,"^%04x\n",fixups[i]);
                   }
                 if (fixupTypes[i] == 'L')
                   sprintf(buffer,"v%04x\n",fixups[i]);
                 write(outFile, buffer, strlen(buffer));
                 }
               sprintf(buffer,"}\n");
               write(outFile, buffer, strlen(buffer));
               }
             inProc = 0;
             strcpy(module,"*");
             break;
        case OT_VER:
             output(buildMonth);
             output(buildDay);
             output((buildYear >> 8) & 0xff);
             output(buildYear & 0xff);
             break;
        case OT_EVER:
             output(buildMonth | 0x80);
             output(buildDay);
             output((buildYear >> 8) & 0xff);
             output(buildYear & 0xff);
             output((buildNumber >> 8) & 0xff);
             output(buildNumber & 0xff);
             break;
        case OT_EEVER:
             output(buildMonth | 0xc0);
             output(buildDay);
             output((buildYear >> 8) & 0xff);
             output(buildYear & 0xff);
             output(buildHour);
             output(buildMinute);
             output(buildSecond);
             output((buildNumber >> 8) & 0xff);
             output(buildNumber & 0xff);
             break;
        default:
             printf("***ERROR: Unknown instruction type: %d\n",opcodes[pos].typ);
             errors++;
             break;
        }
      }
    if (passNumber == 2) {
      while (lstCount < 4) {
        strcat(listLine, "   ");
        lstCount++;
        }
      if (lstCount <= 4) {
        strcat(listLine, sourceLine);
        }
      strcat(listLine, "\n");
      list(listLine);
      }
    }
  else {
    sprintf(lst, "%7s                   %s\n",lineNo(), orig); list(lst);
    }
  }

word getHex(char* line) {
  word number;
  number = 0;
  while ((*line >= '0' && *line <= '9') ||
         (*line >= 'a' && *line <= 'f') ||
         (*line >= 'A' && *line <= 'F')) {
    if (*line >= '0' && *line <= '9') number = (number << 4) + (*line - '0');
    if (*line >= 'a' && *line <= 'f') number = (number << 4) + (*line - 'a') + 10;
    if (*line >= 'A' && *line <= 'F') number = (number << 4) + (*line - 'A') + 10;
    line++;
    }
  return number;
  }


void processRAM(char* buffer) {
  ramStart = getHex(buffer);
  while (*buffer != '-' && *buffer != 0) buffer++;
  if (*buffer != '-') {
    printf("Invalid format for -ram\n");
    exit(1);
    }
  buffer++;
  ramEnd = getHex(buffer);
  }

void processROM(char* buffer) {
  romStart = getHex(buffer);
  while (*buffer != '-' && *buffer != 0) buffer++;
  if (*buffer != '-') {
    printf("Invalid format for -rom\n");
    exit(1);
    }
  buffer++;
  romEnd = getHex(buffer);
  }

void processOption(char* option) {
  char def[256];
  char *equals;
    if (strcmp(option,"-1805") == 0) use1805 = -1;
    if (strcmp(option,"-b") == 0) outMode = 'B';
    if (strcmp(option,"-i") == 0) outMode = 'I';
    if (strcmp(option,"-r") == 0) outMode = 'R';
    if (strcmp(option,"-l") == 0) showList = -1;
    if (strcmp(option,"-L") == 0) createLst = -1;
    if (strcmp(option,"-s") == 0) showSymbols = -1;
    if (strcmp(option,"-e") == 0) useExtended = -1;
    if (strcmp(option,"-lf") == 0) strcpy(lineEnding,"\n");
    if (strcmp(option,"-cr") == 0) strcpy(lineEnding,"\r");
    if (strcmp(option,"-crlf") == 0) strcpy(lineEnding,"\r\n");
    if (strcmp(option,"-lfcr") == 0) strcpy(lineEnding,"\n\r");
    if (strncmp(option,"-D",2) == 0) {
      option += 2;
      strcpy(def,option);
      equals = strchr(def,'=');
      numClDefines++;
      if (numClDefines == 1) {
        clDefines = (char**)malloc(sizeof(char*));
        clDefineValues = (char**)malloc(sizeof(char*));
        }
      else {
        clDefines = (char**)realloc(clDefines,sizeof(char*)*numClDefines);
        clDefineValues = (char**)realloc(clDefineValues,sizeof(char*)*numClDefines);
        }
      if (equals != NULL) {
        *equals = 0;
        equals++;
        clDefines[numClDefines-1] = (char*)malloc(strlen(def)+1);
        clDefineValues[numClDefines-1] = (char*)malloc(strlen(equals)+1);
        strcpy(clDefines[numClDefines-1], def);
        strcpy(clDefineValues[numClDefines-1], equals);
        }
      else {
        clDefines[numClDefines-1] = (char*)malloc(strlen(option)+1);
        clDefineValues[numClDefines-1] = (char*)malloc(2);
        strcpy(clDefines[numClDefines-1], option);
        strcpy(clDefineValues[numClDefines-1], "1");
        }
      }
    if (strncmp(option,"-I",2) == 0) {
      option += 2;
      numIncPath++;
      if (numIncPath == 1) 
        incPath = (char**)malloc(sizeof(char*));
      else
        incPath = (char**)realloc(incPath,sizeof(char*)*numIncPath);
      incPath[numIncPath-1] = (char*)malloc(strlen(option)+1);
      strcpy(incPath[numIncPath-1], option);
      }

    if (strcmp(option,"-melf") == 0) {
      ramStart = 0x0000;
      ramEnd = 0x7fff;
      romStart = 0x8000;
      romEnd = 0xffff;
      }
    if (strcmp(option,"-pev") == 0) {
      ramStart = 0x0000;
      ramEnd = 0x7fff;
      romStart = 0x8000;
      romEnd = 0xffff;
      }
    if (strcmp(option,"-pev2") == 0) {
      ramStart = 0x0000;
      ramEnd = 0x7fff;
      romStart = 0x8000;
      romEnd = 0xffff;
      }
    if (strcmp(option,"-elf2k") == 0) {
      ramStart = 0x0000;
      ramEnd = 0x7fff;
      romStart = 0x8000;
      romEnd = 0xffff;
      }
    if (strcmp(option,"-mclo") == 0) {
      ramStart = 0x0000;
      ramEnd = 0x7fff;
      romStart = 0x8000;
      romEnd = 0xffff;
      }
    if (strcmp(option,"-mchi") == 0) {
      ramStart = 0x8000;
      ramEnd = 0xffff;
      romStart = 0x0000;
      romEnd = 0x7fff;
      }
    if (strcmp(option,"-mchip") == 0) {
      ramStart = 0x8000;
      ramEnd = 0xffff;
      romStart = 0x0000;
      romEnd = 0x7fff;
      }
    if (strncmp(option,"-ram=",5) == 0) processRAM(option+5);
    if (strncmp(option,"-rom=",5) == 0) processROM(option+5);
  }

int pass(int p, char* srcFile) {
  int i;
  char buffer[256];
  suppression = 0;
  passNumber = p;
  address = 0;
  outCount = 0;
  numNests = 0;
  outAddress = 0;
  linesAssembled = 0;
  numFixups = 0;
  lowAddress = 0xffff;
  highAddress = 0x0000;
  strcpy(module,"*");
  fileNumber = 0;
  sourceFile[0] = fopen(srcFile,"r");
  if (sourceFile[0] == NULL) {
    printf("Could not open source file: %s\n",srcFile);
    exit(1);
    }
  lineNumber[0] = 0;
  if (passNumber == 2) {
      if (outMode != 'B') {
      outFile = open(outName,O_CREAT|O_TRUNC|O_WRONLY|O_BINARY,0666);
      if (outFile < 0) {
        printf("Could not open output file: %s\n",outName);
        exit(1);
        }
      if (outMode == 'R') {
        sprintf(buffer,".big\n");
        write(outFile, buffer, strlen(buffer));
        }
      }
    if (createLst) lstFile = fopen(lstName,"w");
    }
  nests[0] = 'Y';
  while (nextLine(buffer) != NULL) {
    for (i=0; i<strlen(buffer); i++)
      if (buffer[i] < 32 && buffer[i] != '\t') buffer[i] = 0;
    Asm(buffer);
    }
  fclose(sourceFile[0]);
  if (inProc) {
    printf("***ERROR: PROC without ENDP\n");
    errors++;
    }
  if (passNumber == 2 && outCount > 0) writeOutput();    
  if (passNumber == 2 && outMode != 'B') {
    //write EOF before closing intel hex file
    if (outMode == 'I') {
      write(outFile, ":00000001ff\n", 12);
      }
    if (outMode == 'R') {
      if (execAddr != 0xffff) {
        sprintf(buffer,"@%04x\n",execAddr);
        write(outFile, buffer, strlen(buffer));
        }
      }
    close(outFile); 
  }
  if (passNumber == 2 && createLst) fclose(lstFile);
  if (numNests > 0) printf("#ifdef without #endif\n");

  for (i=0; i<numDefines; i++)
    free(defines[i]);
  if (numDefines > 0) {
    free(defines);
    free(defineValues);
    }
  return 0;
  }

void clear() {
  int i;
  if (numLabels != 0) {
    for (i=0; i<numLabels; i++) {
      free(labels[i]);
      free(labelProcs[i]);
      }
    free(labels);
    free(labelValues);
    free(labelProcs);
    }
  numLabels = 0;
  numExternals = 0;
  execAddr = 0xffff;
  strcpy(module," ");
  addLabel("r0",0);
  addLabel("r1",1);
  addLabel("r2",2);
  addLabel("r3",3);
  addLabel("r4",4);
  addLabel("r5",5);
  addLabel("r6",6);
  addLabel("r7",7);
  addLabel("r8",8);
  addLabel("r9",9);
  addLabel("r10",10);
  addLabel("r11",11);
  addLabel("r12",12);
  addLabel("r13",13);
  addLabel("r14",14);
  addLabel("r15",15);
  addLabel("ra",10);
  addLabel("rb",11);
  addLabel("rc",12);
  addLabel("rd",13);
  addLabel("re",14);
  addLabel("rf",15);
  }

void assembleFile(char* sourceFile, int argc, char** argv) {
  int i;
  char tmp[1024];
  FILE *buildFile;
  inProc = 0;
  numDefines = 0;
  errors = 0;
  numOps = 0;
  passNumber = 1;
  codeGenerated = 0;
  clear();
  strcpy(baseName, sourceFile);
  for (i=0; i<strlen(baseName); i++)
    if (baseName[i] == '.') baseName[i] = 0;
  strcpy(outName,baseName);
  switch (outMode) {
    case 'R': strcat(outName, ".prg"); break;
    case 'I': strcat(outName, ".hex"); break;
    case 'B': strcat(outName, ".bin"); break;
    }
  strcpy(lstName,baseName);
  strcat(lstName,".lst");

  strcpy(tmp, baseName);
  strcat(tmp,".build");
  buildFile = fopen(tmp, "r");
  if (buildFile == NULL) {
    buildNumber = 1;
    }
  else {
    fgets(buffer, 32, buildFile);
    buildNumber = atoi(buffer) + 1;
    fclose(buildFile);
    }
  buildFile = fopen(tmp,"w");
  fprintf(buildFile,"%d\n",buildNumber);
  fclose(buildFile);
  

//  for (i=0; i<argc; i++) {
//    if (strncmp(argv[i],"-D",2) == 0) {
//      addDefine(argv[i]+2,"1");
//      }
//    }

  for (i=0; i<numClDefines; i++)
    addDefine(clDefines[i], clDefineValues[i]);

  i = pass(1, sourceFile);
  numDefines = 0;
  if (i == 0 && errors == 0) {
//    for (i=0; i<argc; i++) {
//      if (strncmp(argv[i],"-D",2) == 0) {
//        addDefine(argv[i]+2,"1");
//        }
//      }
    for (i=0; i<numClDefines; i++)
      addDefine(clDefines[i], clDefineValues[i]);
    i = pass(2, sourceFile);
    if (outMode == 'B' && i == 0 && errors == 0) {
      outFile = open(outName,O_CREAT|O_TRUNC|O_WRONLY|O_BINARY,0666);
      if (outFile < 0) {
        printf("Could not open output file: %s\n",outName);
        exit(1);
        }
      write(outFile, memory+lowAddress, (highAddress-lowAddress) + 1);
      close(outFile);
      }
    }
  else printf("Errors during pass 1, aborting pass 2\n");

  printf("\n");
  printf("Lines Assembled   : %d\n",linesAssembled);
  printf("Code Generated    : %d\n",codeGenerated);
  printf("Errors            : %d\n",errors);
  printf("\n");

  if (showSymbols) {
    printf("Symbols:\n");
    for (i=22; i<numLabels; i++) {
      printf("  %04x  %-20s %-20s",labelValues[i],labels[i],labelProcs[i]);
      if (isExternal(i) >= 0) printf(" *");
      printf("\n");
      }
    }

  if (numLabels > 0) {
    for (i=0; i<numLabels; i++) {
      free(labels[i]);
      free(labelProcs[i]);
      }
    free(labels);
    free(labelValues);
    free(labelProcs);
    }
  if (errors > 0) exit(1);
  numLabels = 0;
  }

int main(int argc, char** argv) {
  int i;
  time_t tv;
  struct tm dt;
  printf("Asm/02 v1.1\n");
  printf("by Michael H. Riley\n");
  createLst = 0;
  outMode = 'R';
  ramStart = 0x0000;
  ramEnd = 0xffff;
  romStart = 0xffff;
  romEnd = 0xffff;
  showList = 0;
  showSymbols = 0;
  use1805 = 0;
  useExtended = 0;
  numSourceFiles = 0;
  numLabels = 0;
  numExternals = 0;
  numIncPath = 0;
  strcpy(lineEnding,"\n");
  tv = time(NULL);
  localtime_r(&tv, &dt);
  buildMonth = dt.tm_mon + 1;
  buildDay = dt.tm_mday;
  buildYear = dt.tm_year + 1900;
  buildHour = dt.tm_hour;
  buildMinute = dt.tm_min;
  buildSecond = dt.tm_sec;
  i = 1;
  while (i < argc) {
    if (argv[i][0] != '-') {
      numSourceFiles++;
      if (numSourceFiles == 0)
        sourceFiles = (char**)malloc(sizeof(char*));
      else
        sourceFiles = (char**)realloc(sourceFiles,sizeof(char*)*numSourceFiles);
      sourceFiles[numSourceFiles-1] = (char*)malloc(strlen(argv[i])+1);
      strcpy(sourceFiles[numSourceFiles-1], argv[i]);
      }
    else processOption(argv[i]);
    i++;
    }
  if (numSourceFiles == 0) {
    printf("No source files specified\n");
    exit(1);
    }
  for (i=0; i<numSourceFiles; i++)
    assembleFile(sourceFiles[i], argc, argv);
  if (errors > 0) return 1;
  return 0;
  }
