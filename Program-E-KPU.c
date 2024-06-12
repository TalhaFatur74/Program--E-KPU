#include <stdio.h>
#include <string.h>
#define peserta 11
#define paslon 3

struct mahasiswa
{
    char nama[50];
    char nim[50];
};

struct pasangan
{
    struct mahasiswa ketua;
    struct mahasiswa wakil;
};

void menuAwal()
{
    printf("\n======== PROGRAM E-KPU PRESIDEN MAHASISWA ========\n");
    printf("Masuk sebagai\n");
    printf("1.Admin\n2.User\n");
}

// Gunakan pointer untuk mengingat memory address dari variabel pada fungsi main ke fungsi lainnya begitupun sebaliknya (pass by reference)
void tambahPeserta(int *jumlahMahasiswa, struct mahasiswa user[])
{

    if (*jumlahMahasiswa < peserta)
    {
        printf("Masukan Nama: ");
        scanf("%s", user[*jumlahMahasiswa].nama);

        printf("Masukan NIM: ");
        scanf("%s", user[*jumlahMahasiswa].nim);

        (*jumlahMahasiswa)++;
    }
    else
    {
        printf("Daftar Mahasiswa sudah penuh\n");
    }
}

void tambahPaslon(int *jumlahPaslon, int jumlahMahasiswa, struct pasangan bem[], struct mahasiswa user[], int sudah[])
{

    if (*jumlahPaslon < paslon)
    {
        printf("Masukan Nama Ketua: ");
        scanf("%s", bem[*jumlahPaslon].ketua.nama);

        printf("Masukan NIM Ketua: ");
        scanf("%s", bem[*jumlahPaslon].ketua.nim);

        printf("Masukan Nama Wakil Ketua: ");
        scanf("%s", bem[*jumlahPaslon].wakil.nama);

        printf("Masukan NIM Wakil Ketua: ");
        scanf("%s", bem[*jumlahPaslon].wakil.nim);

        int terdaftarKetua = 0; // Penanda apakah calon ketua sudah terdaftar sebagai mahasiswa atau belum
        int terdaftarWakil = 0; // Penanda apakah calon wakil ketua sudah terdaftar sebagai mahasiswa atau belum

        // Proses Searching untuk mencari apakah calon ketua dan wakilnya sudah terdaftar sebagai mahasiswa atau belum
        for (int i = 0; i < jumlahMahasiswa; i++)
        {
            if (strcmp(bem[*jumlahPaslon].ketua.nama, user[i].nama) == 0 && strcmp(bem[*jumlahPaslon].ketua.nim, user[i].nim) == 0)
            {
                terdaftarKetua = 1; // Terdaftar
            }
        }

        for (int i = 0; i < jumlahMahasiswa; i++)
        {
            if (strcmp(bem[*jumlahPaslon].wakil.nama, user[i].nama) == 0 && strcmp(bem[*jumlahPaslon].wakil.nim, user[i].nim) == 0)
            {
                terdaftarWakil = 1; // Terdaftar
            }
        }

        if (terdaftarKetua != 0 && terdaftarWakil != 0)
        {
            (*jumlahPaslon)++;
        }
        else
        {
            printf("Mahasiswa belum terdaftar\n");
        }
    }
    else
    {
        printf("Tidak bisa menambah paslon lagi\n");
    }
}

void daftarMahasiswa(int jumlahMahasiswa, struct mahasiswa user[], int sudah[])
{

    printf("\n=====DAFTAR MAHASISWA=====\n");
    if (jumlahMahasiswa == 0)
    {
        printf("Tidak ada Mahasiswa yang Mendaftar\n");
    }
    else
    {
        // Mencetak daftar mahasiswa
        for (int i = 0; i < jumlahMahasiswa; i++)
        {
            if (sudah[i] == 1)
            {
                printf("%d.%s (%s) [SUDAH MEMILIH]\n", i + 1, user[i].nama, user[i].nim); // Kondisi apabila mahasiswa sudah memilih
            }
            else
            {
                printf("%d.%s (%s)\n", i + 1, user[i].nama, user[i].nim);
            }
        }
    }
}

void daftarPaslon(int jumlahPaslon, struct pasangan bem[])
{

    printf("\n=====DAFTAR PASLON=====\n");
    if (jumlahPaslon == 0)
    {
        printf("Tidak ada Paslon\n");
    }
    else
    {
        // Mencetak daftar paslon
        for (int i = 0; i < jumlahPaslon; i++)
        {
            printf("%d.%s (%s) - %s (%s)\n", i + 1, bem[i].ketua.nama, bem[i].ketua.nim, bem[i].wakil.nama, bem[i].wakil.nim);
        }
    }
}

