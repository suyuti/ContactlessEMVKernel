/*
    Copyright 2015
*/

#ifndef SRC_BASE_ERR_H_
#define SRC_BASE_ERR_H_

#define SUCCESS                     0

#define ERR_BASE                    0
#define NULL_PARAMETER              (ERR_BASE - 1)
#define UNKNOWN_PARAMETER           (ERR_BASE - 2)
#define SIZE_INCORRECT              (ERR_BASE - 3)
#define INVALID_PARAMETER           (ERR_BASE - 4)
#define INCORRECT_DATA              (ERR_BASE - 5)
#define FILE_NOT_FOUND              (ERR_BASE - 6)
#define CRYPTO_FAILURE              (ERR_BASE - 7)
#define INDEX_OUT_OF_RANGE          (ERR_BASE - 8)
#define OBJECT_NOT_FOUND            (ERR_BASE - 9)
#define HAL_INTERFACE_IS_NULL       (ERR_BASE - 10)
    

#define ERR_EMV_BASE                (-100)
#define SW_NOT_SUCCESS              (ERR_EMV_BASE - 1)
#define UNKNOWN_TAG                 (ERR_EMV_BASE - 2)

#define ERR_SELECT_BASE             (-200)
#define FCI_NOT_FOUND               (ERR_SELECT_BASE - 1)
#define TAG84_NOT_FOUND             (ERR_SELECT_BASE - 2)
#define TAGA5_NOT_FOUND             (ERR_SELECT_BASE - 3)
#define TAG88_NOT_FOUND             (ERR_SELECT_BASE - 4)
#define NO_MORE_RECORDS             (ERR_SELECT_BASE - 5)
#define TAG82_NOT_FOUND             (ERR_SELECT_BASE - 6)
#define TAG94_NOT_FOUND             (ERR_SELECT_BASE - 7)

#define ERR_ODA_BASE                (-300)
#define CARD_AIP_NOT_FOUND          (ERR_ODA_BASE - 1)
#define CARD_AID_NOT_FOUND          (ERR_ODA_BASE - 2)
#define CARD_CAPK_INDEX_NOT_FOUND   (ERR_ODA_BASE - 3)
#define ISS_CERT_NOT_FOUND          (ERR_ODA_BASE - 4)
#define ISS_CERT_NOT_VALID          (ERR_ODA_BASE - 5)

#endif //SRC_BASE_ERR_H_
