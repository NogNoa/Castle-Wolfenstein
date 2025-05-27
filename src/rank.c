#include "video.h"
#include "conio.h"

struct cs_pg_t castl_pg;

char rank_calculate(void)
{
  bool temp = castl_pg.ris_rnk_twc;
  if (castl_pg.save_status < 0x80) {
    if (1 < castl_pg.save_status) {
      castl_pg.rank_index -= 1;
    }
  }
  else {
    if (castl_pg.rank_index <= 0xf0) 
    {   castl_pg.rank_index += 0x10;
        if (castl_pg.ris_rnk_twc && (castl_pg.rank_index <= 0xf0))
            { castl_pg.ris_rnk_twc = temp;
              castl_pg.rank_index += 0x10;
              temp = false;
            }
    }
    if ((0xf0 < castl_pg.rank_index)) {
      castl_pg.rank_index = 0xf0;
    }
  }
  if (castl_pg.rank_index < 0x10) {
    castl_pg.rank_index = 0x10;
  }
  return castl_pg.rank_index;
}
  /*     100 > ur >=  f0
          00 > sr >= -10
  
  */


