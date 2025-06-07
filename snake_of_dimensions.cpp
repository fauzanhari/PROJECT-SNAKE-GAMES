#include <iostream>
#include <conio.h>   // menyediakan fungsi input secara real time. seperti fungsi getch sama kbhit, kbhit ini untuk cek apakah ada tombol yang diklik, jika true getch akan memproses
#include <ctime>     // menyediakan fungsi untuk mengambil dan mengelola waktu komputer. time() untuk Mengambil waktu sekarang dalam bentuk angka detik
#include <windows.h> // menyediakan fungsi khusus operasi windows. seperti sleep() untuk jeda sejenak, beep() untuk mengahsilkan efek suara
using namespace std;

// inisialisasi variabel global
const int lebar = 50;
const int tinggi = 20;
const int ekorMaks = 100;
bool selesai;
int skor;
int jedaGame = 5000;

enum Arah
{
    DIAM = 0,
    KIRI,
    KANAN,
    ATAS,
    BAWAH
}; // seperti daftar kode (angka) yang diberi nama biar gampang dibaca
Arah arah; // variabel dengan tipe data enumerasi yang cuma bisa berisi salah satu nilai dari enum Arah

// struct itu wadah yang bisa nyimpen banyak data sekaligus, dan tipe datanya bisa berbeda-beda.
struct Titik
{
    int x, y; // x menyimpan angka untuk posisi x (koordinat horizontal), dan y menyimpan angka untuk posisi y (koordinat vertikal)
};

Titik kepala, makanan;
Titik ekor[ekorMaks];
int jumlahEkor;

void garisMenu()
{
    for (int i = 0; i <= 50; i++)
        cout << "\033[34m" << "=" << "\033[0m";
    cout << "\n";
}

string rataTengah(string teks, int lebar)
{
    int spasi = (lebar - (int)teks.length()) / 2;
    return string(spasi, ' ') + teks + string(lebar - (int)teks.length() - spasi, ' ');
}

void ketikTengah(string teks, int lebar)
{
    int spasi = (lebar - (int)teks.length()) / 2;
    cout << string(spasi, ' ');
    for (char c : teks)
    {
        cout << c;
        for (long long i = 0; i < 100000000; i++)
            ;
    }
    cout << endl;
}

void mulai()
{
    string ular[] = {
        "         /^\\/^\\",
        "       _|__|  O|",
        "\\/    /~     \\_/ \\",
        "  \\____|__________/ ",
        "        \\_______/"};
    string judul = "+  SNAKE OF DIMENSION  +";
    int tinggiLogo = 5;

    system("cls");
    garisMenu();
    cout << endl;
    cout << "\033[32m";
    for (int i = 0; i < tinggiLogo; i++)
    {
        cout << rataTengah(ular[i], lebar) << endl;
    }
    cout << "\033[0m";
    cout << endl;
    ketikTengah(judul, 50);
    cout << endl;
    garisMenu();

    cout << "\n";
    cout << "\033[31m";
    ketikTengah("[  START  ]", lebar);
    cout << "\033[0m";
}

void buatMakanan()
{ // mencetak posisi makanan secara acak, tapi ga boleh di atas kepala ular dan di badan ular
    bool valid;
    do
    {
        valid = true;               // rand() menghasilkan angka acak (random number), biasanya angka bulat positif besar makanya perlu modulo
        makanan.x = rand() % lebar; // menentukan posisi secara acak terlebih dahulu
        makanan.y = rand() % tinggi;
        // cek kondisi posisi
        if (makanan.x == kepala.x && makanan.y == kepala.y)
            valid = false;
        for (int i = 0; i < jumlahEkor; i++)
        {
            if (ekor[i].x == makanan.x && ekor[i].y == makanan.y)
            {
                valid = false;
                break;
            }
        }
    } while (!valid);
}

void awalGame()
{
    selesai = false;
    arah = KANAN;
    kepala.x = lebar / 2;
    kepala.y = tinggi / 2;
    jumlahEkor = 0;
    skor = 0;
    jedaGame = 200;
    buatMakanan();
}

