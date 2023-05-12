int test_and_set ( int *mem) {   
      if (*mem == 0)  {     // the lock is available
               *mem = 1;       // grab the lock
                return 0          // return a value to end the spinning WHILE
      }
        else {                     // the lock is occupied -- not available
                 return 1        // return a value to keep the WHILE spinning
       }

// ======================================
int compare_and_exchange (
               cae_t      *mem,
               int           compare_value,
               int           swap_value )    {

    int ret_value = 0;
  
    // spin while the lock is not available;  return a 0 when lock is grabbed
    while (test_and_set(&mem-->lock)) 
       { //SPIN  }

      if (compare_value == mem-->value)  {
                 mem-->value = swap_value;
                 ret_value = 1;
      } // IF

      else {                //  DON'T THINK THIS 'else' IS NECESSARY
                 ret_value = 0;   
      }
     
      //release the lock
      mem-->lock =0;
      return ret_value

} END FUNCTION compare_and_exchange
// ----------------------------------------

