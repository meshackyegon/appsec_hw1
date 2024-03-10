/*
 * Gift Card Example Writer
 * Original Author: Shoddycorp's Cut-Rate Contracting
 * Maintainer: ???
 * Comments added by Justin Cappos (JAC)
 * Modification Date: 8 July 2020
 */
#include <stdio.h>
#include "giftcard.h"
/* JAC: Why is this included? */
#include <time.h>
struct this_gift_card examplegc;
struct gift_card_data examplegcd;
struct gift_card_record_data examplegcrd0;
struct gift_card_amount_change examplegcac0;
struct gift_card_program examplegcp;
// Break it up so that we don't have long functions! Good programming style!
// (JAC: This is so wrong. Global variable use / initialization is a
// terrible thing to do.)
void setupgc() {
FILE *fd1;
examplegc.num_bytes = 928;
examplegc.gift_card_data = (void *) &examplegcd;
examplegcd.merchant_id = "GiftCardz.com ";
examplegcd.customer_id = "DuaneGreenes Store 1451 ";
examplegcd.number_of_gift_card_records = 2;
fd1 = fopen("crash2.gft","w");
fwrite(&examplegc.num_bytes,4,1,fd1);
fwrite(examplegcd.merchant_id,32,1,fd1);
fwrite(examplegcd.customer_id,32,1,fd1);
fwrite(&examplegcd.number_of_gift_card_records,4,1,fd1);
/* JAC: Something seems fishy... */
examplegcd.gift_card_record_data =
malloc(examplegcd.number_of_gift_card_records*sizeof(void *));
/* JAC: here too! */
for (int i=0; i<examplegcd.number_of_gift_card_records-1; i++){
examplegcd.gift_card_record_data[i] = (void *) &examplegcrd0;
examplegcrd0.record_size_in_bytes = 44;
examplegcrd0.type_of_record = 1; // JAC: Should be enum! amount_change
examplegcrd0.actual_record = (void *) &examplegcac0;
examplegcac0.amount_added = 200;
examplegcac0.actual_signature = "[ insert crypto signature here0]";
fwrite(&examplegcrd0.record_size_in_bytes,4,1,fd1);
fwrite(&examplegcrd0.type_of_record,4,1,fd1);
fwrite(&examplegcac0.amount_added,4,1,fd1);
fwrite(examplegcac0.actual_signature,32,1,fd1);
}
examplegcd.gift_card_record_data[1] = (void *) &examplegcrd0;
examplegcrd0.record_size_in_bytes = 44;
examplegcrd0.type_of_record = 3; // JAC: Should be enum! amount_change
examplegcrd0.actual_record = (void *) &examplegcp;
examplegcp.message = "This is a happy birthday messgae";
examplegcp.program = "PUT SOMETHING IN HERE"
fwrite(&examplegcrd0.record_size_in_bytes,4,1,fd1);
fwrite(&examplegcrd0.type_of_record,4,1,fd1);
fwrite(&examplegcp.message,32,1,fd1);
fwrite(examplegcp.program,128,1,fd1);
fclose(fd1);
}
// moved into separate files to avoid erroenous style checker error...
/* JAC: opening and writing a fixed filename using a global is terrible style.
 * the style checker was right! This code is terrible
 */
void writegc() {
}
/* JAC: No args and return -1 for no reason!?! */
int main(void) {
setupgc();
//writegc();
return -1;
}