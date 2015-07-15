#ifndef _EP_OUTCOME_H_
#define _EP_OUTCOME_H_

#include "epCommon.h"
//--------------------------------------------------------------------
// Outcome types
#define SELECT_NEXT                 1
#define TRY_AGAIN                   2
#define APPROVED                    3
#define DECLINED                    4
#define ONLINE_REQUEST              5
#define TRY_ANOTHER_INTERFACE       6
#define END_APPLICATION             7

/*#define RESET_OUTCOME(obj)              memset(&obj, 0x00, sizeof(EpOutcome))

#define SET_OUTCOME_STARTTYPE(obj, t)               (obj).start = (t)
#define SET_OUTCOME_ONLINERESPONSE(obj, r, l)       memcpy((obj).onlineResponseData, r, l); (obj).onlineResponseDataLen = (l)
#define SET_OUTCOME_CVM(obj, v)                     (obj).cvm = (v)
#define SET_OUTCOME_UIREQON_OUTCOME_PRESENT(obj)    (obj).uiRequestOnOutcomePresent = SET     
#define SET_OUTCOME_UIREQON_RESTART_PRESENT(obj)    (obj).uiRequestOnRestartPresent = SET
#define SET_OUTCOME_DATARECORD_PRESENT(obj)         (obj).dataRecordPresent = SET
#define SET_OUTCOME_DISCDATA_PRESENT(obj)           (obj).discreationaryDataPresent = SET
#define SET_OUTCOME_ALTERNATE_INTERFACE(obj, i)     (obj).alternateInterfacePreference = (i)
#define SET_OUTCOME_RECEIPT(obj)                    (obj).receipt = SET
#define SET_OUTCOME_FIELDOFF(obj)                   (obj).fieldOffRequest = SET
#define SET_OUTCOME_REMOVAL_TIMEOUT(obj, t)         (obj).removalTimeout = (t)
*/
int          resetOutcome(EpOutcomePtr p);
EpOutcomePtr withStartType(EpOutcomePtr p, OutcomeStartTypes t);
EpOutcomePtr withOnlineResponseData(EpOutcomePtr p, unsigned char* data, int len);
EpOutcomePtr withCvm(EpOutcomePtr p, CvmTypes t);
EpOutcomePtr withUiRequestOnOutcomePresent(EpOutcomePtr p);
EpOutcomePtr withUiRequestOnRestartPresent(EpOutcomePtr p);
EpOutcomePtr withDataRecordPresent(EpOutcomePtr p);
EpOutcomePtr withDiscreationaryDataPresent(EpOutcomePtr p);
EpOutcomePtr withAlternateInterface(EpOutcomePtr p, InterfaceTypes t);
EpOutcomePtr withReceipt(EpOutcomePtr p);
EpOutcomePtr withFieldOff(EpOutcomePtr p);
EpOutcomePtr withRemovalTimeout(EpOutcomePtr p, int t);

#endif// _EP_OUTCOME_H_
