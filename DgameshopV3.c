#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct User{
    char username[50];
    char nama[50];
    char password[50];
    char email[100];
    char feedback[50];
    char no_telp[50];
    int saldo;
    int developer;
} data_user, current_user;

struct Game{
    char judul[50];
    char genre[50];
    char platform[50];
    char pengembang[50];
    char tanggalRilis[50];
    int harga;
    float rating;
} game;

FILE *fuser;
FILE *fadmin;
FILE *fdeveloper;
FILE *fgame;
FILE *ffeedback;
FILE *fpendapatan;

void MenuLogin();
void LoginAdmin();
void LoginUser();
void LoginDeveloper();
void RegistrasiUser();
void MenuAdmin();
void ListAkunUser();
void KumulatifPendapatan();
void RiwayatPembelian();
void MenuUser();
void HomePage();
void StorePage();
void Searching();
void GamePage(struct Game *games);
void BeliGame(struct Game *games);
void FeedbackGame(struct Game *games);
void Wallet();
void tambahWallet();
void ProfileUser();
void RegistrasiDeveloper();
void MenuDeveloper();
void TambahGame();
void UpdateGame();
void LihatFeedback();
void ToLower(char *string);

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
        printf("Silahkan input pilihan anda: ");
        scanf("%d", &pilihan);
        getchar();

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
        scanf("%s", username);
        printf("Masukan Password: ");
        scanf("%s", pw);

        rewind(fuser);
        while (fread(&data_user, sizeof(data_user), 1, fuser) == 1) {
            if (strcmp(username, data_user.username) == 0 && strcmp(pw, data_user.password) == 0) {
                printf("== LOGIN BERHASIL ==\n");
                printf("== SELAMAT DATANG GAMERS ==\n");
                berhasil = 1;
                current_user = data_user;
                fclose(fuser);
                system("pause");
                MenuUser();
                return;
            }
        }
        percobaan++;
        if (percobaan < 3) {    
            printf("Username atau Password salah! Silahkan coba lagi.\n");
            printf("Percobaan ke-%d dari 3\n", percobaan);
            system("pause");
        } else {
            printf("Mohon maaf, batas percobaan login telah habis, silahkan coba lagi nanti...\n");
            fclose(fuser);
            system("pause");
            MenuLogin();
        }
    }
      
}

void LoginDeveloper(){
    char username[50], pw[50];
    int percobaan = 0, berhasil = 0;

    system("cls");
    fuser = fopen("AkunUser.dat", "rb");
    if (fuser == NULL) {
        printf("Gagal membuka file\n");
        return;
    }

    printf("=== LOGIN DEVELOPER ===\n");

    while (percobaan < 3 && !berhasil) {
        printf("Masukan Username: ");
        scanf("%s", username);
        printf("Masukan Password: ");
        scanf("%s", pw);

        rewind(fuser);
        while (fread(&data_user, sizeof(data_user), 1, fuser) ==1) {
            if (strcmp(username, data_user.username) == 0 && strcmp(pw, data_user.password) == 0 && data_user.developer == 1) {
                printf("== LOGIN BERHASIL ==\n");
                printf("== SELAMAT DATANG DEVELOPER ==\n");
                berhasil = 1;
                fclose(fuser);
                system("pause");
                MenuDeveloper();
                return;
            }
            
        }
        percobaan++;
        if (percobaan < 3) {
            printf("Username atau Password salah! Silahkan coba lagi.\n");
            printf("Percobaan ke-%d dari 3\n", percobaan);
            system("pause");
        } else {
            printf("Mohon maaf, batas percobaan login telah habis, silahkan coba lagi nanti...\n");
            fclose(fuser);
            system("pause");
            MenuLogin();
        }
        
    }
      
}

void RegistrasiUser(){
    system("cls");
    fuser = fopen("AkunUser.dat", "ab");
    if (fuser == NULL) {
        printf("Gagal membuka file AkunUser.dat\n");
        return;
    }

    system("cls");
    printf("=== REGISTRASI USER ===\n");
    printf("\nusername: ");
    gets(data_user.username);
    printf("\npassword: ");
    gets(data_user.password);

    data_user.developer = 0;

    fwrite(&data_user, sizeof(data_user), 1, fuser);
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
        printf("Silahkan input pilihan anda: ");
        scanf("%d", &pilihan);
        getchar();

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
    printf("%-20s %-20s %-25s %-20s\n", "Username", "Password", "Email", "No Telp");
    
    while (fread(&data_user, sizeof(data_user), 1, fuser) == 1) {
        printf("%-20s %-20s %-25s %-20s\n", data_user.username, data_user.password, data_user.email, data_user.no_telp);
    }

    fclose(fuser);
    system("pause");

}

