void
duff_foobar()
   {
     int a;

  // Error: this unparses as: "switch(a){ case 1: while(a){ a = 7; } }"
     switch (a)
          default: a = 7;
   }
