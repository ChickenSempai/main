
uint8_t win_x;
uint8_t win_y;
const int mSize = 11;
bool table[mSize][mSize];
bool sight[mSize][mSize];
bool input = false;
bool previnput = false;
byte character[8] = { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };
byte blnk_character[8] = { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };
bool WL = 0;
bool RD = 1;
const uint8_t colPins[8] = { 2, 3, 4, 5, 6, 7, 8, 9 };
enum { UP, RIGHT, DOWN, LEFT };
struct Actor {
    int x;
    int y;
} player;
#define SER_PIN 10
#define SCK_PIN 11
#define RCK_PIN 12
#define Y_AX 1
#define X_AX 0
//const for player and exit blinking;
bool exit_inSight = false; //used in "lookEverywhere"
bool blnkFlag = false;
unsigned long blnkDelay = 50;
unsigned long lastBlnk = 0;

void setup() {
    randomSeed(analogRead(A3));
    pinMode(Y_AX, INPUT);
    pinMode(X_AX, INPUT);
    // Turn everything to low
    for (uint8_t i = 0; i < 8; i++) {
        pinMode(colPins[i], OUTPUT);
    }
    pinMode(SER_PIN, OUTPUT);
    pinMode(SCK_PIN, OUTPUT);
    pinMode(RCK_PIN, OUTPUT);
    Serial.begin(9600);
    for (int j = 1; j < mSize; j++)
        for (int i = 1; i < mSize; i++)
            table[j][i] = WL;

    for (int j = 1; j < mSize; j++)
        for (int i = 1; i < mSize; i++)
            sight[j][i] = RD;

    genMaze();
    win_x = mSize - 2;
    win_y = mSize - 2;
    player.x = 1;
    player.y = 1;
    lookEverywhere(0, 0);
        for (int row = 0, rowp = player.y - 3; row < 8; row++, rowp++)
            for (int k = 0, kr = player.x - 4; k < 8; k++, kr++)
                if (rowp < mSize && kr < mSize && rowp >= 0 && kr >= 0)
                    if (rowp == player.y && kr == player.x) {
                        blnk_character[row] = blnk_character[row] << 1 | true;
                        character[row] = character[row] << 1 | (sight[rowp][kr] == WL);
                    }
                    else {
                        if (exit_inSight) {
                            if (rowp == win_y && kr == win_x) {
                                blnk_character[row] = blnk_character[row] << 1 | true;
                                character[row] = character[row] << 1 | (sight[rowp][kr] == WL);
                            }
                        }
                        else {
                            character[row] = character[row] << 1 | (table[rowp][kr] == WL);
                            blnk_character[row] = blnk_character[row] << 1 | (sight[rowp][kr] == WL);
                        }
                    }
                else {
                    character[row] = character[row] << 1 | false;
                    blnk_character[row] = blnk_character[row] << 1 | false;
                }


}

