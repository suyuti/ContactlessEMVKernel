#ifndef _EP_OUTCOME_H_
#define _EP_OUTCOME_H_

//--------------------------------------------------------------------
// Outcome types
#define SELECT_NEXT                 1
#define TRY_AGAIN                   2
#define APPROVED                    3
#define DECLINED                    4
#define ONLINE_REQUEST              5
#define TRY_ANOTHER_INTERFACE       6
#define END_APPLICATION             7


typedef struct {
    int outcomeType;
} EpOutcome, *EpOutcomePtr;

#endif// _EP_OUTCOME_H_
