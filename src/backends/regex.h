// Internal defs
#ifndef HAMMER_BACKEND_REGEX__H
#define HAMMER_BACKEND_REGEX__H

// each insn is an 8-bit opcode and a 16-bit parameter
// [a] are actions; they add an instruction to the stackvm that is being output.
// [m] are match ops; they can either succeed or fail, depending on the current character
// [c] are control ops. They affect the pc non-linearly.
typedef enum HRVMOp_ {
  RVM_ACCEPT,  // [a]
  RVM_GOTO,    // [c] parameter is an offset into the instruction table
  RVM_FORK,    // [c] parameter is an offset into the instruction table
  RVM_PUSH,    // [a] No arguments, just pushes a mark onto the stack
  RVM_ACTION,  // [a] argument is an action ID
  RVM_CAPTURE, // [a] Capture the last string, and push it on the stack. No arg.
  RVM_EOF,     // [m] Succeeds only if at EOF.
  RVM_MATCH,   // [m] The high byte of the parameter is an upper bound
	       //     and the low byte is a lower bound, both
	       //     inclusive. An inverted match should be handled
	       //     as two ranges.
  RVM_STEP,    // [a] Step to the next byte of input
  RVM_OPCOUNT
} HRVMOp;

typedef struct HRVMInsn_{
  uint8_t op;
  uint16_t arg;
} HRVMInsn;


typedef struct HRVMProg_ {
  size_t length;
  size_t action_count;
  HAction *actions;
  HRVMInsn *insns;
};

#endif
