/*
 ******************************************************************************
 *                     INTERPEAK CONFIGURATION HEADER FILE
 *
 *   Document no: @(#) $Name: VXWORKS_ITER18A_FRZ10 $ $RCSfile: ipipsec_config.h,v $ $Revision: 1.51.8.1 $
 *   $Source: /home/interpeak/CVSRoot/ipipsec2/config/ipipsec_config.h,v $
 *   $Author: ulf $ $Date: 2010-07-02 13:21:09 $
 *   $State: Exp $ $Locker:  $
 *
 *   INTERPEAK_COPYRIGHT_STRING
 *   Design and implementation by Lennart Bang <lob@interpeak.se>
 ******************************************************************************
 */
#ifndef IPIPSEC_CONFIG_H
#define IPIPSEC_CONFIG_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 2                    INCLUDE FILES
 ****************************************************************************
 */

#include <ipcom_config.h>
#include <ipcom_type.h>
#include <ipcom_cstyle.h>
#ifdef IPCRYPTO
#include <ipcrypto_config.h>
#endif
#ifdef IPHWCRYPTO
#include <iphwcrypto_config.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 3                    DEFINES
 ****************************************************************************
 */

/*
 * IMPORTANT: Do not edit this file in case you are using the LKM port
 *  All the options below are configurable through the
 *  Linux kernel configuration tool (make menuconfig)
 *
 */

#ifndef IP_PORT_LKM
/*
 *===========================================================================
 *                         IPIPSEC_USE_DAEMONS
 *===========================================================================
 * Enable this define to process ipsec in a separate context. This is typically
 * used to improve performance on multi-core platforms.
 */
#ifdef IPCOM_USE_SMP
#define IPIPSEC_USE_DAEMONS
#endif


/*
 *===========================================================================
 *                         IPIPSEC_USE_ESP/AH/IPIP
 *===========================================================================
 * Define for IPSEC ESP, AH and/or IPIP
 * RFC4301 section 3.2: "IPsec implementations MUST support ESP and MAY support AH."
 */

#define IPIPSEC_USE_ESP
#define IPIPSEC_USE_AH
#define IPIPSEC_USE_IPIP


/*
 *===========================================================================
 *                       IPSEC authentication algorithms
 *===========================================================================
 * Enable/disable support for MD5, SHA, RIPEMD and/or AESMAC.
 */

#ifndef OPENSSL_NO_MD5
#define IPIPSEC_USE_MD5
#endif

#ifndef OPENSSL_NO_SHA
#define IPIPSEC_USE_SHA
#endif

#if !defined(OPENSSL_NO_RIPEMD) && !defined(IP_SIZE)
#define IPIPSEC_USE_RIPEMD
#endif

#if !defined(OPENSSL_NO_AES)
#define IPIPSEC_USE_AESMAC
#endif


/*
 *===========================================================================
 *                       IPSEC encryption algorithms
 *===========================================================================
 * Enable/disable support for DES, 3DES, AES, AESCTR, BF and/or CAST.
 */

#if !defined(OPENSSL_NO_DES)
#ifndef OPENSSL_FIPS
#define IPIPSEC_USE_DES
#endif
#define IPIPSEC_USE_3DES
#endif

#if !defined(OPENSSL_NO_AES)
#define IPIPSEC_USE_AES
#define IPIPSEC_USE_AESCTR
#endif

#if !defined(OPENSSL_NO_BF) && !defined(IP_SIZE)
#define IPIPSEC_USE_BLOWFISH
#endif

#if !defined(OPENSSL_NO_CAST) && !defined(IP_SIZE)
#define IPIPSEC_USE_CAST
#endif

/*
 *===========================================================================
 *                         IPIPSEC_USE_ESN
 *===========================================================================
 * Define to enable Extended Sequence Number (ESN) for AH and ESP.
 *
 */
