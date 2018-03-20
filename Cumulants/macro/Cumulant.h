#ifndef CUMULANT_H
#define CUMULANT_H

#include <iostream>
#include <vector>

//___________________________________________________
//
// Compute cumulants
//___________________________________________________
void cumulant(const std::vector< std::vector< std::vector<double> > > &qNM,
              const std::vector< std::vector< std::vector<double> > > &wqNM,
              std::vector< std::vector<double> > &cNM,
              std::vector< std::vector<double> > &wcNM,
              int order, int harm0, int harm1, int inoff, int iref, int nsub)
{
//           order 0: 17
//           order 1: 51
//           order 2: 119
//           order 3: 11111111
//           order 4: 33
//           order 5: 18
//           order 6: 34
//           order 7: 20
//           order 8: 36  
// for four
//           order 9: 53
//           order 10: 58
//           order 11: 60
//           order 12: 83
//           order 13: 85
//           order 14: 90
//           order 15: 99
//           order 16: 101
//           order 17: 108
//           order 18: 163
//           order 19: 165
//           order 20: 170
// for six
//           order 21: 123
//           order 22: 125
//           order 23: 183
//           order 24: 187
//           order 25: 231
//           order 26: 237
   if( nsub <= 2 && harm0==harm1) // 2-subevent cumulant
   {
      switch(order)
      {
         case 0:
            if( wqNM[0][inoff][iref] != 0. )
            {
               cNM[order][inoff]  += ( qNM[0][inoff][iref] / wqNM[0][inoff][iref] ) // <<2>> 
                                      *wqNM[0][inoff][iref];
               wcNM[order][inoff] += wqNM[0][inoff][iref];
            }
            break;
         case 1:
            if( wqNM[1][inoff][iref] != 0.)
            {
               cNM[order][inoff]  += ( qNM[1][inoff][iref]   / wqNM[1][inoff][iref] -   //   <<4>>
                                     2*qNM[0][inoff][iref] / wqNM[0][inoff][iref]   //-2*<<2>>^{2}
                                      *qNM[0][inoff][iref] / wqNM[0][inoff][iref] ) 
                                      *wqNM[1][inoff][iref];
               wcNM[order][inoff] += wqNM[1][inoff][iref];
            }
            break;
         case 2:
            if( wqNM[2][inoff][iref] != 0. )
            {
               cNM[order][inoff]  += ( qNM[2][inoff][iref]   / wqNM[2][inoff][iref]   - //    <<6>>
                                     9*qNM[1][inoff][iref] / wqNM[1][inoff][iref]   //- 9*<<4>><<2>>
                                      *qNM[0][inoff][iref] / wqNM[0][inoff][iref] + //
                                    12*qNM[0][inoff][iref] / wqNM[0][inoff][iref]   //+12*<<2>>^{3}
                                      *qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[0][inoff][iref] / wqNM[0][inoff][iref] ) 
                                      *wqNM[2][inoff][iref];
               wcNM[order][inoff] += wqNM[2][inoff][iref];
            }
            break;
         case 3:
            if( wqNM[3][inoff][iref] != 0. )
            {
               cNM[order][inoff]  += ( qNM[3][inoff][iref]   / wqNM[3][inoff][iref]   - //     <<8>>
                                    16*qNM[2][inoff][iref] / wqNM[2][inoff][iref]   //- 16*<<6>><<2>>
                                      *qNM[0][inoff][iref] / wqNM[0][inoff][iref] - //
                                    18*qNM[1][inoff][iref] / wqNM[1][inoff][iref]   //- 18*<<4>>^{2}
                                      *qNM[1][inoff][iref] / wqNM[1][inoff][iref] + //
                                   144*qNM[1][inoff][iref] / wqNM[1][inoff][iref]   //+144*<<4>><<2>>^{2}
                                      *qNM[0][inoff][iref] / wqNM[0][inoff][iref]   //
                                      *qNM[0][inoff][iref] / wqNM[0][inoff][iref] - //-144*<<2>>^{4}
                                   144*qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[0][inoff][iref] / wqNM[0][inoff][iref] )
                                      *wqNM[3][inoff][iref];
               wcNM[order][inoff] += wqNM[3][inoff][iref];
            }
            break;
         default:
            LOG_S(ERROR) << "Not defined order";
            break;
      }
   }
   else if(harm0!=harm1) //symmetric cumulant
   {
      switch(order)
      {
         case 0:
            if( wqNM[2][inoff][iref] != 0. )
            {
               cNM[order][inoff]  += ( qNM[2][inoff][iref] / wqNM[2][inoff][iref] ) // <<2>>_33 not really useful in the case of symmetic cumulant
                                      *wqNM[2][inoff][iref];
               wcNM[order][inoff] += wqNM[2][inoff][iref];
            }
            break;
         case 1:
            if( wqNM[1][inoff][iref] != 0.)
            {
               cNM[order][inoff]  += ( qNM[1][inoff][iref] / wqNM[1][inoff][iref] -  // <<4>>-<<34>>*<<17>>
                                       qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[4][inoff][iref] / wqNM[4][inoff][iref]
                                      )
                                      *wqNM[1][inoff][iref];
               wcNM[order][inoff] += wqNM[1][inoff][iref];
            }
            break;
         default:
            LOG_S(ERROR) << "Not defined order";
            break;
      }
   }
   else if(nsub==3 && harm0==harm1)
   {
      switch(order)
      {
         case 0:
            if( wqNM[4][inoff][iref] != 0. )
            {
               cNM[order][inoff]  += ( qNM[4][inoff][iref] / wqNM[4][inoff][iref] ) // <<2>>_33 not really useful in the case of nsub=3 
                                      *wqNM[4][inoff][iref];
               wcNM[order][inoff] += wqNM[4][inoff][iref];
            }
            break;
         case 1:
            if( wqNM[1][inoff][iref] != 0.)
            {
               cNM[order][inoff]  += ( qNM[1][inoff][iref]   / wqNM[1][inoff][iref] -  // <<4>>-2<<33>>*<<17>>
                                       2*qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[4][inoff][iref] / wqNM[4][inoff][iref] 
                                      )
                                      *wqNM[1][inoff][iref];
               wcNM[order][inoff] += wqNM[1][inoff][iref];
            }
            break;
         case 2:
            if( wqNM[2][inoff][iref]   != 0. ) 
            {
               cNM[order][inoff]  += ( qNM[2][inoff][iref]   / wqNM[2][inoff][iref]   - //    <<6>>
                                     2*qNM[1][inoff][iref] / wqNM[1][inoff][iref]   
                                      *qNM[8][inoff][iref] / wqNM[8][inoff][iref] - 
                                       qNM[7][inoff][iref] / wqNM[7][inoff][iref]   
                                      *qNM[15][inoff][iref] / wqNM[15][inoff][iref] - 
                                     4*qNM[9][inoff][iref] / wqNM[9][inoff][iref]
                                      *qNM[4][inoff][iref] / wqNM[4][inoff][iref] -
                                     2*qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[16][inoff][iref] / wqNM[16][inoff][iref] +
                                     8*qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[4][inoff][iref] / wqNM[4][inoff][iref] 
                                      *qNM[8][inoff][iref] / wqNM[8][inoff][iref] +
                                     4*qNM[7][inoff][iref] / wqNM[7][inoff][iref]
                                      *qNM[4][inoff][iref] / wqNM[4][inoff][iref] 
                                      *qNM[4][inoff][iref] / wqNM[4][inoff][iref] ) 
                                      *wqNM[2][inoff][iref];
               wcNM[order][inoff] += wqNM[2][inoff][iref];
            }
            break;
         case 3:
            if( wqNM[3][inoff][iref]   != 0. )
            {
               cNM[order][inoff]  += ( qNM[3][inoff][iref]   / wqNM[3][inoff][iref]   - //    <<8>>
                                       qNM[6][inoff][iref] / wqNM[6][inoff][iref]
                                      *qNM[13][inoff][iref] / wqNM[13][inoff][iref] -
                                     2*qNM[4][inoff][iref] / wqNM[4][inoff][iref]
                                      *qNM[12][inoff][iref] / wqNM[12][inoff][iref] -
                                     2*qNM[9][inoff][iref] / wqNM[9][inoff][iref]
                                      *qNM[5][inoff][iref] / wqNM[5][inoff][iref] -
                                     4*qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[1][inoff][iref] / wqNM[1][inoff][iref] +
                                     8*qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[4][inoff][iref] / wqNM[4][inoff][iref]
                                      *qNM[5][inoff][iref] / wqNM[5][inoff][iref] +
                                     4*qNM[6][inoff][iref] / wqNM[6][inoff][iref]
                                      *qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[0][inoff][iref] / wqNM[0][inoff][iref] )
                                      *wqNM[3][inoff][iref];
               wcNM[order][inoff] += wqNM[3][inoff][iref];
            }
            break;
         default:
            LOG_S(ERROR) << "Not defined order";
            break;
      }
   }
   else if(nsub==4 && harm0==harm1)
   {
      switch(order)
      {
         case 0:
            if( wqNM[4][inoff][iref] != 0. )
            {
               cNM[order][inoff]  += ( qNM[4][inoff][iref] / wqNM[4][inoff][iref] ) // <<2>>_33 not really useful in the case of nsub=4 
                                      *wqNM[4][inoff][iref];
               wcNM[order][inoff] += wqNM[4][inoff][iref];
            }
            break;
         case 1:
            if( wqNM[1][inoff][iref] != 0. )
            {
               cNM[order][inoff]  += ( qNM[1][inoff][iref]   / wqNM[1][inoff][iref] -  // <<4>>-<<33>>*<<18>>-<<34>>*<<17>>
                                       qNM[4][inoff][iref] / wqNM[4][inoff][iref]
                                      *qNM[5][inoff][iref] / wqNM[5][inoff][iref] -
                                       qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[6][inoff][iref] / wqNM[6][inoff][iref]
                                      )
                                      *wqNM[1][inoff][iref];
               wcNM[order][inoff] += wqNM[1][inoff][iref];
            }
            break;
         case 2:
            if( wqNM[2][inoff][iref] != 0. )
            {
               cNM[order][inoff]  += ( qNM[2][inoff][iref]   / wqNM[2][inoff][iref]   - //    <<6>>
                                     3*qNM[4][inoff][iref] / wqNM[4][inoff][iref]  
                                      *qNM[22][inoff][iref] / wqNM[22][inoff][iref] - 
                                     3*qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[26][inoff][iref] / wqNM[26][inoff][iref] -
                                     6*qNM[2][inoff][iref] / wqNM[2][inoff][iref]
                                      *qNM[8][inoff][iref] / wqNM[8][inoff][iref] -
                                     2*qNM[7][inoff][iref] / wqNM[7][inoff][iref]
                                      *qNM[25][inoff][iref] / wqNM[25][inoff][iref] -
                                     3*qNM[11][inoff][iref] / wqNM[11][inoff][iref]
                                      *qNM[15][inoff][iref] / wqNM[15][inoff][iref] -
                                     3*qNM[1][inoff][iref] / wqNM[1][inoff][iref]
                                      *qNM[17][inoff][iref] / wqNM[17][inoff][iref] -
                                    12*qNM[9][inoff][iref] / wqNM[9][inoff][iref]
                                      *qNM[15][inoff][iref] / wqNM[15][inoff][iref] +
                                    12*qNM[1][inoff][iref] / wqNM[1][inoff][iref]  
                                      *qNM[8][inoff][iref] / wqNM[8][inoff][iref]
                                      *qNM[8][inoff][iref] / wqNM[8][inoff][iref] +
                                    12*qNM[11][inoff][iref] / wqNM[11][inoff][iref]
                                      *qNM[4][inoff][iref] / wqNM[4][inoff][iref]
                                      *qNM[4][inoff][iref] / wqNM[4][inoff][iref] +
                                    12*qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[4][inoff][iref] / wqNM[4][inoff][iref]
                                      *qNM[17][inoff][iref] / wqNM[17][inoff][iref] +
                                    48*qNM[4][inoff][iref] / wqNM[4][inoff][iref]
                                      *qNM[7][inoff][iref] / wqNM[7][inoff][iref]
                                      *qNM[15][inoff][iref] / wqNM[15][inoff][iref] +
                                    24*qNM[4][inoff][iref] / wqNM[4][inoff][iref]
                                      *qNM[8][inoff][iref] / wqNM[8][inoff][iref]
                                      *qNM[9][inoff][iref] / wqNM[9][inoff][iref] +
                                    24*qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[8][inoff][iref] / wqNM[8][inoff][iref]
                                      *qNM[15][inoff][iref] / wqNM[15][inoff][iref] +
                                    12*qNM[4][inoff][iref] / wqNM[4][inoff][iref]
                                      *qNM[7][inoff][iref] / wqNM[7][inoff][iref]
                                      *qNM[15][inoff][iref] / wqNM[15][inoff][iref] -
                                    72*qNM[7][inoff][iref] / wqNM[7][inoff][iref]
                                      *qNM[8][inoff][iref] / wqNM[8][inoff][iref]
                                      *qNM[4][inoff][iref] / wqNM[4][inoff][iref]
                                      *qNM[4][inoff][iref] / wqNM[4][inoff][iref] -
                                    72*qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[4][inoff][iref] / wqNM[4][inoff][iref]
                                      *qNM[8][inoff][iref] / wqNM[8][inoff][iref]
                                      *qNM[8][inoff][iref] / wqNM[8][inoff][iref] )
                                      *wqNM[2][inoff][iref];
               wcNM[order][inoff] += wqNM[2][inoff][iref];
            }
            break;
         case 3:
            if( wqNM[3][inoff][iref] != 0. )
            {
               cNM[order][inoff]  += ( qNM[3][inoff][iref]   / wqNM[3][inoff][iref]   - //     <<8>>
                                     4*qNM[4][inoff][iref] / wqNM[4][inoff][iref]   
                                      *qNM[21][inoff][iref] / wqNM[21][inoff][iref] - 
                                     4*qNM[24][inoff][iref] / wqNM[24][inoff][iref]   
                                      *qNM[17][inoff][iref] / wqNM[17][inoff][iref] -
                                     4*qNM[2][inoff][iref] / wqNM[2][inoff][iref]   
                                      *qNM[6][inoff][iref] / wqNM[6][inoff][iref] -
                                     4*qNM[23][inoff][iref] / wqNM[23][inoff][iref]   
                                      *qNM[5][inoff][iref] / wqNM[5][inoff][iref] -
                                     8*qNM[1][inoff][iref] / wqNM[1][inoff][iref]   
                                      *qNM[1][inoff][iref] / wqNM[1][inoff][iref] -
                                       qNM[14][inoff][iref] / wqNM[14][inoff][iref]   
                                      *qNM[19][inoff][iref] / wqNM[19][inoff][iref] -
                                       qNM[13][inoff][iref] / wqNM[13][inoff][iref]   
                                      *qNM[20][inoff][iref] / wqNM[20][inoff][iref] -
                                     4*qNM[9][inoff][iref] / wqNM[9][inoff][iref]   
                                      *qNM[10][inoff][iref] / wqNM[10][inoff][iref] -
                                     4*qNM[12][inoff][iref] / wqNM[12][inoff][iref]   
                                      *qNM[18][inoff][iref] / wqNM[18][inoff][iref] + 
                                    32*qNM[1][inoff][iref] / wqNM[1][inoff][iref]
                                      *qNM[4][inoff][iref] / wqNM[4][inoff][iref]
                                      *qNM[5][inoff][iref] / wqNM[5][inoff][iref] +
                                    32*qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[1][inoff][iref] / wqNM[1][inoff][iref]
                                      *qNM[6][inoff][iref] / wqNM[6][inoff][iref] + 
                                     4*qNM[14][inoff][iref] / wqNM[14][inoff][iref]
                                      *qNM[4][inoff][iref] / wqNM[4][inoff][iref]
                                      *qNM[4][inoff][iref] / wqNM[4][inoff][iref] + 
                                     4*qNM[19][inoff][iref] / wqNM[19][inoff][iref]
                                      *qNM[5][inoff][iref] / wqNM[5][inoff][iref]
                                      *qNM[5][inoff][iref] / wqNM[5][inoff][iref] +
                                     4*qNM[13][inoff][iref] / wqNM[13][inoff][iref]
                                      *qNM[6][inoff][iref] / wqNM[6][inoff][iref]
                                      *qNM[6][inoff][iref] / wqNM[6][inoff][iref] + 
                                     4*qNM[20][inoff][iref] / wqNM[20][inoff][iref]
                                      *qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[0][inoff][iref] / wqNM[0][inoff][iref] + 
                                    16*qNM[10][inoff][iref] / wqNM[10][inoff][iref]
                                      *qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[4][inoff][iref] / wqNM[4][inoff][iref] + 
                                    16*qNM[9][inoff][iref] / wqNM[9][inoff][iref]
                                      *qNM[5][inoff][iref] / wqNM[5][inoff][iref]
                                      *qNM[6][inoff][iref] / wqNM[6][inoff][iref] + 
                                    16*qNM[12][inoff][iref] / wqNM[12][inoff][iref]
                                      *qNM[6][inoff][iref] / wqNM[6][inoff][iref]
                                      *qNM[4][inoff][iref] / wqNM[4][inoff][iref] + 
                                    16*qNM[18][inoff][iref] / wqNM[18][inoff][iref]   
                                      *qNM[5][inoff][iref] / wqNM[5][inoff][iref]  
                                      *qNM[0][inoff][iref] / wqNM[0][inoff][iref] -
                                    72*qNM[5][inoff][iref] / wqNM[5][inoff][iref]
                                      *qNM[6][inoff][iref] / wqNM[6][inoff][iref]
                                      *qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[4][inoff][iref] / wqNM[4][inoff][iref] -
                                    36*qNM[5][inoff][iref] / wqNM[5][inoff][iref]
                                      *qNM[5][inoff][iref] / wqNM[5][inoff][iref]
                                      *qNM[4][inoff][iref] / wqNM[4][inoff][iref]
                                      *qNM[4][inoff][iref] / wqNM[4][inoff][iref] -
                                    36*qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[6][inoff][iref] / wqNM[6][inoff][iref]
                                      *qNM[6][inoff][iref] / wqNM[6][inoff][iref] )
                                      *wqNM[3][inoff][iref];
               wcNM[order][inoff] += wqNM[3][inoff][iref];
            }
            break;
         default:
            LOG_S(ERROR) << "Not defined order";
            break;
      }
   }
}

