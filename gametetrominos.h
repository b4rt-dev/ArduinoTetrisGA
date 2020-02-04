

enum Tetromino { T_I,  T_J,  T_L,  T_O,  T_S,  T_T,  T_Z,  T_NONE };

// [rotation],[row],[col] - 0,0 lower left corner
const bool t_i[4*4*4] = {
  
  0, 0, 0, 0,
  0, 0, 0, 0,
  1, 1, 1, 1,
  0, 0, 0, 0,

  0, 0, 1, 0,
  0, 0, 1, 0,
  0, 0, 1, 0,
  0, 0, 1, 0,

  0, 0, 0, 0,
  1, 1, 1, 1,
  0, 0, 0, 0,
  0, 0, 0, 0,

  0, 1, 0, 0,
  0, 1, 0, 0,
  0, 1, 0, 0,
  0, 1, 0, 0
};

const bool t_j[4*3*3] = {
  
  0, 0, 0,
  1, 1, 1,
  1, 0, 0,

  0, 1, 0,
  0, 1, 0,
  0, 1, 1,

  0, 0, 1,
  1, 1, 1,
  0, 0, 0,

  1, 1, 0,
  0, 1, 0,
  0, 1, 0
};

const bool t_l[4*3*3] = {

  0, 0, 0,
  1, 1, 1,
  0, 0, 1,

  0, 1, 1,
  0, 1, 0,
  0, 1, 0,

  1, 0, 0,
  1, 1, 1,
  0, 0, 0,

  0, 1, 0,
  0, 1, 0,
  1, 1, 0
};

const bool t_o[1*3*4] = {

  0, 0, 0, 0,
  0, 1, 1, 0,
  0, 1, 1, 0
};

const bool t_s[4*3*3] = {

  0, 0, 0,
  1, 1, 0,
  0, 1, 1,

  0, 0, 1,
  0, 1, 1,
  0, 1, 0,

  1, 1, 0,
  0, 1, 1,
  0, 0, 0,
  
  0, 1, 0,
  1, 1, 0,
  1, 0, 0
};

const bool t_t[4*3*3] = {

  0, 0, 0,
  1, 1, 1,
  0, 1, 0,

  0, 1, 0,
  0, 1, 1,
  0, 1, 0,

  0, 1, 0,
  1, 1, 1,
  0, 0, 0,

  0, 1, 0,
  1, 1, 0,
  0, 1, 0,
};

const bool t_z[4*3*3] = {
  
  0, 0, 0,
  0, 1, 1,
  1, 1, 0,
  
  0, 1, 0,
  0, 1, 1,
  0, 0, 1,
  
  0, 1, 1,
  1, 1, 0,
  0, 0, 0,
 
  1, 0, 0,
  1, 1, 0,
  0, 1, 0
};

const int8_t wallKickData[][5][2] = {
  { {0, 0}, {-1, 0}, {-1,+1}, {0,-2}, {-1,-2} },
  { {0, 0}, {+1, 0}, {+1,-1}, {0,+2}, {+1,+2} },
  { {0, 0}, {+1, 0}, {+1,-1}, {0,+2}, {+1,+2} },
  { {0, 0}, {-1, 0}, {-1,+1}, {0,-2}, {-1,-2} },
  { {0, 0}, {+1, 0}, {+1,+1}, {0,-2}, {+1,-2} },
  { {0, 0}, {-1, 0}, {-1,-1}, {0,+2}, {-1,+2} },
  { {0, 0}, {-1, 0}, {-1,-1}, {0,+2}, {-1,+2} },
  { {0, 0}, {+1, 0}, {+1,+1}, {0,-2}, {+1,-2} }
};

const int8_t wallKickDataI[][5][2] = {
  { {0, 0}, {-2, 0}, {+1, 0}, {-2,-1}, {+1,+2} },
  { {0, 0}, {+2, 0}, {-1, 0}, {+2,+1}, {-1,-2} },
  { {0, 0}, {-1, 0}, {+2, 0}, {-1,+2}, {+2,-1} },
  { {0, 0}, {+1, 0}, {-2, 0}, {+1,-2}, {-2,+1} },
  { {0, 0}, {+2, 0}, {-1, 0}, {+2,+1}, {-1,-2} },
  { {0, 0}, {-2, 0}, {+1, 0}, {-2,-1}, {+1,+2} },
  { {0, 0}, {+1, 0}, {-2, 0}, {+1,-2}, {-2,+1} },
  { {0, 0}, {-1, 0}, {+2, 0}, {-1,+2}, {+2,-1} }
};

/* https://tetris.wiki/SRS

           J, L, S, T, Z Tetromino Wall Kick Data  
           Test 1   Test 2    Test 3    Test 4    Test 5
    0->R  ( 0, 0)   (-1, 0)   (-1,+1)   ( 0,-2)   (-1,-2)
    R->0  ( 0, 0)   (+1, 0)   (+1,-1)   ( 0,+2)   (+1,+2)
    R->2  ( 0, 0)   (+1, 0)   (+1,-1)   ( 0,+2)   (+1,+2)
    2->R  ( 0, 0)   (-1, 0)   (-1,+1)   ( 0,-2)   (-1,-2)
    2->L  ( 0, 0)   (+1, 0)   (+1,+1)   ( 0,-2)   (+1,-2)
    L->2  ( 0, 0)   (-1, 0)   (-1,-1)   ( 0,+2)   (-1,+2)
    L->0  ( 0, 0)   (-1, 0)   (-1,-1)   ( 0,+2)   (-1,+2)
    0->L  ( 0, 0)   (+1, 0)   (+1,+1)   ( 0,-2)   (+1,-2)
    
    
          I Tetromino Wall Kick Data  
          Test 1    Test 2    Test 3    Test 4    Test 5
    0->R  ( 0, 0)   (-2, 0)   (+1, 0)   (-2,-1)   (+1,+2)
    R->0  ( 0, 0)   (+2, 0)   (-1, 0)   (+2,+1)   (-1,-2)
    R->2  ( 0, 0)   (-1, 0)   (+2, 0)   (-1,+2)   (+2,-1)
    2->R  ( 0, 0)   (+1, 0)   (-2, 0)   (+1,-2)   (-2,+1)
    2->L  ( 0, 0)   (+2, 0)   (-1, 0)   (+2,+1)   (-1,-2)
    L->2  ( 0, 0)   (-2, 0)   (+1, 0)   (-2,-1)   (+1,+2)
    L->0  ( 0, 0)   (+1, 0)   (-2, 0)   (+1,-2)   (-2,+1)
    0->L  ( 0, 0)   (-1, 0)   (+2, 0)   (-1,+2)   (+2,-1)
 */
