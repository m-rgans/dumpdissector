
enum {
  I_RR,
  I_QST,
  I_QV,
  I_RRE
  I_RS,
  I_RX,
};

typedef struct
{
  u8 OpCode;
  u8 R1;
  u8 R2;
} RRinst;

typedef struct
{
  u8 OpCode;
  u8 R1;
  u8 X2; //4 bit
  u8 B2; //4 bit
  u16 D2;
} RXinst;

typedef struct
{
  u16 OpCode;
  u8 R1;
  u8 R2;
} QSTinst;

typedef struct {
  char* text;

  u8 INST_TYPE;
  union {
    RRinst RRInterp;
    RXinst RXInterp;
  } Operands;
} Instruction_t;

Instruction Interp_Trace(const char*)