#if defined(IPIPSEC_USE_ESP) || defined(IPIPSEC_USE_AH)
#define IPIPSEC_USE_ESN
#endif


/*
 *===========================================================================
 *                         IPIPSEC_USE_TFC
 *===========================================================================
 * Define to enable Traffic Flow Confidentiality (TFC) Padding for ESP.
 *
 */
#if defined(IPIPSEC_USE_ESP)
#define IPIPSEC_USE_TFC
#endif

#endif /* IP_PORT_LKM */

/*
 *===========================================================================
 *                         IPIPSEC_USE_PMTU_DISCOVERY
 *===========================================================================
 * Define to enable path mtu discovery over IPSEC tunnels.
 *
 */
#define IPIPSEC_USE_PMTU_DISCOVERY


/*
 *===========================================================================
 *                         IPIPSEC_USE_BITARRAY
 *===========================================================================
 * Define to enable configuration replay windows for ESN for AH and ESP.
 *
 */
#if defined(IPIPSEC_USE_ESN) && defined(IPCOM_USE_BITARRAY)
#define IPIPSEC_USE_BITARRAY
#endif


/*
 *===========================================================================
 *                         IPIPSEC_USE_MIB
 *===========================================================================
 * Define for IPSEC MIB support
 */
#ifdef IP_DEBUG
#define IPIPSEC_USE_MIB
#endif


/*
 *===========================================================================
 *                         IPIPSEC_USE_STATS
 *===========================================================================
 * Define for IPSEC STATS support (found in 'ipipsec.stats').
 */
#if defined(IP_DEBUG) && !defined(IPIPSEC_USE_STATS)
#define IPIPSEC_USE_STATS
#endif


/*
 *===========================================================================
 *                         IPIPSEC_USE_CTRL_API
 *===========================================================================
 * Define for old deprecated CTRL API support
 */
#define IPIPSEC_USE_CTRL_API


/*
 *===========================================================================
 *                         SYSLOG
 *===========================================================================
 */

/* Define to use syslogs */
#define IPIPSEC_USE_SYSLOG

/* Syslog system priority. */
#ifdef IP_DEBUG
#define IPIPSEC_SYSTEM_PRIORITY    IPCOM_LOG_DEBUG2
#else
#define IPIPSEC_SYSTEM_PRIORITY    IPCOM_LOG_WARNING
#endif


/*
 *===========================================================================
 *                         TRAPS
 *===========================================================================
 */

/* Define to support IPSEC MIB traps. */
#define IPIPSEC_USE_TRAPS

/* Minimum TRAP seconds between each sent trap per SA & type. */
#define IPIPSEC_MIN_SEND_TRAP_SECONDS    3


/*
 ****************************************************************************
 * 4                    PROTOTYPES
 ****************************************************************************
 */

/*
 *===========================================================================
 *                         runtime global enabler/disablers
 *===========================================================================
 */
IP_EXTERN int ipipsec_conf_enable_outfilter;
IP_EXTERN int ipipsec_conf_enable_infilter;
IP_EXTERN int ipipsec_conf_esp_enable;
IP_EXTERN int ipipsec_conf_ah_enable;
IP_EXTERN int ipipsec_conf_ipip_allow;
#ifdef IPIPSEC_USE_TFC
IP_EXTERN int ipipsec_max_tfc_bytes;
IP_EXTERN int ipipsec_max_tfc_delay;
IP_EXTERN int ipipsec_min_tfc_delay;
IP_EXTERN int ipipsec_max_dummy_payload;
#endif

/* not runtime */
IP_EXTERN int ipipsec_conf_num_cpus;
IP_EXTERN int ipipsec_conf_sa_cache_maxsize;
IP_EXTERN int ipipsec_conf_flow_cache_maxsize;
#ifdef IPIPSEC_USE_ESN
IP_EXTERN int ipipsec_conf_esn_resync_trigger;
#endif


#ifdef __cplusplus
}
#endif

#endif


/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
