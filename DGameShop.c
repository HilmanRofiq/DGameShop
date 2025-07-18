#include <stdio.h>
#include <string.h> 
#include <stdlib.h>

struct User{
    char username[50];
    char nama[50];
    char password[50];
    char email[100];
    char no_telp[50];
    char feedback[50];
    int saldo;
    int developer;
} data_user;

struct Game{
    char judul[50];
    char genre[50];
    char platform[50];
    char pengembang[50];
    char tanggalRilis[50];
    int harga;
    int rating;
} game;

FILE *fuser;
FILE *fadmin;
FILE *fdeveloper;
FILE *fgame;
FILE *ffeedback;
FILE *fpendapatan;


int main(){
    MenuLogin();
    return 0;
}


void MenuLogin(){
    int pilihan;
    while (1) {
        system("cls");
        printf("\n=== SELAMAT DATANG DI DGAMESHOP ===\n");
        printf("1. Login Admin\n");
        printf("2. Login User\n");
        printf("3. Login Developer\n");
        printf("4. Registrasi User\n");
        printf("5. Logout\n");
        printf("Silahkan input pilihan anda: \n");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
            LoginAdmin();
            break;

            case 2:
            LoginUser();
            break;

            case 3:
            LoginDeveloper();
            break;

            case 4:
            RegistrasiUser();
            break;

            case 5:
            printf("Terimakasih Telah Menggunakan DGameShop");
            exit(0);
            break;
    
            default:
            printf("Pilihan tidak valid! Silahkan coba lagi.\n");
            system("pause");
        }    
    }    
}


void LoginAdmin(){
    char username[50], password[50];
    system("cls");
    int i = 0;

    printf("=== Login Admin DGameShop\n");
    while (i < 3) {
        printf("\nMasukan Username: ");
        scanf("%s", &username);
        printf("\nMasukan Password: ");
        scanf("%s", &password);
        if (strcmp(username, "Admin") == 0 && strcmp (password, "Admin123") == 0) {
            printf("Login Berhasil...\n");
            printf("Selamat Datang Admin\n");
            getchar();
            system("pause");
            MenuAdmin(1);
            break;
        } 
        else {
            printf("Username atau Password salah!\n");
            i++;
        }
        if (i < 3) {
            printf("Klik enter untuk ke halaman selanjutnya...\n");
            getchar();
        }
        else {
            printf("Mohon maaf, batas percobaan login telah habis, silahkan coba lagi nanti...");
            system("pause");
            MenuLogin();
        }   

    }  

}

void LoginUser(){
    struct data_user;
    FILE *fuser;
    char username[50], pw[50];
    int percobaan = 0, berhasil = 0;

    system("cls");
    fuser = fopen("AkunUser.dat", "rb");
    if (fuser == NULL) {
        printf("Gagal membuka file\n");
        return;
    }

    printf("=== LOGIN USER ===\n");

    while (percobaan < 3 && !berhasil) {
        printf("Masukan Username: ");
        gets(username);
        printf("Masukan Password");
        gets(pw);

        rewind(fuser);
        while (fread(&data_user, sizeof(data_user), 1, fuser) ==1) {
            if (strcmp(username, data_user.username) == 0 && strcmp(pw, data_user.password) == 0) {
                printf("== LOGIN BERHASIL ==\n");
                printf("== SELAMAT DATANG GAMERS ==\n");
                berhasil = 1;
                fclose(fuser);
                system("pause");
                MenuUser();
                return;
            }
            
        }
        
    }
      
}

void LoginDeveloper(){

}

void RegistrasiUser(){
    system("cls");
    fuser = fopen("AkunUser.dat", "ab");

    getchar();
    printf("=== REGISTRASI USER ===\n");
    printf("\nusername: ");
    gets(data_user.username);
    printf("\npassword: ");
    gets(data_user.password);

    fwrite(&data_user, sizeof(data_user), 2, fuser);
    fclose(fuser);

    printf("REGISTRASI BERHASIL...\n");
    system("pause");
    LoginUser();
}

