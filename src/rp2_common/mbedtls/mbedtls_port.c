#include "mbedtls_config.h"

#include "hardware/rtc.h"
#include "hardware/structs/rosc.h"

#define POLY (0xD5)

uint8_t pico_random_byte(int cycles) {
    static uint8_t byte;
    assert(cycles >= 8);
    assert(rosc_hw->status & ROSC_STATUS_ENABLED_BITS);
    for(int i=0;i<cycles;i++) {
        // picked a fairly arbitrary polynomial of 0x35u - this doesn't have to be crazily uniform.
        byte = ((byte << 1) | rosc_hw->randombit) ^ (byte & 0x80u ? 0x35u : 0);
        // delay a little because the random bit is a little slow
        busy_wait_at_least_cycles(30);
    }
    return byte;
}


int mbedtls_hardware_poll(void *data, unsigned char *output, size_t len, size_t *olen) {
    *olen = len;
    for (size_t i = 0; i < len; i++) {
        output[i] = pico_random_byte(8);
    }
    return 0;
}

// copy pasted from micropython/shared/timeutils/timeutils.h

#define TIMEUTILS_SECONDS_1970_TO_2000 (946684800ULL)

static const uint16_t days_since_jan1[] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };

bool timeutils_is_leap_year(uint16_t year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

uint16_t timeutils_year_day(uint16_t year, uint16_t month, uint16_t date) {
    uint16_t yday = days_since_jan1[month - 1] + date;
    if (month >= 3 && timeutils_is_leap_year(year)) {
        yday += 1;
    }
    return yday;
}

uint64_t timeutils_seconds_since_2000(uint64_t year, uint64_t month,
    uint64_t date, uint64_t hour, uint64_t minute, uint64_t second) {
    return
        second
        + minute * 60
        + hour * 3600
        + (timeutils_year_day(year, month, date) - 1
            + ((year - 2000 + 3) / 4) // add a day each 4 years starting with 2001
            - ((year - 2000 + 99) / 100) // subtract a day each 100 years starting with 2001
            + ((year - 2000 + 399) / 400) // add a day each 400 years starting with 2001
            ) * 86400
        + (year - 2000) * 31536000;
}

time_t rp2_rtctime_seconds(time_t *timer) {
    datetime_t t;
    rtc_get_datetime(&t);
    return timeutils_seconds_since_2000(t.year, t.month, t.day, t.hour, t.min, t.sec) + TIMEUTILS_SECONDS_1970_TO_2000;
}

void m_tracked_free(void *ptr_in) {
    if (ptr_in == NULL) {
        return;
    }
    free(ptr_in);
}

void *m_tracked_calloc(size_t nmemb, size_t size) {
  return calloc(nmemb, size);
}
