while(1){

            DS = UART5_read();

                if (DS=='$')

                {

                      a =UART5_read();

                    if (a=='G')

                    {

                       // while (R_isEmpty()){};



                          a1 =UART5_read();



                            if (a1=='P')

                            {

                               // while (R_isEmpty()){};



                             a2 =UART5_read();



                                if (a2=='R')

                                {

                                    //while (R_isEmpty()){};



                               a3 =UART5_read();





                                  if (a3 =='M')

                                  {

                                    //while (R_isEmpty()){};



                               a4 =UART5_read();



                                        if (a4 =='C')

                                    {

                                      //while (R_isEmpty()){};



                                 a5 =UART5_read();



                                          if (a5 ==',')

                                    {

                                        //while (R_isEmpty()){};



                                   a6 =UART5_read();



                                            while (a6 !='*')

                                        {

                                                     gValues[in]=a6;

                                          //while (R_isEmpty()){};



                                      a6 =UART5_read();

                                            in++;

                                        }

                                        