void MenuAdmin(){
    int pilihan;
    while (1) {
        system("cls");
        printf("== SELAMAT DATANG DI MENU ADMIN ==\n");
        printf("1. List Akun User\n");
        printf("2. Kumulatif Pendapatan\n");
        printf("3. Riwayat Pembelian\n");
        printf("4. Logout\n");
        printf("Silahkan input pilihan anda: \n");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
            ListAkunUser();
            break;
            
            case 2:
            KumulatifPendapatan();
            break;

            case 3:
            RiwayatPembelian();
            break;

            case 4:
            printf("Terimakasih Telah Menggunakan DGameShop");
            exit(0);
            break;

            default:
            printf("Pilihan tidak valid!, coba lagi.\n");
            system("pause");
            break;
        }

    }

}
void ListAkunUser(){
    system("cls");
    fuser = fopen("AkunUser.dat", "rb");
    if (fuser == NULL) {
        printf("Gagal membuka file AkunUser.dat\n");
        system("pause");
        MenuAdmin();
        return;
    }

    printf("=== LIST AKUN USER ===\n");
    printf("%-20s %-20s %-20s %-20s %-20s\n", "Username", "Nama", "Password", "Email", "No Telp");
    
    while (fread(&data_user, sizeof(data_user), 1, fuser) == 1) {
        printf("%-20s %-20s %-20s %-20s %-20s\n", data_user.username, data_user.nama, data_user.password, data_user.email, data_user.no_telp);
    }

    fclose(fuser);
    system("pause");

}
void KumulatifPendapatan(){
    FILE *fpendapatan;
    char line[256];
    int totalPendapatan = 0;
    int totalAdmin = 0;

    system("cls");
    fpendapatan = fopen("pendapatan.dat", "r");
    if (fpendapatan == NULL) {
        printf("Gagal membuka file pendapatan.dat\n");
        system("pause");
        MenuAdmin();
        return;
    }

    printf("=== KUMULATIF PENDAPATAN ===\n");
    while (fgets(line, sizeof(line), fpendapatan)) {
        printf("%s", line);
        int devAmount = 0, adminAmount = 0;
        // Cek apakah baris ini adalah baris Admin
        if (sscanf(line, "Admin: %d", &adminAmount) == 1) {
            totalAdmin += adminAmount;
        }
        // Untuk total pendapatan (admin + dev)
        if (sscanf(line, "Dev  : %d", &devAmount) == 1) {
            totalPendapatan += devAmount;
        }
        if (sscanf(line, "Admin: %d", &adminAmount) == 1) {
            totalPendapatan += adminAmount;
        }
    }

    fclose(fpendapatan);
    printf("\nTotal Pendapatan: Rp%d\n", totalPendapatan);
    printf("Total Pendapatan Admin saja: Rp%d\n", totalAdmin);
    system("pause");


}
void RiwayatPembelian(){
    FILE *friwayat;
    char line[256];

    system("cls");
    friwayat = fopen("riwayat.dat", "r");
    if (friwayat == NULL) {
        printf("Gagal membuka file riwayat.dat\n");
        system("pause");
        MenuAdmin();
        return;
    }

    printf("=== RIWAYAT PEMBELIAN ===\n");
    while (fgets(line, sizeof(line), friwayat)) {
        printf("%s", line);
    }

    fclose(friwayat);
    system("pause");
   
}
void MenuUser(){
    int pilihan;
    while (1) {
        system("cls");
        printf("== SELAMAT DATANG DI MENU USER ==\n");
        printf("1. Home Page\n");
        printf("2.  Profile User\n");
        printf("3. Registrasi Developer\n");
        printf("4. Logout\n");
        printf("Silahkan input pilihan anda :\n");
        scanf("%d", &pilihan);
        
        switch (pilihan) {
            case 1:
            HomePage();
            break;
            
            case 2:
            ProfileUser();
            break;

            case 3:
            RegistrasiDeveloper();
            break;

            case 4:
            printf("Terimakasih telah menggunakan DGameShop!\n");
            exit(0);
            break;

            default:
            printf("Pilihan tidak valid!, silahkan coba lagi.");
            system("pause");
            break;
        }

    }
    
}