void loop() {
    int x = analogRead(X_AX);
    int y = analogRead(Y_AX);
    if (x > 755 || x < 255 || y < 255 || y>755) {
        if (previnput == false) {
            input = true;
            previnput = true;
        }
        else input = false;
    }
    else {
        input = false;
        previnput = false;
    }

    if (input) { //если есть инпут значит есть смысл разочек попробовать чтото изменить
               //если нет то пускай просто нонстоп отображает что есть
               //нет учета того что игрок должен мигать

        if (x < 255)
            x = -1;
        else if (x > 755)
            x = 1;
        else x = 0;
        if (y < 255)
            y = 1;
        else if (y > 755)
            y = -1;
        else y = 0;
        moveP(x, y);
        Serial.print(player.x);
        Serial.print(' ');
        Serial.print(player.y);
        Serial.print('\n');
        for (int j = 1; j < mSize; j++)
            for (int i = 1; i < mSize; i++)
                sight[j][i] = RD;
        if (player.x == win_x && player.y == win_y) {

            for (int j = 1; j < mSize; j++)
                for (int i = 1; i < mSize; i++)
                    table[j][i] = WL;

            genMaze();

            for (int j = 1; j < mSize; j++)
                for (int i = 1; i < mSize; i++)
                    sight[j][i] = RD;
            switch (random(4)) {
            case 0:

                win_y = 1;
                win_x = 1;
                player.x = random(mSize / 2) + mSize / 2;
                if (player.x % 2 == 0)
                    player.x--;
                player.y = random(mSize / 2) + mSize / 2;
                if (player.y % 2 == 0)
                    player.y--;
                break;
            case 1:

                win_y = 1;
                win_x = mSize - 2;
                player.x = random(mSize / 2);
                if (player.x % 2 == 0)
                    player.x++;
                player.y = random(mSize / 2) + mSize / 2;
                if (player.y % 2 == 0)
                    player.y--;
                break;
            case 2:

                win_y = mSize - 2;
                win_x = 1;
                player.x = random(mSize / 2) + mSize / 2;
                if (player.x % 2 == 0)
                    player.x--;
                player.y = random(mSize / 2);
                if (player.y % 2 == 0)
                    player.y++;
                break;
            case 3:

                win_y = mSize - 2;
                win_x = mSize - 2;
                player.x = random(mSize / 2);
                if (player.x % 2 == 0)
                    player.x++;
                player.y = random(mSize / 2);
                if (player.y % 2 == 0)
                    player.y++;
                break;
            }
        }
        lookEverywhere(player.x, player.y);

        //формировка вывода
        for (int row = 0, rowp = player.y - 3; row < 8; row++, rowp++)
            for (int k = 0, kr = player.x - 4; k < 8; k++, kr++)
                if (rowp < mSize && kr < mSize && rowp >= 0 && kr >= 0)
                    if (rowp == player.y && kr == player.x) {
                        blnk_character[row] = blnk_character[row] << 1 | true;
                        character[row] = character[row] << 1 | false;
                    }
                    else {
                        if (exit_inSight) {
                            if (rowp == win_y && kr == win_x) {
                                blnk_character[row] = blnk_character[row] << 1 | true;
                                character[row] = character[row] << 1 | (sight[rowp][kr] == WL);
                            }
                        }
                        else {
                            character[row] = character[row] << 1 | (sight[rowp][kr] == WL);
                            blnk_character[row] = blnk_character[row] << 1 | (sight[rowp][kr] == WL);
                        }
                    }
                else {
                    character[row] = character[row] << 1 | false;
                    blnk_character[row] = blnk_character[row] << 1 | false;
                }


    }

    //вывод
    int rowbits = 0x80;
    for (int row = 0; row < 8; row++) {
        for (int k = 0; k < 8; k++)
            digitalWrite(colPins[k], HIGH); // Cleanup cols
        write595(rowbits); // prepare to write the row
        if ((millis() - lastBlnk)>blnkDelay){
          blnkFlag = !blnkFlag;
          lastBlnk = millis();
          }
        if (blnkFlag)
            for (int col = 0; col < 8; col++)
                digitalWrite(colPins[7 - col], character[row] & 1 << col ? LOW : HIGH);
        else 
            for (int col = 0; col < 8; col++)
                digitalWrite(colPins[7 - col], blnk_character[row] & 1 << col ? LOW : HIGH);
        delay(1);
        write595(0);
        rowbits >>= 1;
    }
    //вывод
}

inline void moveP(int x, int y) {

    if (table[player.y][player.x + x] != WL && table[player.y][player.x + x * 2] != WL)
        player.x += x * 2;
    if (table[player.y + y][player.x] != WL && table[player.y + y * 2][player.x] != WL)
        player.y += y * 2;
    /*
    if (table[player.y][player.x + x] != WL)
         player.x += x;
     if (table[player.y + y][player.x] != WL)
       player.y += y;
       */
}//improvable


inline void lookEverywhere(int x, int y) {
  exit_inSight = false; 
    for (int i = player.y; table[i][player.x] != WL && (i - player.y) < 4; i++) {
        sight[i + 1][player.x - 1] = table[i + 1][player.x - 1];
        sight[i + 1][player.x] = table[i + 1][player.x];
        exit_inSight = (i + 1 == win_y) && (player.x == win_x);
        sight[i + 1][player.x + 1] = table[i + 1][player.x + 1];
    }
    for (int i = player.y; table[i][player.x] != WL && (player.y - i) < 3; i--) {
        sight[i - 1][player.x - 1] = table[i - 1][player.x - 1];
        sight[i - 1][player.x] = table[i - 1][player.x];
        exit_inSight = (i - 1 == win_y) && (player.x == win_x);
        sight[i - 1][player.x + 1] = table[i - 1][player.x + 1];
    }
    for (int i = player.x; table[i][player.x] != WL && (i - player.x) < 4; i++) {
        sight[player.y - 1][i + 1] = table[player.y - 1][i + 1];
        sight[player.y][i + 1] = table[player.y][i + 1];
        exit_inSight = (i + 1 == win_x) && (player.y == win_y);
        sight[player.y + 1][i + 1] = table[player.y + 1][i + 1];
    }
    for (int i = player.x; table[i][player.x] != WL && (player.y - i) < 3; i--) {
        sight[player.y - 1][i - 1] = table[player.y - 1][i - 1];
        sight[player.y][i - 1] = table[player.y][i - 1];
        exit_inSight = (i - 1 == win_x) && (player.y == win_y);
        sight[player.y + 1][i - 1] = table[player.y + 1][i - 1];
    }
    if (x == 1) {
        sight[player.y + 1][player.x - 3 - 1] = RD;//unsee
        sight[player.y][player.x - 3 - 1] = RD;//unsee
        sight[player.y - 1][player.x - 3 - 1] = RD;//unsee
    }
    else if (x == -1) {
        sight[player.y + 1][player.x + 4 + 1] = RD;//unsee
        sight[player.y][player.x + 4 + 1] = RD;//unsee
        sight[player.y - 1][player.x + 4 + 1] = RD;//unsee
    }
    else if (y == 1) {
        sight[player.y - 3 - 1][player.x + 1] = RD;//unsee
        sight[player.y - 3 - 1][player.x] = RD;//unsee
        sight[player.y - 3 - 1][player.x - 1] = RD;//unsee
    }
    else if (y == -1) {
        sight[player.y + 4 + 1][player.x + 1] = RD;//unsee
        sight[player.y + 4 + 1][player.x] = RD;//unsee
        sight[player.y + 4 + 1][player.x - 1] = RD;//unsee
    }
}

