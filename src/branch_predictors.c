//
// This file contains all of the implementations of the branch predictor
// constructors from the branch_predictors.h file.
//
// It also contains stubs of all of the functions that are added to each
// branch_predictor struct at construction time.
//
// Feel free to create any additional structs or global variables that you
// want.
//
// ============================================================================
// NOTE: It is recommended that you read the comments in the
// branch_predictors.h file for further context on what each function is for.
// ============================================================================
//


#include "BranchPredictor.h"
#include "Debug.h"
 BranchPredictor::BranchPredictor() {
 } }
for (int i = 0; i < PRED_BUF_SIZE; ++i) {
Report :
 this->predbuf[i] = WEAK_TAKEN;
BranchPredictor::~BranchPredictor() {}
bool BranchPredictor::predict(uint32_t pc, uint32_t insttype, int64_t op1,
int64_t op2, int64_t offset) {
switch (this->strategy) {
case NT:
return false;
case AT:
return true;
case BTFNT: {
if (offset >= 0) {
  } }
return false;
 } else {
 return true;
 break;
 case BPB: {
 PredictorState state = this->predbuf[pc % PRED_BUF_SIZE];
 if (state == STRONG_TAKEN || state == WEAK_TAKEN) {
 return true;
 } else if (state == STRONG_NOT_TAKEN || state == WEAK_NOT_TAKEN) {
 return false;
 } else {
 dbgprintf("Strange Prediction Buffer!\n");
} }
}
return false;
}
 break;
 default:
 dbgprintf("Unknown Branch Perdiction Strategy!\n");
 break;
  void BranchPredictor::update(uint32_t pc, bool branch) {
 int id = pc % PRED_BUF_SIZE;
 PredictorState state = this->predbuf[id];
 if (branch) {

  if (state == STRONG_NOT_TAKEN) {
 this->predbuf[id] = WEAK_NOT_TAKEN;
 } else if (state == WEAK_NOT_TAKEN) {
 this->predbuf[id] = WEAK_TAKEN;
 } else if (state == WEAK_TAKEN) {
 this->predbuf[id] = STRONG_TAKEN;
 } // do nothing if STRONG_TAKEN
 } else { // not branch
 if (state == STRONG_TAKEN) {
 this->predbuf[id] = WEAK_TAKEN;
 } else if (state == WEAK_TAKEN) {
 this->predbuf[id] = WEAK_NOT_TAKEN;
 } else if (state == WEAK_NOT_TAKEN) {
 this->predbuf[id] = STRONG_NOT_TAKEN;
 } // do noting if STRONG_NOT_TAKEN
} }
 std::string BranchPredictor::strategyName() {
 switch (this->strategy) {
 case NT:
 return "Always Not Taken";
 case AT:
 return "Always Taken";
 case BTFNT:
 return "Back Taken Forward Not Taken";
 case BPB:
 return "Branch Prediction Buffer";

  default:
 dbgprintf("Unknown Branch Perdiction Strategy!\n");
 break;
}
return "error"; // should not go here
}
  #ifndef BRANCH_PREDICTOR_H
 #define BRANCH_PREDICTOR_H
 #include <cstdint>
 #include <string>
 const int PRED_BUF_SIZE = 4096;
 class BranchPredictor {
 public:
 enum Strategy {
 AT, // Always Taken
 NT, // Always Not Taken
 BTFNT, // Backward Taken, Forward Not Taken
 BPB, // Branch Prediction Buffer with 2bit history information
 } strategy;
 BranchPredictor();
 ~BranchPredictor();
 bool predict(uint32_t pc, uint32_t insttype, int64_t op1, int64_t op2,

int64_t offset);
std::string strategyName();
 // For Branch Prediction Buffer
 void update(uint32_t pc, bool branch);
private:
enum PredictorState {
STRONG_TAKEN = 0, WEAK_TAKEN = 1,
STRONG_NOT_TAKEN = 3, WEAK_NOT_TAKEN = 2,
} predbuf[PRED_BUF_SIZE]; // initial state: WEAK_TAKEN
};
#endif