void uncumulant(const std::vector< std::vector< std::vector<double> > > &qNM,
                const std::vector< std::vector< std::vector<double> > > &wqNM,
                std::vector< std::vector<double> > &cNM,
                std::vector< std::vector<double> > &wcNM,
                int order, int harm0, int harm1, int inoff, int iref, int nsub)
{
//           order 0: 17
//           order 1: 51
//           order 2: 119
//           order 3: 11111111
//           order 4: 33
//           order 5: 18
//           order 6: 34
//           order 7: 20
//           order 8: 36  
// for four
//           order 9: 53
//           order 10: 58
//           order 11: 60
//           order 12: 83
//           order 13: 85
//           order 14: 90
//           order 15: 99
//           order 16: 101
//           order 17: 108
//           order 18: 163
//           order 19: 165
//           order 20: 170
// for six
//           order 21: 123
//           order 22: 125
//           order 23: 183
//           order 24: 187
//           order 25: 231
//           order 26: 237
   if( nsub <= 2 && harm0==harm1) // 2-subevent cumulant
   {
      switch(order)
      {
         case 0:
            if( wqNM[0][inoff][iref] != 0. )
            {
               cNM[order][inoff]  -= ( qNM[0][inoff][iref] / wqNM[0][inoff][iref] ) // <<2>> 
                                      *wqNM[0][inoff][iref];
               wcNM[order][inoff] -= wqNM[0][inoff][iref];
            }
            break;
         case 1:
            if( wqNM[1][inoff][iref] != 0.)
            {
               cNM[order][inoff]  -= ( qNM[1][inoff][iref]   / wqNM[1][inoff][iref] -   //   <<4>>
                                     2*qNM[0][inoff][iref] / wqNM[0][inoff][iref]   //-2*<<2>>^{2}
                                      *qNM[0][inoff][iref] / wqNM[0][inoff][iref] ) 
                                      *wqNM[1][inoff][iref];
               wcNM[order][inoff] -= wqNM[1][inoff][iref];
            }
            break;
         case 2:
            if( wqNM[2][inoff][iref] != 0. )
            {
               cNM[order][inoff]  -= ( qNM[2][inoff][iref]   / wqNM[2][inoff][iref]   - //    <<6>>
                                     9*qNM[1][inoff][iref] / wqNM[1][inoff][iref]   //- 9*<<4>><<2>>
                                      *qNM[0][inoff][iref] / wqNM[0][inoff][iref] + //
                                    12*qNM[0][inoff][iref] / wqNM[0][inoff][iref]   //+12*<<2>>^{3}
                                      *qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[0][inoff][iref] / wqNM[0][inoff][iref] ) 
                                      *wqNM[2][inoff][iref];
               wcNM[order][inoff] -= wqNM[2][inoff][iref];
            }
            break;
         case 3:
            if( wqNM[3][inoff][iref] != 0. )
            {
               cNM[order][inoff]  -= ( qNM[3][inoff][iref]   / wqNM[3][inoff][iref]   - //     <<8>>
                                    16*qNM[2][inoff][iref] / wqNM[2][inoff][iref]   //- 16*<<6>><<2>>
                                      *qNM[0][inoff][iref] / wqNM[0][inoff][iref] - //
                                    18*qNM[1][inoff][iref] / wqNM[1][inoff][iref]   //- 18*<<4>>^{2}
                                      *qNM[1][inoff][iref] / wqNM[1][inoff][iref] + //
                                   144*qNM[1][inoff][iref] / wqNM[1][inoff][iref]   //+144*<<4>><<2>>^{2}
                                      *qNM[0][inoff][iref] / wqNM[0][inoff][iref]   //
                                      *qNM[0][inoff][iref] / wqNM[0][inoff][iref] - //-144*<<2>>^{4}
                                   144*qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[0][inoff][iref] / wqNM[0][inoff][iref] )
                                      *wqNM[3][inoff][iref];
               wcNM[order][inoff] -= wqNM[3][inoff][iref];
            }
            break;
         default:
            LOG_S(ERROR) << "Not defined order";
            break;
      }
   }
   else if(harm0!=harm1) //symmetric cumulant
   {
      switch(order)
      {
         case 0:
            if( wqNM[4][inoff][iref] != 0. )
            {
               cNM[order][inoff]  -= ( qNM[2][inoff][iref] / wqNM[2][inoff][iref] ) // <<2>>_33 not really useful in the case of symmetic cumulant
                                      *wqNM[2][inoff][iref];
               wcNM[order][inoff] -= wqNM[2][inoff][iref];
            }
            break;
         case 1:
            if( wqNM[1][inoff][iref] != 0.)
            {
               cNM[order][inoff]  -= ( qNM[1][inoff][iref] / wqNM[1][inoff][iref] -  // <<4>>-<<33>>*<<18>>-<<34>>*<<17>>
                                       qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[4][inoff][iref] / wqNM[4][inoff][iref]
                                      )
                                      *wqNM[1][inoff][iref];
               wcNM[order][inoff] -= wqNM[1][inoff][iref];
            }
            break;
         default:
            LOG_S(ERROR) << "Not defined order";
            break;
      }
   }
   else if(nsub==3 && harm0==harm1)
   {
      switch(order)
      {
         case 0:
            if( wqNM[4][inoff][iref] != 0. )
            {
               cNM[order][inoff]  -= ( qNM[4][inoff][iref] / wqNM[4][inoff][iref] ) // <<2>>_33 not really useful in the case of nsub=3 
                                      *wqNM[4][inoff][iref];
               wcNM[order][inoff] -= wqNM[4][inoff][iref];
            }
            break;
         case 1:
            if( wqNM[1][inoff][iref] != 0.)
            {
               cNM[order][inoff]  -= ( qNM[1][inoff][iref]   / wqNM[1][inoff][iref] -  // <<4>>-2<<33>>*<<17>>
                                       2*qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[4][inoff][iref] / wqNM[4][inoff][iref] 
                                      )
                                      *wqNM[1][inoff][iref];
               wcNM[order][inoff] -= wqNM[1][inoff][iref];
            }
            break;
         case 2:
            if( wqNM[2][inoff][iref]   != 0. ) 
            {
               cNM[order][inoff]  -= ( qNM[2][inoff][iref]   / wqNM[2][inoff][iref]   - //    <<6>>
                                     2*qNM[1][inoff][iref] / wqNM[1][inoff][iref]   
                                      *qNM[8][inoff][iref] / wqNM[8][inoff][iref] - 
                                       qNM[7][inoff][iref] / wqNM[7][inoff][iref]   
                                      *qNM[15][inoff][iref] / wqNM[15][inoff][iref] - 
                                     4*qNM[9][inoff][iref] / wqNM[9][inoff][iref]
                                      *qNM[4][inoff][iref] / wqNM[4][inoff][iref] -
                                     2*qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[16][inoff][iref] / wqNM[16][inoff][iref] +
                                     8*qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[4][inoff][iref] / wqNM[4][inoff][iref] 
                                      *qNM[8][inoff][iref] / wqNM[8][inoff][iref] +
                                     4*qNM[7][inoff][iref] / wqNM[7][inoff][iref]
                                      *qNM[4][inoff][iref] / wqNM[4][inoff][iref] 
                                      *qNM[4][inoff][iref] / wqNM[4][inoff][iref] ) 
                                      *wqNM[2][inoff][iref];
               wcNM[order][inoff] -= wqNM[2][inoff][iref];
            }
            break;
         case 3:
            if( wqNM[3][inoff][iref]   != 0. )
            {
               cNM[order][inoff]  -= ( qNM[3][inoff][iref]   / wqNM[3][inoff][iref]   - //    <<8>>
                                       qNM[6][inoff][iref] / wqNM[6][inoff][iref]
                                      *qNM[13][inoff][iref] / wqNM[13][inoff][iref] -
                                     2*qNM[4][inoff][iref] / wqNM[4][inoff][iref]
                                      *qNM[12][inoff][iref] / wqNM[12][inoff][iref] -
                                     2*qNM[9][inoff][iref] / wqNM[9][inoff][iref]
                                      *qNM[5][inoff][iref] / wqNM[5][inoff][iref] -
                                     4*qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[1][inoff][iref] / wqNM[1][inoff][iref] +
                                     8*qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[4][inoff][iref] / wqNM[4][inoff][iref]
                                      *qNM[5][inoff][iref] / wqNM[5][inoff][iref] +
                                     4*qNM[6][inoff][iref] / wqNM[6][inoff][iref]
                                      *qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[0][inoff][iref] / wqNM[0][inoff][iref] )
                                      *wqNM[3][inoff][iref];
               wcNM[order][inoff] -= wqNM[3][inoff][iref];
            }
            break;
         default:
            LOG_S(ERROR) << "Not defined order";
            break;
      }
   }
   else if(nsub==4 && harm0==harm1)
   {
      switch(order)
      {
         case 0:
            if( wqNM[4][inoff][iref] != 0. )
            {
               cNM[order][inoff]  -= ( qNM[4][inoff][iref] / wqNM[4][inoff][iref] ) // <<2>>_33 not really useful in the case of nsub=4 
                                      *wqNM[4][inoff][iref];
               wcNM[order][inoff] -= wqNM[4][inoff][iref];
            }
            break;
         case 1:
            if( wqNM[1][inoff][iref] != 0. )
            {
               cNM[order][inoff]  -= ( qNM[1][inoff][iref]   / wqNM[1][inoff][iref] -  // <<4>>-<<33>>*<<18>>-<<34>>*<<17>>
                                       qNM[4][inoff][iref] / wqNM[4][inoff][iref]
                                      *qNM[5][inoff][iref] / wqNM[5][inoff][iref] -
                                       qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[6][inoff][iref] / wqNM[6][inoff][iref]
                                      )
                                      *wqNM[1][inoff][iref];
               wcNM[order][inoff] -= wqNM[1][inoff][iref];
            }
            break;
         case 2:
            if( wqNM[2][inoff][iref] != 0. )
            {
               cNM[order][inoff]  -= ( qNM[2][inoff][iref]   / wqNM[2][inoff][iref]   - //    <<6>>
                                     3*qNM[4][inoff][iref] / wqNM[4][inoff][iref]  
                                      *qNM[22][inoff][iref] / wqNM[22][inoff][iref] - 
                                     3*qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[26][inoff][iref] / wqNM[26][inoff][iref] -
                                     6*qNM[2][inoff][iref] / wqNM[2][inoff][iref]
                                      *qNM[8][inoff][iref] / wqNM[8][inoff][iref] -
                                     2*qNM[7][inoff][iref] / wqNM[7][inoff][iref]
                                      *qNM[25][inoff][iref] / wqNM[25][inoff][iref] -
                                     3*qNM[11][inoff][iref] / wqNM[11][inoff][iref]
                                      *qNM[15][inoff][iref] / wqNM[15][inoff][iref] -
                                     3*qNM[1][inoff][iref] / wqNM[1][inoff][iref]
                                      *qNM[17][inoff][iref] / wqNM[17][inoff][iref] -
                                    12*qNM[9][inoff][iref] / wqNM[9][inoff][iref]
                                      *qNM[15][inoff][iref] / wqNM[15][inoff][iref] +
                                    12*qNM[1][inoff][iref] / wqNM[1][inoff][iref]  
                                      *qNM[8][inoff][iref] / wqNM[8][inoff][iref]
                                      *qNM[8][inoff][iref] / wqNM[8][inoff][iref] +
                                    12*qNM[11][inoff][iref] / wqNM[11][inoff][iref]
                                      *qNM[4][inoff][iref] / wqNM[4][inoff][iref]
                                      *qNM[4][inoff][iref] / wqNM[4][inoff][iref] +
                                    12*qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[4][inoff][iref] / wqNM[4][inoff][iref]
                                      *qNM[17][inoff][iref] / wqNM[17][inoff][iref] +
                                    48*qNM[4][inoff][iref] / wqNM[4][inoff][iref]
                                      *qNM[7][inoff][iref] / wqNM[7][inoff][iref]
                                      *qNM[15][inoff][iref] / wqNM[15][inoff][iref] +
                                    24*qNM[4][inoff][iref] / wqNM[4][inoff][iref]
                                      *qNM[8][inoff][iref] / wqNM[8][inoff][iref]
                                      *qNM[9][inoff][iref] / wqNM[9][inoff][iref] +
                                    24*qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[8][inoff][iref] / wqNM[8][inoff][iref]
                                      *qNM[15][inoff][iref] / wqNM[15][inoff][iref] +
                                    12*qNM[4][inoff][iref] / wqNM[4][inoff][iref]
                                      *qNM[7][inoff][iref] / wqNM[7][inoff][iref]
                                      *qNM[15][inoff][iref] / wqNM[15][inoff][iref] -
                                    72*qNM[7][inoff][iref] / wqNM[7][inoff][iref]
                                      *qNM[8][inoff][iref] / wqNM[8][inoff][iref]
                                      *qNM[4][inoff][iref] / wqNM[4][inoff][iref]
                                      *qNM[4][inoff][iref] / wqNM[4][inoff][iref] -
                                    72*qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[4][inoff][iref] / wqNM[4][inoff][iref]
                                      *qNM[8][inoff][iref] / wqNM[8][inoff][iref]
                                      *qNM[8][inoff][iref] / wqNM[8][inoff][iref] )
                                      *wqNM[2][inoff][iref];
               wcNM[order][inoff] -= wqNM[2][inoff][iref];
            }
            break;
         case 3:
            if( wqNM[3][inoff][iref] != 0. )
            {
               cNM[order][inoff]  -= ( qNM[3][inoff][iref]   / wqNM[3][inoff][iref]   - //     <<8>>
                                     4*qNM[4][inoff][iref] / wqNM[4][inoff][iref]   
                                      *qNM[21][inoff][iref] / wqNM[21][inoff][iref] - 
                                     4*qNM[24][inoff][iref] / wqNM[24][inoff][iref]   
                                      *qNM[17][inoff][iref] / wqNM[17][inoff][iref] -
                                     4*qNM[2][inoff][iref] / wqNM[2][inoff][iref]   
                                      *qNM[6][inoff][iref] / wqNM[6][inoff][iref] -
                                     4*qNM[23][inoff][iref] / wqNM[23][inoff][iref]   
                                      *qNM[5][inoff][iref] / wqNM[5][inoff][iref] -
                                     8*qNM[1][inoff][iref] / wqNM[1][inoff][iref]   
                                      *qNM[1][inoff][iref] / wqNM[1][inoff][iref] -
                                       qNM[14][inoff][iref] / wqNM[14][inoff][iref]   
                                      *qNM[19][inoff][iref] / wqNM[19][inoff][iref] -
                                       qNM[13][inoff][iref] / wqNM[13][inoff][iref]   
                                      *qNM[20][inoff][iref] / wqNM[20][inoff][iref] -
                                     4*qNM[9][inoff][iref] / wqNM[9][inoff][iref]   
                                      *qNM[10][inoff][iref] / wqNM[10][inoff][iref] -
                                     4*qNM[12][inoff][iref] / wqNM[12][inoff][iref]   
                                      *qNM[18][inoff][iref] / wqNM[18][inoff][iref] + 
                                    32*qNM[1][inoff][iref] / wqNM[1][inoff][iref]
                                      *qNM[4][inoff][iref] / wqNM[4][inoff][iref]
                                      *qNM[5][inoff][iref] / wqNM[5][inoff][iref] +
                                    32*qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[1][inoff][iref] / wqNM[1][inoff][iref]
                                      *qNM[6][inoff][iref] / wqNM[6][inoff][iref] + 
                                     4*qNM[14][inoff][iref] / wqNM[14][inoff][iref]
                                      *qNM[4][inoff][iref] / wqNM[4][inoff][iref]
                                      *qNM[4][inoff][iref] / wqNM[4][inoff][iref] + 
                                     4*qNM[19][inoff][iref] / wqNM[19][inoff][iref]
                                      *qNM[5][inoff][iref] / wqNM[5][inoff][iref]
                                      *qNM[5][inoff][iref] / wqNM[5][inoff][iref] +
                                     4*qNM[13][inoff][iref] / wqNM[13][inoff][iref]
                                      *qNM[6][inoff][iref] / wqNM[6][inoff][iref]
                                      *qNM[6][inoff][iref] / wqNM[6][inoff][iref] + 
                                     4*qNM[20][inoff][iref] / wqNM[20][inoff][iref]
                                      *qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[0][inoff][iref] / wqNM[0][inoff][iref] + 
                                    16*qNM[10][inoff][iref] / wqNM[10][inoff][iref]
                                      *qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[4][inoff][iref] / wqNM[4][inoff][iref] + 
                                    16*qNM[9][inoff][iref] / wqNM[9][inoff][iref]
                                      *qNM[5][inoff][iref] / wqNM[5][inoff][iref]
                                      *qNM[6][inoff][iref] / wqNM[6][inoff][iref] + 
                                    16*qNM[12][inoff][iref] / wqNM[12][inoff][iref]
                                      *qNM[6][inoff][iref] / wqNM[6][inoff][iref]
                                      *qNM[4][inoff][iref] / wqNM[4][inoff][iref] + 
                                    16*qNM[18][inoff][iref] / wqNM[18][inoff][iref]   
                                      *qNM[5][inoff][iref] / wqNM[5][inoff][iref]  
                                      *qNM[0][inoff][iref] / wqNM[0][inoff][iref] -
                                    72*qNM[5][inoff][iref] / wqNM[5][inoff][iref]
                                      *qNM[6][inoff][iref] / wqNM[6][inoff][iref]
                                      *qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[4][inoff][iref] / wqNM[4][inoff][iref] -
                                    36*qNM[5][inoff][iref] / wqNM[5][inoff][iref]
                                      *qNM[5][inoff][iref] / wqNM[5][inoff][iref]
                                      *qNM[4][inoff][iref] / wqNM[4][inoff][iref]
                                      *qNM[4][inoff][iref] / wqNM[4][inoff][iref] -
                                    36*qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[0][inoff][iref] / wqNM[0][inoff][iref]
                                      *qNM[6][inoff][iref] / wqNM[6][inoff][iref]
                                      *qNM[6][inoff][iref] / wqNM[6][inoff][iref] )
                                      *wqNM[3][inoff][iref];
               wcNM[order][inoff] -= wqNM[3][inoff][iref];
            }
            break;
         default:
            LOG_S(ERROR) << "Not defined order";
            break;
      }
   }
}
//___________________________________________________
//
// compute v_{n}
//___________________________________________________
double
computeVn(int iord, double cval, int nsub)
{
   double val = 0.;
   if( nsub <= 2)
   {
      switch(iord)
      {
         case 0:
            if (cval > 0.) val = TMath::Sqrt(cval);
            break;
         case 1:
            if (cval < 0.) val = TMath::Power(-1*cval, 1./4.);
            break;
         case 2:
            if (cval > 0.) val = TMath::Power(cval/4., 1./6.);
            break;
         case 3:
            if (cval < 0.) val = TMath::Power(-1*cval/33., 1./8.);
            break;
         default:
            LOG_S(ERROR) << "Unknown cumulant order. Will return 0 values...";
            break;
      }
   }
   else
   {
      switch(iord)
      {
         case 0:
            if (cval > 0.) val = TMath::Sqrt(cval);
            break;
         case 1:
            if (cval > 0.) val = TMath::Sqrt(cval);
            break;
         case 2:
            if (cval > 0.) val = TMath::Sqrt(cval);
            break;
         case 3:
            if (cval > 0.) val = TMath::Sqrt(cval);
            break;
         case 4:
            if (cval < 0.) val = TMath::Power(-1*cval, 1./4.);
            break;
         case 5:
            if (cval > 0.) val = TMath::Power(cval/4., 1./6.);
            break;
         case 6:
            if (cval < 0.) val = TMath::Power(-1*cval/33., 1./8.);
            break;
         default:
            LOG_S(ERROR) << "Unknown cumulant order. Will return 0 values...";
            break;
      }
   }
   return val;
}

