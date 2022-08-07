if (DEFINED ENV{PICO_MBEDTLS_PATH} AND (NOT PICO_MBEDTLS_PATH))
    set(PICO_MBEDTLS_PATH $ENV{PICO_MBEDTLS_PATH})
    message("Using PICO_MBEDTLS_PATH from environment ('${PICO_MBEDTLS_PATH}')")
endif ()

if (NOT PICO_MBEDTLS_PATH)
    set(PICO_MBEDTLS_PATH ${PROJECT_SOURCE_DIR}/lib/mbedtls)
endif ()

if (EXISTS ${PICO_MBEDTLS_PATH}/CMakeLists.txt)
    message("mbedtls available at ${PICO_MBEDTLS_PATH}")
    add_library(pico_mbedtls INTERFACE)

    target_include_directories(pico_mbedtls INTERFACE
        ${PICO_MBEDTLS_PATH}/include
    )

    target_sources(pico_mbedtls INTERFACE
#       ${MICROPY_DIR}/lib/mbedtls_errors/mp_mbedtls_errors.c
        ${CMAKE_CURRENT_LIST_DIR}/mbedtls_port.c
        ${PICO_MBEDTLS_PATH}/library/aes.c
        ${PICO_MBEDTLS_PATH}/library/aesni.c
        ${PICO_MBEDTLS_PATH}/library/arc4.c
        ${PICO_MBEDTLS_PATH}/library/asn1parse.c
        ${PICO_MBEDTLS_PATH}/library/asn1write.c
        ${PICO_MBEDTLS_PATH}/library/base64.c
        ${PICO_MBEDTLS_PATH}/library/bignum.c
        ${PICO_MBEDTLS_PATH}/library/blowfish.c
        ${PICO_MBEDTLS_PATH}/library/camellia.c
        ${PICO_MBEDTLS_PATH}/library/ccm.c
        ${PICO_MBEDTLS_PATH}/library/certs.c
        ${PICO_MBEDTLS_PATH}/library/chacha20.c
        ${PICO_MBEDTLS_PATH}/library/chachapoly.c
        ${PICO_MBEDTLS_PATH}/library/cipher.c
        ${PICO_MBEDTLS_PATH}/library/cipher_wrap.c
        ${PICO_MBEDTLS_PATH}/library/cmac.c
        ${PICO_MBEDTLS_PATH}/library/ctr_drbg.c
        ${PICO_MBEDTLS_PATH}/library/debug.c
        ${PICO_MBEDTLS_PATH}/library/des.c
        ${PICO_MBEDTLS_PATH}/library/dhm.c
        ${PICO_MBEDTLS_PATH}/library/ecdh.c
        ${PICO_MBEDTLS_PATH}/library/ecdsa.c
        ${PICO_MBEDTLS_PATH}/library/ecjpake.c
        ${PICO_MBEDTLS_PATH}/library/ecp.c
        ${PICO_MBEDTLS_PATH}/library/ecp_curves.c
        ${PICO_MBEDTLS_PATH}/library/entropy.c
        ${PICO_MBEDTLS_PATH}/library/entropy_poll.c
        ${PICO_MBEDTLS_PATH}/library/gcm.c
        ${PICO_MBEDTLS_PATH}/library/havege.c
        ${PICO_MBEDTLS_PATH}/library/hmac_drbg.c
        ${PICO_MBEDTLS_PATH}/library/md2.c
        ${PICO_MBEDTLS_PATH}/library/md4.c
        ${PICO_MBEDTLS_PATH}/library/md5.c
        ${PICO_MBEDTLS_PATH}/library/md.c
        ${PICO_MBEDTLS_PATH}/library/md_wrap.c
        ${PICO_MBEDTLS_PATH}/library/oid.c
        ${PICO_MBEDTLS_PATH}/library/padlock.c
        ${PICO_MBEDTLS_PATH}/library/pem.c
        ${PICO_MBEDTLS_PATH}/library/pk.c
        ${PICO_MBEDTLS_PATH}/library/pkcs11.c
        ${PICO_MBEDTLS_PATH}/library/pkcs12.c
        ${PICO_MBEDTLS_PATH}/library/pkcs5.c
        ${PICO_MBEDTLS_PATH}/library/pkparse.c
        ${PICO_MBEDTLS_PATH}/library/pk_wrap.c
        ${PICO_MBEDTLS_PATH}/library/pkwrite.c
        ${PICO_MBEDTLS_PATH}/library/platform.c
        ${PICO_MBEDTLS_PATH}/library/platform_util.c
        ${PICO_MBEDTLS_PATH}/library/poly1305.c
        ${PICO_MBEDTLS_PATH}/library/ripemd160.c
        ${PICO_MBEDTLS_PATH}/library/rsa.c
        ${PICO_MBEDTLS_PATH}/library/rsa_internal.c
        ${PICO_MBEDTLS_PATH}/library/sha1.c
        ${PICO_MBEDTLS_PATH}/library/sha256.c
        ${PICO_MBEDTLS_PATH}/library/sha512.c
        ${PICO_MBEDTLS_PATH}/library/ssl_cache.c
        ${PICO_MBEDTLS_PATH}/library/ssl_ciphersuites.c
        ${PICO_MBEDTLS_PATH}/library/ssl_cli.c
        ${PICO_MBEDTLS_PATH}/library/ssl_cookie.c
        ${PICO_MBEDTLS_PATH}/library/ssl_srv.c
        ${PICO_MBEDTLS_PATH}/library/ssl_ticket.c
        ${PICO_MBEDTLS_PATH}/library/ssl_tls.c
        ${PICO_MBEDTLS_PATH}/library/timing.c
        ${PICO_MBEDTLS_PATH}/library/x509.c
        ${PICO_MBEDTLS_PATH}/library/x509_create.c
        ${PICO_MBEDTLS_PATH}/library/x509_crl.c
        ${PICO_MBEDTLS_PATH}/library/x509_crt.c
        ${PICO_MBEDTLS_PATH}/library/x509_csr.c
        ${PICO_MBEDTLS_PATH}/library/x509write_crt.c
        ${PICO_MBEDTLS_PATH}/library/x509write_csr.c
        ${PICO_MBEDTLS_PATH}/library/xtea.c
    )

    target_compile_definitions(pico_mbedtls INTERFACE
        MBEDTLS_CONFIG_FILE="${CMAKE_CURRENT_LIST_DIR}/mbedtls_config.h"
    )

    target_link_libraries(pico_mbedtls INTERFACE hardware_rtc)
endif()