void HomePage(){
    int pilihan;
    while (1) {
        system("cls");
        printf("== Selamat Datang di Home Page DGameShop!\n");
        printf("1. Store Page\n");
        printf("2. Wallet\n");
        printf("3. Kembali\n");
        printf("Silahkan input pilihan anda\n");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
            StorePage();
            break;

            case 2:
            Wallet();
            break;

            case 3:
            MenuUser();
            break;
        
            default:
            printf("Pilihan tidak valid!, silahkan coba lagi");
            system("pause");
            break;
        }

    }
    
}

void StorePage(){
    FILE *fgame;
    struct Game list_game[69];
    int jumlah_game = 0;
    int pilihan;

    fgame = fopen("games.dat", "rb");
    if(!fgame) {
        printf("\nGagal membuka file!\n");
        printf("Press enter kalau melihat ini.");
        getchar();
        HomePage();
        return;
    }

    while(fread(&list_game[jumlah_game], sizeof(struct Game), 1, fgame)) {
        jumlah_game++;
        if(jumlah_game >= 69)
        break;
    }
    fclose(fgame);

    for(int i = 0; i < jumlah_game; i++) {
        for(int j = 0; j < jumlah_game - i - 1; j++) {
            if(list_game[j].harga > list_game[j + 1].harga) {
                struct Game temp = list_game[j];
                list_game[j] = list_game[j + 1];
                list_game[j + 1] = temp;
            }
        }
    }

    printf("=== STORE PAGE ===\n");
    if(jumlah_game == 0) {
        printf("Game belum tersedia.\n\n");
    } else {
        printf("Daftar game (berdasarkan harga):\n");
        for(int i = 0; i < jumlah_game; i++) {
            printf("%d. %s — Rp%d", i + 1, list_game[i].judul, list_game[i].harga);
        }
    }

    printf("\nMenu:\n");
    printf("1. Searching\n");
    printf("2. Exit\n");
    printf("Pilihan : "); scanf("%d", &pilihan);

    // fuff i used switch by accident, oh well it's the same lol
    switch (pilihan) {
        case 1:
            system("cls");
            Searching();
            break;
        case 2:
            system("cls");
            HomePage();
            return;
        default:
            system("cls");
            printf("\nPilihan tidak valid! Coba lagi.\n\n");
            StorePage();
            break;
    }

}
void ToLower(char *string) {
    for(int i = 0; string[i]; i++) {
        string[i] = tolower(string[i]);
    }
}
void Searching(){
    FILE *fgame;
    struct Game games;
    char namaGame[50];
    char input_lower[50], game_lower[50];
    int ditemukan = 0;

    printf("=== SEARCH GAME ===\n");
    printf("Nama Game : ");
    fgets(namaGame, sizeof(namaGame), stdin);
    namaGame[strcspn(namaGame, "\n")] = '\0';

    strcpy(input_lower, namaGame);
    ToLower(input_lower);

    fgame = fopen("games.dat", "rb");
    if(!fgame) {
        printf("\nGagal membuka file!\n");
        printf("Press enter kalau melihat ini.");
        getchar();
        StorePage();
        return;
    }

    while(fread(&games, sizeof(struct Game), 1, fgame)) {
        strcpy(game_lower, games.judul);
        ToLower(game_lower);

        if(strcmp(input_lower, game_lower) == 0) {
            ditemukan = 1;

            printf("\nGame ditemukan!\n");
            printf("Judul           : %s\n", games.judul);
            printf("Genre           : %s\n", games.genre);
            printf("Platform        : %s\n", games.platform);
            printf("Penggembang     : %s\n", games.pengembang);
            printf("Tanggal Rilis   : %s\n", games.tanggalRilis);
            printf("Harga           : %d\n", games.harga);
            printf("Rating          : %.1f\n", games.rating);
            break;
        }
    }   

    fclose(fgame);

    if(!ditemukan) {
        printf("Game tidak tersedia!\n");
        printf("Press enter kalau melihat ini.");
        getchar();
        StorePage();
        return;
    }
    printf("Press Enter untuk melihat game. (TEMPORARY MESSAGE)");
    getchar();
    system("cls");  
    GamePage(&games);
}
void GamePage(struct Game *games){
    int pilihan;

    printf("=== GAME PAGE ===\n");
    printf("Judul           : %s\n", games->judul);
    printf("Genre           : %s\n", games->genre);
    printf("Platform        : %s\n", games->platform);
    printf("Penggembang     : %s\n", games->pengembang);
    printf("Tanggal Rilis   : %s\n", games->tanggalRilis);
    printf("Harga           : %d\n", games->harga);
    printf("Rating          : %.1f\n", games->rating);

    printf("\nMenu :\n");
    printf("1. Membeli Game\n");
    printf("2. Feedback Game\n");
    printf("3. Exit\n");
    printf("Pilihan : "); scanf("%d", &pilihan);

    switch (pilihan) {
        case 1:
            system("cls");
            BeliGame(games);
            break;
        case 2:
            system("cls");
            FeedbackGame(games);
            break;
        case 3:
            system("cls");
            StorePage();
            return;
        default:
            system("cls");
            printf("\nPilihan tidak valid! Coba lagi.\n\n");
            GamePage(games);
            break;
    }

}
void BeliGame(struct Game *games){
    // struct User user;
    // int hasilDeveloper;
    // int hasilAdmin;

    // if(user_sekarang.saldo < games->harga) {
    //     printf("Maaf, Wallet Anda tidak cukup untuk membeli game ini!\n");
    //     GamePage(games);
    //     return;
    // }

    // user_sekarang.saldo -= games->harga;

    // FILE *fpendapatan = fopen("pendapatan.dat", "ab");
    // if(fpendapatan) {
    //     hasilDeveloper = 0.7 * games->harga;
    //     hasilAdmin = 0.3 * games->harga;
    //     fprintf(fpendapatan, "Game : %s\nDev  : %d\nAdmin: %d\n\n", games->judul, hasilDeveloper, hasilAdmin);
    //     fclose(fpendapatan);
    // }

    // FILE *friwayat = fopen("riwayat.dat", "ab");
    // if(friwayat) {
    //     fprintf(friwayat, "%s membeli %s dengan harga Rp%d\n", user_sekarang.username, games->judul, games->harga);
    //     fclose(friwayat);
    // }

    // FILE *fuser = fopen("user.dat", "rb+");
    // if(fuser) {
    //     while(fread(&user, sizeof(struct User), 1, fuser)) {
    //         if(strcmp(user.username, user_sekarang.username) == 0) {
    //             user.saldo = user_sekarang.saldo;
    //             fseek(fuser, -sizeof(struct User), SEEK_CUR);
    //             fwrite(&user, sizeof(struct User), 1, fuser);
    //             break;
    //         }
    //     }
    //     fclose(fuser);
    // }
    // printf("Pembelian game berhasil!\n");
    // printf("Sisa saldo : Rp%d\n", user_sekarang.saldo);
    // printf("Press Enter untuk melihat game. (TEMPORARY MESSAGE)");
    // getchar();
    // GamePage(games);

}
void FeedbackGame(struct Game *games){
    // char feedback[256];

    // printf("=== FEEDBACK ===\n");
    // printf("Game : %s\n", games->judul);
    // printf("Tuliskan review / feedback Anda : ");
    // fgets(feedback, sizeof(feedback), stdin);
    // feedback[strcspn(feedback, '\n')] = '\0';

    // FILE *ffeedback = fopen("feedback.txt", "a");
    // if(ffeedback) {
    //     fprintf(ffeedback, "%s memiliki feedback tentang %s : %s\n", user_sekarang.username, games->judul, feedback);
    //     fclose(ffeedback);
    //     printf("Feedback berhasil terkirim!\n");
    // } else {
    //     printf("Feedback gagal terkirim.\n");
    // }
    
    // printf("Press Enter untuk melihat game. (TEMPORARY MESSAGE)");
    // getchar();
    // GamePage(games);


}
void Wallet(){
    // struct User user;
    // int pilihan;

    // printf("=== DGAMESHOP WALLET ===\n");
    // printf("Username    : %s\n", user_sekarang.username);
    // printf("Saldo       : %d\n", user_sekarang.saldo);

    // printf("\nMenu :\n");
    // printf("1. Tambah Saldo\n");
    // printf("2. Exit\n");
    // printf("Pilihan : "); scanf("%d", &pilihan);

    // // hmm should i use switch hehe
    // if (pilihan == 1) {
    //     system("cls");
    //     tambahWallet();
    // } else if (pilihan == 2) {
    //     system("cls");
    //     HomePage();
    // } else {
    //     system("cls");
    //     printf("\nPilihan tidak valid! Coba lagi.\n\n");
    //     Wallet();
    // }

}
void tambahWallet() {
    // struct User user;
    // int tambah;

    // printf("Masukkan jumlah saldo yang ingin ditambah : "); scanf("%d", &tambah);
    // if (tambah <= 0) {
    //     printf("Jumlah tidak valid!\n\n");
    //     printf("Press enter kalau melihat ini.");
    //     getchar();
    //     Wallet();
    //     return;
    // }

    // user_sekarang.saldo += tambah;
    // printf("Saldo berhasil ditambah. Saldo sekarang: %d\n", user_sekarang.saldo);

    // FILE *fuser = fopen("user.dat", "rb+");
    // if (fuser) {
    //     while(fread(&user, sizeof(struct User), 1, fuser)) {
    //         if(strcmp(user.username, user_sekarang.username) == 0) {
    //             user.saldo = user_sekarang.saldo;
    //             fseek(fuser, -sizeof(struct User), SEEK_CUR);
    //             fwrite(&user, sizeof(struct User), 1, fuser);
    //             break;
    //         }
    //     }
    //     fclose(fuser);
    // } else {
    //     printf("Gagal membuka file!\n");
    // }
    // printf("Press enter kalau melihat ini.");
    // getchar();
    // Wallet();
}
void ProfileUser(){
    //  int pilihan;
    
    // printf("=== PROFILE USER ===\n");
    // printf("Username    : %s\n", user_sekarang.username);
    // printf("Email       : %s\n", user_sekarang.email);
    // printf("No. Telepon : %s\n", user_sekarang.no_telp);
    // printf("Saldo       : %d\n", user_sekarang.saldo);

    // if(user_sekarang.developer) {
    //     printf("Status : Developer\n");
    //     printf("Hello Developer, %s!\n", user_sekarang.username);
    // } else {
    //     printf("Status : User\n");
    // }

    // printf("\nMenu:\n");
    // printf("1. Exit\n");
    // printf("Pilihan : "); scanf("%d", &pilihan);

    // if (pilihan == 1) {
    //     system("cls");
    //     MenuUser();
    // } else {
    //     system("cls");
    //     printf("\nPilihan tidak valid! Coba lagi.\n\n");
    //     ProfileUser();
    // }
}
void RegistrasiDeveloper(){
    system("cls");
    fuser = fopen("AkunUser.dat", "ab");

    getchar();
    printf("=== REGISTRASI DEVELOPER ===\n");
    printf("\nusername: ");
    gets(data_user.username);
    printf("\npassword: ");
    gets(data_user.password);
    printf("\nnama: ");
    gets(data_user.nama);
    printf("\nemail :");
    gets(data_user.email);
    printf("\nnomer telepon: ");
    scanf("%d", &data_user.no_telp);
    getchar();
    printf("\nnomer rekening: ");
    scanf("%d", &data_user.saldo);
    getchar();

    data_user.developer = 1;

    fwrite(&data_user, sizeof(data_user), 1, fuser);
    fclose(fuser);

    printf("REGISTRASI BERHASIL...\n");
    system("pause");
    LoginDeveloper();

}
void MenuDeveloper(){
    int pilihan;
    while (1) {
        system("cls");
        printf("=== SELAMAT DATANG DI MENU DEVELOPER ===\n");
        printf("1. Tambah Game\n");
        printf("2. Update Game\n");
        printf("3. Lihat Feedback\n");
        printf("4. Logout\n");
        printf("Silahkan Input Pilihan Anda :\n");
        scanf("%d", &pilihan);
        getchar();

        switch (pilihan) {
            case 1:
            TambahGame();
            break;
            
            case 2:
            UpdateGame();
            break;
        
            case 3:
            LihatFeedback();
            break;
        
            case 4:
            printf("Terimakasih Telah Menggunakan DGameShop!\n");
            exit(0);
            break;

            default:
            printf("Pilihan anda tidak valid!, silahkan coba lagi\n");
            system("pause");
            break;
        }

    }
    

}
void TambahGame(){
    fgame = fopen("games.dat", "ab");
    if (fgame == NULL) {
        printf("Gagal membuka file!");
        return;
    }

    system("cls");
    printf("=== TAMBAH GAME ==="); 
    printf("Masukan Judul Game :\n");
    gets(game.judul);
    printf("Masukan Genre Game :\n");
    gets(game.genre);
    printf("Masukan Platform Game :\n");
    gets(game.platform);
    printf("Masukan Pengembang Game :\n");
    gets(game.pengembang);
    printf("Masukan Tanggal Rilis Game :\n");
    gets(game.tanggalRilis);
    printf("Masukan Harga Game :\n");
    scanf("%d", &game.harga);
    printf("Masukan Rating Game :\n");
    scanf("%f", &game.rating);
    getchar();

    fwrite(&game, sizeof(game), 1, fgame);
    fclose(fgame);

    printf("Game berhasil ditambahkan!\n");
    system("pause");
    MenuDeveloper();


}
void UpdateGame(){
     fgame = fopen("games.dat", "rb+");
    if (fgame == NULL) {
        printf("Gagal membuka file!\n");
        return;
    }

    system("cls");
    printf("=== UPDATE GAME ===\n");
    
    printf("Masukan Judul Game yang ingin diupdate:\n");
    char judul[50]; 
    gets(judul);
    rewind(fgame);

    int ditemukan = 0;
    while (fread(&game, sizeof(game), 1, fgame) == 1) {
        if (strcmp(game.judul, judul) == 0) {
            printf("Masukan Genre Game Baru:\n");
            gets(game.genre);
            printf("Masukan Platform Game Baru:\n");
            gets(game.platform);
            printf("Masukan Pengembang Game Baru:\n");
            gets(game.pengembang);
            printf("Masukan Tanggal Rilis Game Baru:\n");
            gets(game.tanggalRilis);
            printf("Masukan Harga Game Baru:\n");
            scanf("%d", &game.harga);
            printf("Masukan Rating Game Baru:\n");
            scanf("%f", &game.rating);
            getchar();

            fseek(fgame, -sizeof(game), SEEK_CUR);
            fwrite(&game, sizeof(game), 1, fgame);
            ditemukan = 1;
            printf("Game berhasil diupdate!\n");
            break;
        }
    }
    fclose(fgame);

    if (!ditemukan) {
        printf("Game dengan judul '%s' tidak ditemukan!\n", judul);
    }
    system("pause");
    MenuDeveloper();
}
void LihatFeedback(){
     ffeedback = fopen("feedback.dat", "rb");
    if (ffeedback == NULL) {
        printf("Gagal membuka file feedback!\n");
        return;
    }

    system("cls");
    printf("=== LIHAT FEEDBACK ===\n");
    int ada = 0;
    while (fread(&data_user, sizeof(data_user), 1, ffeedback) == 1) {
        if (data_user.feedback[0] != '\0') {
            printf("Username: %s\n", data_user.username);
            printf("Feedback: %s\n", data_user.feedback);
            printf("-------------------------\n");
            ada = 1;
        }
    }
    if (!ada) {
        printf("Tidak ada feedback yang tersedia.\n");
    }
    fclose(ffeedback);
    system("pause");
    MenuDeveloper();
}