//___________________________________________________
//
// compute v_{n} error
//___________________________________________________
double
errorVn(int iord, double cval, double cvalerr, double vval, int nsub)
{
   double val = 0;
   if( nsub <= 2 )
   {
      switch(iord)
      {
         case 0:
            cval = fabs(cval);
            val = 1./2. * 1./TMath::Sqrt(cval) * cvalerr * vval;
            break;
         case 1:
            cval = fabs(cval);
            val = 1./4. * 1./TMath::Power(cval, 3./4.) * cvalerr * vval;
            break;
         case 2:
            cval = fabs(cval);
            val = 1./6. * 1./TMath::Power(cval*cval*cval*cval*cval/4., 1./6.) * cvalerr * vval;
            break;
         case 3:
            cval = fabs(cval);
            val = 1./8. * 1./TMath::Power(cval*cval*cval*cval*cval*cval*cval/33., 1./8.) * cvalerr * vval;
            break;
         default:
            LOG_S(ERROR) << "Unknown cumulant order. Will return 0 values...";
            break;
      }
   }
   else
   {
      switch(iord)
      {
         case 0:
            cval = fabs(cval);
            val = 1./2. * 1./TMath::Sqrt(cval) * cvalerr * vval;
            break;
         case 1:
            cval = fabs(cval);
            val = 1./2. * 1./TMath::Sqrt(cval) * cvalerr * vval;
            break;
         case 2:
            cval = fabs(cval);
            val = 1./2. * 1./TMath::Sqrt(cval) * cvalerr * vval;
            break;
         case 3:
            cval = fabs(cval);
            val = 1./2. * 1./TMath::Sqrt(cval) * cvalerr * vval;
            break;
         case 4:
            cval = fabs(cval);
            val = 1./4. * 1./TMath::Power(cval, 3./4.) * cvalerr * vval;
            break;
         case 5:
            cval = fabs(cval);
            val = 1./6. * 1./TMath::Power(cval*cval*cval*cval*cval/4., 1./6.) * cvalerr * vval;
            break;
         case 6:
            cval = fabs(cval);
            val = 1./8. * 1./TMath::Power(cval*cval*cval*cval*cval*cval*cval/33., 1./8.) * cvalerr * vval;
            break;
         default:
            LOG_S(ERROR) << "Unknown cumulant order. Will return 0 values...";
            break;
      }
   }
   return val;
}

#endif
