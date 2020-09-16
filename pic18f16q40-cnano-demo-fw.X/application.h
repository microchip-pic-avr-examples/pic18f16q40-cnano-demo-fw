/* 
 * File:   application.h
 * Author: C16783
 *
 * Created on September 2, 2020, 10:28 AM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

#ifdef	__cplusplus
extern "C" {
#endif

    int16_t gain, offset = 0;
    uint16_t adcc_meas = 0;
    int24_t tempC = 0;

    void IntroSplashMessage(void);
    void TempIndicator_Init(void);
    void TempIndicator_Calc(void);

#ifdef	__cplusplus
}
#endif

#endif	/* APPLICATION_H */

