#include "aliases.h"
#include "stdio.h"
#include <string.h>

// Global struct to store general dump info
struct {
  //This is an array so that little vs big endian systems dont break our math
  u8 PSW[8];

  //Parts of the PSW
  u8 ILC;
  u8 ConditionCode;
  u32 NextInstruction;
  u32 InterruptCode;
} DumpInfo;

u64 MergeBytes(u8* buffer, u32 start, u8 len) {
  u64 res = 0;
  for (size_t i = start; i <= len; i++) {
    //Push over the previously inserted byte.
    //This doesn't cause problems on first run.
    res *= 0x100;
    // OR in the byte
    res += buffer[i];
  }
  return res;
}

void InterpPSW_s(const char* b1, const char* b2) {
  char cbuffer[3] = "00";

  for (size_t i = 0; i < 4; i++) {
    cbuffer[0] = b1[i * 2];
    cbuffer[1] = b1[(i * 2) + 1];

    sscanf(cbuffer, "%x", (unsigned*)&DumpInfo.PSW[i]);
  }

  for (size_t i = 0; i < 4; i++) {
    cbuffer[0] = b2[i * 2];
    cbuffer[1] = b2[(i * 2) + 1];

    sscanf(cbuffer, "%x", (unsigned*)&DumpInfo.PSW[i + 4]);
  }

  //populate the PSW Components
  DumpInfo.ILC = (DumpInfo.PSW[4] >> 6);
  DumpInfo.ConditionCode = (DumpInfo.PSW[4] & 0x30) >> 4;
  DumpInfo.NextInstruction = MergeBytes(DumpInfo.PSW, 5, 7);
  DumpInfo.InterruptCode = MergeBytes(DumpInfo.PSW, 2, 3);
  return;

  printf("Got psw: ");
  for (size_t i = 0; i < 8; i++) {
    printf("%02x", DumpInfo.PSW[i]);
    if (i == 3) {
      printf(" ");
    }
  }
  printf("\n");
  return;
}

int main(int argc, char const *argv[]) {

  if (!strcmp(argv[1], "psw")) {
    if (argc != 4) {
      printf("Please enter PSW in the following format:ddi psw [First 64 bits] [Second 64 bits]\n");
      return 1;

    }

    InterpPSW_s(argv[2], argv[3]);

    printf("Interruption Code: %04x\n", DumpInfo.InterruptCode);
    printf("Instruction Length Code: %x\n", DumpInfo.ILC);
    printf("Condition Code: %x\n", DumpInfo.ConditionCode);
    printf("Next Instruction: %06x\n", DumpInfo.NextInstruction);
    printf("System halted on Instruction %06x\n", DumpInfo.NextInstruction - (2 * DumpInfo.ILC) );

  }
  return 0;
}