void KumulatifPendapatan(){
    FILE *fpendapatan;
    char line[256];
    int devAmount = 0, adminAmount = 0;
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
        if (sscanf(line, "Dev  : %d", &devAmount) == 1) {
            totalPendapatan += devAmount;
        }
        if (sscanf(line, "Admin: %d", &adminAmount) == 1) {
            totalPendapatan += adminAmount;
            totalAdmin += adminAmount;
        }
    }

    fclose(fpendapatan);
    printf("\nTotal Pendapatan: Rp%d\n", totalPendapatan);
    printf("Total Pendapatan Admin saja: Rp%d\n", totalAdmin);
    system("pause");
    MenuAdmin();
}

void RiwayatPembelian(){
     FILE *friwayat;
    char line[256];
    char namaGame[50], username[50];
    int harga, potDev, potAdmin;

    system("cls");
    friwayat = fopen("riwayat.dat", "r");
    if (friwayat == NULL) {
        printf("Gagal membuka file riwayat.dat\n");
        system("pause");
        MenuAdmin();
        return;
    }

    printf("=== RIWAYAT PEMBELIAN ===\n");
    printf("%-20s %-15s %-10s %-10s %-10s\n", "Nama Game", "Username", "Harga", "Dev", "Admin");
    printf("---------------------------------------------------------------------\n");
    while (fgets(line, sizeof(line), friwayat)) {
        if (sscanf(line, "%49[^,],%49[^,],%d,%d,%d", namaGame, username, &harga, &potDev, &potAdmin) == 5) {
            printf("%-20s %-15s %-10d %-10d %-10d\n", namaGame, username, harga, potDev, potAdmin);
        }
    }

    fclose(friwayat);
    system("pause");
    MenuAdmin();
}

void MenuUser(){
    int pilihan;
    while (1) {
        system("cls");
        printf("== SELAMAT DATANG DI MENU USER ==\n");
        printf("1. Home Page\n");
        printf("2. Profile User\n");
        printf("3. Registrasi Developer\n");
        printf("4. Logout\n");
        printf("Silahkan input pilihan anda :");
        scanf("%d", &pilihan);
        getchar();
        
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
        printf("Silahkan input pilihan anda :");
        scanf("%d", &pilihan);
        getchar();

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

    system("cls");

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
            printf("%d. %s : Rp%d\n", i + 1, list_game[i].judul, list_game[i].harga);
        }
    }

    printf("\nMenu:\n");
    printf("1. Searching\n");
    printf("2. Exit\n");
    printf("Pilihan : "); 
    scanf("%d", &pilihan);
    getchar(); 

        switch (pilihan) {
            case 1:
            Searching();
            break;

            case 2:
            HomePage();
            return;

            default:
            printf("\nPilihan tidak valid! Coba lagi.\n\n");
            StorePage();
            system("pause");
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
    for (int i = 0; namaGame[i] != '\0'; i++) {
    if (namaGame[i] == '\n') {
        namaGame[i] = '\0';
        break;
        }
    }

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
            system("cls");

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
    getchar(); 
    GamePage(&games);
    system("pause");
}
void GamePage(struct Game *games){
    int pilihan;

    system("cls");
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
        BeliGame(games);
        break;

        case 2:
        FeedbackGame(games);
        break;

        case 3:
        StorePage();
        return;

        default:
        printf("\nPilihan tidak valid! Coba lagi.\n\n");
        GamePage(games);
        system("pause");
        break;
    }

}