void write595(byte data) {
    digitalWrite(RCK_PIN, LOW);
    shiftOut(SER_PIN, SCK_PIN, LSBFIRST, data);
    digitalWrite(RCK_PIN, HIGH);
}

inline uint8_t down(uint8_t y, uint8_t x)
{
    y += 2;
    return ((y / 2) * (mSize / 2)) + x / 2;
}

inline uint8_t right(uint8_t y, uint8_t x)
{
    x += 2;
    return ((y / 2) * (mSize / 2)) + x / 2;
}

inline uint8_t up(uint8_t y, uint8_t x)
{
    y -= 2;
    return ((y / 2) * (mSize / 2)) + x / 2;
}

inline uint8_t left(uint8_t y, uint8_t x)
{
    x -= 2;
    return ((y / 2) * (mSize / 2)) + x / 2;
}

inline void markNeighb(uint8_t& x, uint8_t& y, uint8_t*& wallSt, uint8_t& wMem)
{

    if (y <= mSize - 4 && table[y + 2][x] == WL && sight[y + 2][x] == RD) {
        wallSt[wMem] = (down(y, x));
        sight[y + 2][x] = WL;
        wMem++;
    }
    if (x <= mSize - 4 && table[y][x + 2] == WL && sight[y][x + 2] == RD) {
        wallSt[wMem] = (right(y, x));
        sight[y][x + 2] = WL;
        wMem++;
    }
    if (y >= 3 && table[y - 2][x] == WL && sight[y - 2][x] == RD) {
        wallSt[wMem] = (up(y, x));
        sight[y - 2][x] = WL;
        wMem++;
    }
    if (x >= 3 && table[y][x - 2] == WL && sight[y][x - 2] == RD) {
        wallSt[wMem] = (left(y, x));
        sight[y][x - 2] = WL;
        wMem++;
    }
}

inline void delwal(uint8_t* arr, uint8_t ind, int lim) {
    for (; ind < lim - 1; ind++)
        arr[ind] = arr[ind + 1];
}

void genMaze()
{
    uint8_t x = 0, y = 0;
    while (x % 2 != 1)
        x = (random((mSize - 2)) + 1);
    while (y % 2 != 1)
        y = (random((mSize - 2)) + 1);
    uint8_t* wallSt = NULL;
    uint8_t wMem = 0;
    table[y][x] = RD;
    wallSt = (uint8_t*)realloc(wallSt, (wMem + 3) * sizeof(uint8_t));
    markNeighb(x, y, wallSt, wMem);
    while (wMem != 0) {
        uint8_t ind;
        uint8_t idel = wMem - 1;
        idel = random(wMem);
        ind = wallSt[idel];
        delwal(wallSt, idel, wMem);
        wMem--;
        y = (ind / (mSize / 2)) * 2 + 1;
        x = (ind % (mSize / 2)) * 2 + 1;
        table[y][x] = RD;
        wallSt = (uint8_t*)realloc(wallSt, (wMem + 3) * sizeof(uint8_t));
        uint8_t dir;

        for (bool flag = WL; flag == WL;) {
            dir = (random(LEFT + 1));
            switch (dir) {
            case UP:
                if (table[y - 2][x] == RD && y - 2 > 0) {
                    flag = table[y - 1][x] = RD;
                }
                break;
            case RIGHT:
                if (table[y][x + 2] == RD && x + 2 < mSize) {
                    flag = table[y][x + 1] = RD;
                }
                break;
            case DOWN:
                if (table[y + 2][x] == RD && y + 2 < mSize) {
                    flag = table[y + 1][x] = RD;
                }
                break;
            case LEFT:
                if (table[y][x - 2] == RD && x - 2 > 0) {
                    flag = table[y][x - 1] = RD;
                }
                break;
            }
            markNeighb(x, y, wallSt, wMem);
        }


    }

    free(wallSt);
}
