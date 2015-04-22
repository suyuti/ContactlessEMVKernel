#ifndef _TTQ_H_
#define _TTQ_H_

#include "../Base/bits.h"

// Book A Table 5-4

#define MAGSTRIPE_SUPP_BYTE                 0
#define EMV_MODE_SUPP_BYTE                  0
#define EMV_CONTACT_CHIP_SUPP_BYTE          0
#define OFFLINE_ONLY_READER_BYTE            0
#define ONLINE_PIN_SUPP_BYTE                0
#define SIGNATURE_SUPP_BYTE                 0
#define ODA_FOR_ONLINE_AUTH_SUPP_BYTE       0

#define ONLINE_CRYPT_REQ_BYTE               1
#define CVM_REQ_BYTE                        1
#define OFFLINE_PIN_SUPP_BYTE               1

#define ISS_UPDATE_SUPP_BYTE                2
#define CONS_DEV_CVM_SUPP_BYTE              2


#define MAGSTRIPE_SUPP_BIT                  8
#define EMV_MODE_SUPP_BIT                   6
#define EMV_CONTACT_CHIP_SUPP_BIT           5
#define OFFLINE_ONLY_READER_BIT             4
#define ONLINE_PIN_SUPP_BIT                 3
#define SIGNATURE_SUPP_BIT                  2
#define ODA_FOR_ONLINE_AUTH_SUPP_BIT        1

#define ONLINE_CRYPT_REQ_BIT                8
#define CVM_REQ_BIT                         7
#define OFFLINE_PIN_SUPP_BIT                6

#define ISS_UPDATE_SUPP_BIT                 8
#define CONS_DEV_CVM_SUPP_BIT               7

//--------------------------------------------------------

#define SET_MAGSTRIPE_SUPP(ttq)                SET_BIT(ttq[MAGSTRIPE_SUPP_BYTE], MAGSTRIPE_SUPP_BIT)
#define SET_EMV_MODE_SUPP(ttq)                 SET_BIT(ttq[EMV_MODE_SUPP_BYTE], EMV_MODE_SUPP_BIT)
#define SET_EMV_CONTACT_CHIP_SUPP(ttq)
#define SET_OFFLINE_ONLY_READER(ttq)
#define SET_ONLINE_PIN_SUPP(ttq)
#define SET_SIGNATURE_SUPP(ttq)
#define SET_ODA_FOR_ONLINE_AUTH_SUPP(ttq)
#define SET_ONLINE_CRYPT_REQ(ttq)
#define SET_CVM_REQ(ttq)
#define SET_OFFLINE_PIN_SUPP(ttq)
#define SET_ISS_UPDATE_SUPP(ttq)
#define SET_CONS_DEV_CVM_SUPP(ttq)

#define RESET_MAGSTRIPE_SUPP(ttq)                SET_BIT(ttq[MAGSTRIPE_SUPP_BYTE], MAGSTRIPE_SUPP_BIT)
#define RESET_EMV_MODE_SUPP(ttq)                 SET_BIT(ttq[EMV_MODE_SUPP_BYTE], EMV_MODE_SUPP_BIT)
#define RESET_EMV_CONTACT_CHIP_SUPP()
#define RESET_OFFLINE_ONLY_READER()
#define RESET_ONLINE_PIN_SUPP()
#define RESET_SIGNATURE_SUPP()
#define RESET_ODA_FOR_ONLINE_AUTH_SUPP()
#define RESET_ONLINE_CRYPT_REQ()
#define RESET_CVM_REQ()
#define RESET_OFFLINE_PIN_SUPP()
#define RESET_ISS_UPDATE_SUPP()
#define RESET_CONS_DEV_CVM_SUPP()


#define IS_MAGSTRIPE_SUPP(ttq)                SET_BIT(ttq[MAGSTRIPE_SUPP_BYTE], MAGSTRIPE_SUPP_BIT)
#define IS_EMV_MODE_SUPP(ttq)                 SET_BIT(ttq[EMV_MODE_SUPP_BYTE], EMV_MODE_SUPP_BIT)
#define IS_EMV_CONTACT_CHIP_SUPP()
#define IS_OFFLINE_ONLY_READER()
#define IS_ONLINE_PIN_SUPP()
#define IS_SIGNATURE_SUPP()
#define IS_ODA_FOR_ONLINE_AUTH_SUPP()
#define IS_ONLINE_CRYPT_REQ()
#define IS_CVM_REQ()
#define IS_OFFLINE_PIN_SUPP()
#define IS_ISS_UPDATE_SUPP()
#define IS_CONS_DEV_CVM_SUPP()

#endif // _TTQ_H_