void BeliGame(struct Game *games){
    int hasilDeveloper;
    int hasilAdmin;

    if(current_user.saldo < games->harga) {
        printf("Maaf, Wallet Anda tidak cukup untuk membeli game ini!\n");
        GamePage(games);
        return;
    }

    
    current_user.saldo -= games->harga;

    
    FILE *fpendapatan = fopen("pendapatan.dat", "a");
    if(fpendapatan) {
        hasilDeveloper = 0.7 * games->harga;
        hasilAdmin = 0.3 * games->harga;
        fprintf(fpendapatan, "Game : %s\nDev  : %d\nAdmin: %d\n\n", games->judul, hasilDeveloper, hasilAdmin);
        fclose(fpendapatan);
    }

    
    FILE *friwayat = fopen("riwayat.dat", "a");
if(friwayat) {
    int hasilDeveloper = 0.7 * games->harga;
    int hasilAdmin = 0.3 * games->harga;
    fprintf(friwayat, "%s,%s,%d,%d,%d\n",
        games->judul,
        current_user.username,
        games->harga,
        hasilDeveloper,
        hasilAdmin
    );
    fclose(friwayat);
    }

   
    FILE *fuser = fopen("AkunUser.dat", "rb+");
    struct User temp;
    if(fuser) {
        while(fread(&temp, sizeof(struct User), 1, fuser)) {
            if(strcmp(temp.username, current_user.username) == 0) {
                temp.saldo = current_user.saldo;
                fseek(fuser, -sizeof(struct User), SEEK_CUR);
                fwrite(&temp, sizeof(struct User), 1, fuser);
                break;
            }
        }
        fclose(fuser);
    }
    system("cls");
    printf("Pembelian game berhasil!\n");
    printf("Sisa saldo : Rp%d\n", current_user.saldo);
    getchar();
    system("pause");
    GamePage(games);
    
}

void FeedbackGame(struct Game *games){
    char feedback[256];
    

    printf("=== FEEDBACK ===\n");
    printf("Game : %s\n", games->judul);
    printf("Tuliskan review / feedback Anda : ");
    fgets(feedback, sizeof(feedback), stdin);
    fgets(feedback, sizeof(feedback), stdin);
    for (int i = 0; feedback[i] != '\0'; i++) {
    if (feedback[i] == '\n') {
        feedback[i] = '\0';
        break;
        }
    }

    FILE *ffeedback = fopen("feedback.txt", "a");
    if(ffeedback) {
        fprintf(ffeedback, "%s memiliki feedback tentang %s : %s\n", current_user.username, games->judul, feedback);
        fclose(ffeedback);
        printf("Feedback berhasil terkirim!\n");
    } else {
        printf("Feedback gagal terkirim.\n");
    }
    
    printf("Press Enter untuk melihat game. (TEMPORARY MESSAGE)");
    getchar();
    GamePage(games);
    system("pause");    
}

void Wallet(){
    struct User user;
    int pilihan;
    int found = 0;

    FILE *fuser = fopen("AkunUser.dat", "rb");
    if(fuser) {
        while(fread(&user, sizeof(struct User), 1, fuser)) {
            if(strcmp(user.username, current_user.username) == 0) {
                found = 1;
                break;
            }
        }
        fclose(fuser);
    } else {
        printf("Gagal membuka file AkunUser.dat!\n");
        return;
    }

    if (!found) {
        printf("User tidak ditemukan!\n");
        system("pause");
        return;
    }

    current_user.saldo = user.saldo;

    system("cls");
    printf("=== DGAMESHOP WALLET ===\n");
    printf("Username    : %s\n", current_user.username);
    printf("Saldo       : %d\n", current_user.saldo);

    printf("\nMenu :\n");
    printf("1. Tambah Saldo\n");
    printf("2. Exit\n");
    printf("Pilihan : "); 
    scanf("%d", &pilihan);
    getchar();

    if (pilihan == 1) {
        system("cls");
        tambahWallet();
    } else if (pilihan == 2) {
        system("cls");
        HomePage();
    } else {
        system("cls");
        printf("\nPilihan tidak valid! Coba lagi.\n\n");
        Wallet();
    }
    system("pause");
    return;
}