void pemungutanSuara(int jumlahPaslon, struct pasangan bem[], int suara[], int *hasil)
{

    printf("\n===== HASIL PEMUNGUTAN SUARA =====\n");
    for (int i = 0; i < jumlahPaslon; i++)
    {
        printf("Paslon %d. (%s - %s): %d suara\n", i + 1, bem[i].ketua.nama, bem[i].wakil.nama, suara[i]);
    }
    *hasil = 1; // Syarat berakhirnya program
}

int main()
{
    int suara[paslon] = {0};
    int sudah[peserta] = {0};
    int jumlahPaslon = 0;
    int jumlahMahasiswa = 0;
    int hasil = 0;
    int coba;
    int pilihan;
    int coblos;
    char admin[50] = "adminganteng123";
    char inputAdmin[50];
    char inputNama[50];
    char inputNim[50];

    struct mahasiswa user[peserta];
    struct pasangan bem[paslon];

    do
    {
        if (pilihan == 5 && hasil == 1) // Kondisi untuk menghentikan program
        {
            break;
        }

        menuAwal();
        printf("Pilih (1-2): ");
        scanf("%d", &pilihan);

        coba = 0;
        if (pilihan == 1)
        {
            do
            {
                printf("Masukan Password: ");
                scanf("%s", &inputAdmin);

                if (strcmp(admin, inputAdmin) != 0)
                {
                    printf("Password salah\n");
                    printf("Coba lagi\n");
                }
                coba++;

            } while (coba < 3 && strcmp(admin, inputAdmin) != 0);

            do
            {
                // Kembali ke menu awal apabila sudah 3 kali salah
                if (coba == 3 && strcmp(admin, inputAdmin) != 0)
                {
                    printf("3 kali salah, kembali ke menu\n");
                    break;
                }

                printf("\n1.Tambahkan Mahasiswa\n");
                printf("2.Tambahkan Paslon\n");
                printf("3.Daftar Mahasiswa\n");
                printf("4.Daftar Paslon\n");
                printf("5.Program Selesai\n");
                printf("6.Kembali\n");
                printf("Pilih (1-6): ");
                scanf("%d", &pilihan);

                switch (pilihan)
                {
                case 1:
                    tambahPeserta(&jumlahMahasiswa, user);
                    break;
                case 2:
                    tambahPaslon(&jumlahPaslon, jumlahMahasiswa, bem, user, sudah);
                    break;
                case 3:
                    daftarMahasiswa(jumlahMahasiswa, user, sudah);
                    break;
                case 4:
                    daftarPaslon(jumlahPaslon, bem);
                    break;
                case 5:
                    pemungutanSuara(jumlahPaslon, bem, suara, &hasil);
                    break;
                case 6:
                    break;
                default:
                    printf("Tidak Valid\n");
                    break;
                }

            } while (pilihan != 5 && pilihan != 6);
        }
        else if (pilihan == 2)
        {
            if (jumlahPaslon == 0)
            {
                printf("daftarkan paslon terlebih dahulu\n");
            }
            else
            {
                printf("Masukan Nama: ");
                scanf("%s", &inputNama);

                printf("Masukan NIM : ");
                scanf("%s", &inputNim);

                int nomor = -1; // Penanda apakah mahasiswa sudah terdaftar atau belum

                // Proses searching untuk mencari mahasiswa yang sudah terdaftar
                for (int i = 0; i < jumlahMahasiswa; i++)
                {
                    if (strcmp(user[i].nama, inputNama) == 0 && strcmp(user[i].nim, inputNim) == 0)
                    {
                        nomor = i; // Terdaftar
                    }
                }
                if (nomor != -1 && sudah[nomor] != 1)
                {
                    daftarPaslon(jumlahPaslon, bem);

                    printf("Pilih Paslon: ");
                    scanf("%d", &coblos);

                    if (coblos >= 1 && coblos <= jumlahPaslon)
                    {
                        suara[coblos - 1]++;
                        printf("Terima kasih sudah memilih\n");

                        sudah[nomor] = 1; // Tanda bahwa mahasiswa sudah memilih
                    }
                    else
                    {
                        printf("Tidak Valid\n");
                    }
                }
                else if (sudah[nomor] == 1)
                {
                    printf("Anda sudah memilih\n");
                }
                else
                {
                    printf("Nama dan NIM salah atau belum terdaftar\n");
                }
            }
        }
        else
        {
            printf("tidak valid\n");
        }
    } while (1);    
    return 0;
}