void displayGame()
{
    system("cls");

    for (int i = 0; i < lebar + 2; i++)
        cout << "\033[34m#\033[0m";
    cout << endl;

    for (int i = 0; i < tinggi; i++) // arah vertikal
    {
        for (int j = 0; j < lebar; j++) // arah horizontal
        {
            if (j == 0)
                cout << "\033[34m#\033[0m"; // dinding kiri biru

            if (i == kepala.y && j == kepala.x)
            {
                cout << "\033[31mO\033[0m"; // kepala ular merah
            }
            else if (i == makanan.y && j == makanan.x)
            {
                cout << "\033[1;33m@\033[0m"; // makanan oranye (kuning tebal)
            }
            else
            {
                bool cetakEkor = false;
                for (int k = 0; k < jumlahEkor; k++)
                {
                    if (ekor[k].x == j && ekor[k].y == i)
                    {
                        cout << "\033[31mo\033[0m"; // ekor ular merah
                        cetakEkor = true;
                        break;
                    }
                }
                if (!cetakEkor)
                    cout << " ";
            }
            if (j == lebar - 1)
                cout << "\033[34m#\033[0m"; // dinding KANAN biru
        }
        cout << endl;
    }

    for (int i = 0; i < lebar + 2; i++)
        cout << "\033[34m#\033[0m";
    cout << endl;

    cout << "Skor: " << skor << "\n";
    cout << "Kontrol: Panah / WASD | Tekan 'x' untuk keluar\n";
}

int ambilTombol()
{
    int tombol = _getch();
    if (tombol == 0 || tombol == 224) // tanda awal bahwa tombol tersebut extended, yang artinya tombol khusus
        tombol = _getch();            // harus membaca kembali tombol apa yang diinputkan
    return tombol;                    // mengembalikan nilai tombol ke pemanggil fungsi
}

void input()
{
    if (_kbhit())
    {
        int tombol = ambilTombol();
        switch (tombol)
        {
        case 72:
        case 'w':
        case 'W':
            if (arah != BAWAH)
                arah = ATAS;
            break;
        case 80:
        case 's':
        case 'S':
            if (arah != ATAS)
                arah = BAWAH;
            break;
        case 75:
        case 'a':
        case 'A':
            if (arah != KANAN)
                arah = KIRI;
            break;
        case 77:
        case 'd':
        case 'D':
            if (arah != KIRI)
                arah = KANAN;
            break;
        case 'x':
        case 'X':
            selesai = true;
            break;
        }
    }
}

void gerakUlar()
{
    if (jumlahEkor > 0)
    {
        for (int i = jumlahEkor - 1; i > 0; i--)
        {
            ekor[i] = ekor[i - 1];
        }
        ekor[0] = kepala;
    }
    switch (arah)
    {
    case KIRI:
        kepala.x--;
        break;
    case KANAN:
        kepala.x++;
        break;
    case ATAS:
        kepala.y--;
        break;
    case BAWAH:
        kepala.y++;
        break;
    default:
        break;
    }

    // tembusin ularnya
    if (kepala.x < 0)
        kepala.x = lebar - 1;
    else if (kepala.x >= lebar)
        kepala.x = 0;

    if (kepala.y < 0)
        kepala.y = tinggi - 1;
    else if (kepala.y >= tinggi)
        kepala.y = 0;

    // cek tabrakan dengan ekor
    for (int i = 0; i < jumlahEkor; i++)
    {
        if (ekor[i].x == kepala.x && ekor[i].y == kepala.y)
            selesai = true;
    }

    // cek jika kepala makan makanan
    if (kepala.x == makanan.x && kepala.y == makanan.y)
    {
        skor += 10;
        Beep(1000, 100);
        if (jumlahEkor < ekorMaks)
            jumlahEkor++;
        buatMakanan();
        if (jedaGame > 50)
            jedaGame -= 5;
    }
}

void akhirGame()
{
    system("cls");
    garisMenu();
    cout << rataTengah(" +     GAME OVER    + ", lebar) << endl;
    cout << rataTengah("Skor Akhir: " + to_string(skor), lebar) << endl;
    cout << rataTengah("Terima kasih sudah bermain!", lebar) << endl;
    garisMenu();
    cout << "\nTekan tombol apa saja untuk keluar...";
    _getch();
}

int main()
{
    mulai();
    _getch();
    awalGame();
    while (!selesai)
    {
        displayGame();
        input();
        gerakUlar();
        Sleep(jedaGame);
    }
    akhirGame();
    return 0;
}
