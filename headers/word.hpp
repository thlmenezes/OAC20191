/**
 * id      17/0045919
 * author  Thales Menezes
 * GitHub  @thaleslim
 * date    01/05/2019
 * brief   Define basic word
 * manipulation procedures.
 */

#ifndef __WORD_HPP__
#define __WORD_HPP__

#include <stdint.h>

inline int32_t  extend_signal(int32_t word, uint32_t wsize);
inline int32_t  get_field    (int32_t word, uint32_t index, uint32_t mask);
inline int32_t  set_field    (int32_t word, uint32_t index, uint32_t mask, int32_t value);


//--------------------------------------------------------------
inline int32_t  extend_signal(int32_t word, uint32_t wsize){
    /**
     * Signal extension method
     * if ( word < 0 )
     *      extend 1
     * else
     *      extend 0
     */
    return word >> (wsize-1) ? word | (-1 << wsize) : word;
}//End extend_signal()

//--------------------------------------------------------------
inline int32_t  get_field(int32_t word, uint32_t index, uint32_t mask){
    /**
     * Isolate \a{mask} bytes from \a{word}, startin' from \a{index}
     */
    return word >> index & mask;
}//End get_field()

//--------------------------------------------------------------
inline int32_t  set_field(int32_t word, uint32_t index, uint32_t mask, int32_t value){
    /**
     * Inserts \a{mask} bytes from \a{value} to \a{word}, startin' from \a{index}
     */
    return (word & ~(mask << index)) | ((value & mask) << index);
}//End set_field()

#endif