void tambahWallet() {
    struct User users[100];
    int jumlah = 0;
    int tambah;
    int found = 0;

    FILE *fuser = fopen("AkunUser.dat", "rb");
    if (!fuser) {
        printf("Gagal membuka file!\n");
        system("pause");
        getchar();
        Wallet();
        return;
    }

    while (fread(&users[jumlah], sizeof(struct User), 1, fuser) == 1) {
        jumlah++;
    }
    fclose(fuser);

    printf("Masukkan jumlah saldo yang ingin ditambah : ");
    scanf("%d", &tambah);
    getchar();
    if (tambah <= 0) {
        printf("Jumlah tidak valid!\n\n");
        printf("Press enter kalau melihat ini.");
        getchar();
        Wallet();
        return;
    }

    for (int i = 0; i < jumlah; i++) {
        if (strcmp(users[i].username, current_user.username) == 0) {
            users[i].saldo += tambah;
            current_user.saldo = users[i].saldo;
            printf("Saldo berhasil ditambah. Saldo sekarang: %d\n", users[i].saldo);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("User tidak ditemukan!\n");
        printf("Press enter kalau melihat ini.");
        getchar();
        Wallet();
        return;
    }

    fuser = fopen("AkunUser.dat", "wb");
    if (!fuser) {
        printf("Gagal membuka file!\n");
        printf("Press enter kalau melihat ini.");
        getchar();
        Wallet();
        return;
    }
    fwrite(users, sizeof(struct User), jumlah, fuser);
    fclose(fuser);
    printf("Saldo berhasil ditambahkan!\n");
    getchar();
    Wallet();
    system("pause");
    return;
}
void ProfileUser(){
     int pilihan;

    printf("=== PROFILE USER ===\n");
    printf("Username    : %s\n", current_user.username);
    printf("Email       : %s\n", current_user.email);
    printf("No. Telepon : %s\n", current_user.no_telp);
    printf("Saldo       : %d\n", current_user.saldo);

    if(current_user.developer) {
        printf("Status : Developer\n");
        printf("Hello Developer, %s!\n", current_user.username);
    } else {
        printf("Status : User\n");
    }

    printf("\nMenu:\n");
    printf("1. Exit\n");
    printf("Pilihan : "); scanf("%d", &pilihan);

    if (pilihan == 1) {
        system("cls");
        MenuUser();
    } else {
        system("cls");
        printf("\nPilihan tidak valid! Coba lagi.\n\n");
        ProfileUser();
    }
}
void RegistrasiDeveloper(){
    system("cls");
    printf("=== REGISTRASI DEVELOPER ===\n");

    printf("\nEmail : ");
     gets(current_user.email);

    printf("\nNo. Telepon : ");
    fgets(current_user.no_telp, sizeof(current_user.no_telp), stdin);
    current_user.no_telp[strcspn(current_user.no_telp, "\n")] = 0;

    current_user.developer = 1;

    FILE *fuser = fopen("AkunUser.dat", "rb+");
    struct User temp;
    if(fuser) {
        while(fread(&temp, sizeof(struct User), 1, fuser)) {
            if(strcmp(temp.username, current_user.username) == 0) {
                temp.developer = 1;
                strcpy(temp.email, current_user.email);
                strcpy(temp.no_telp, current_user.no_telp);
                fseek(fuser, -sizeof(struct User), SEEK_CUR);
                fwrite(&temp, sizeof(struct User), 1, fuser);
                break;
            }
        }
        fclose(fuser);
    }

    printf("REGISTRASI DEVELOPER BERHASIL...\n");
    system("pause");
    MenuUser();
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
        printf("Silahkan Input Pilihan Anda :");
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
    printf("=== TAMBAH GAME ===\n"); 
    printf("Masukan Judul Game :");
    gets(game.judul);
    printf("Masukan Genre Game :");
    gets(game.genre);
    printf("Masukan Platform Game :");
    gets(game.platform);
    printf("Masukan Pengembang Game :");
    gets(game.pengembang);
    printf("Masukan Tanggal Rilis Game :");
    gets(game.tanggalRilis);
    printf("Masukan Harga Game :");
    scanf("%d", &game.harga);
    printf("Masukan Rating Game :");
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
    
    printf("Masukan Judul Game yang ingin diupdate:");
    char judul[50]; 
    gets(judul);
    rewind(fgame);

    int ditemukan = 0;
    while (fread(&game, sizeof(game), 1, fgame) == 1) {
        if (strcmp(game.judul, judul) == 0) {
            printf("Masukan Genre Game Baru:");
            gets(game.genre);
            printf("Masukan Platform Game Baru:");
            gets(game.platform);
            printf("Masukan Pengembang Game Baru:");
            gets(game.pengembang);
            printf("Masukan Tanggal Rilis Game Baru:");
            gets(game.tanggalRilis);
            printf("Masukan Harga Game Baru:");
            scanf("%d", &game.harga);
            printf("Masukan Rating Game Baru:");
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
    FILE *ffeedback = fopen("feedback.txt", "r");
    char line[256];
    int ada = 0;

    if (ffeedback == NULL) {
        printf("Gagal membuka file feedback!\n");
        system("pause");
        MenuDeveloper();
        return;
    }

    system("cls");
    printf("=== LIHAT FEEDBACK ===\n");
    while (fgets(line, sizeof(line), ffeedback)) {
        printf("%s", line);
        ada = 1;
    }
    if (!ada) {
        printf("Tidak ada feedback yang tersedia.\n");
    }
    fclose(ffeedback);
    system("pause");
    MenuDeveloper();
}