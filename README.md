# pac-man
# 👾 Pacman Console Game in C++

Sebuah game **Pacman sederhana** yang dibangun menggunakan **C++** dan pendekatan **Object-Oriented Programming (OOP)**. Game ini dimainkan melalui terminal/console dan melibatkan logika gerakan, collision, manajemen nyawa, dan scoring.

## 🎮 Fitur
- Kendali karakter Pacman dengan tombol `W`, `A`, `S`, `D`
- Misi: kumpulkan semua dot (titik) untuk menang
- Musuh: 1 hantu bergerak secara acak
- Kehilangan nyawa saat bertabrakan dengan hantu
- Game berakhir jika semua dot terkumpul atau nyawa habis
- Tampilan berbasis karakter console

## 🛠 Teknologi
- Bahasa: C++
- Konsep: Class Inheritance, Polymorphism, Dynamic Memory
- Platform: Console (cross-platform, `system("cls")` untuk Windows, `clear` untuk Linux/Mac)

## 📦 Struktur OOP
- `Character` (abstract class): dasar untuk `Pacman` dan `Ghost`
- `Dot`: objek collectible
- `Pacman`: pemain utama, punya skor dan nyawa
- `Ghost`: musuh yang bergerak acak

## 🚀 Cara Menjalankan
1. Clone repo ini:
   ```bash
   git clone https://github.com/yourusername/pacman-cpp.git
   cd pacman-cpp
