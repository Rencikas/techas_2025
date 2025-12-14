# 🚗 Automobilių techninės apžiūros registras

Konsolinė taikomoji programa, realizuota C programavimo kalba, skirta automobilių techninės apžiūros duomenų registravimui, peržiūrai ir administravimui. Projektas kuriamas naudojant modulinę architektūrą, dinaminę atmintį ir tekstinius duomenų failus.

---

## 📌 Projekto funkcionalumas

### 🔐 Log-In sistema  
**Atsakingas:** Nedas  
**Statusas:** DONE

- Vartotojų registracija (Sign Up)
- Prisijungimas (Log In)
- Du paskyrų tipai:
  - `USER`
  - `ADMIN`
- Prisijungimo duomenys saugomi tekstiniame faile `data/users.txt`
- Duomenys šifruojami naudojant paprastą +2 pagal abėcėlę šifravimo metodą
- Prisijungus pateikiamas sunumeruotas operacijų meniu

---

## ⚙️ Sistemos operacijos

1. **Automobilių registravimas**  
   **Atsakingas:** Kristijonas  
   - Valstybiniai numeriai  
   - Markė  
   - Spalva  
   - Kuro tipas  
   - Kategorija  

2. **Duomenų bazė su paieškos funkcija**  
   **Atsakingas:** Kristijonas  
   - Visų registruotų automobilių peržiūra  
   - Paieška pagal pasirinktus kriterijus  

3. **Duomenų bazė su filtravimo sistema**  
   **Atsakingas:** Liudas  
   - Filtravimas pagal techninės apžiūros galiojimą  
   - Papildomi filtrai (spalva, kategorija ir kt.)  

4. **Techninės apžiūros valdymas**  
   **Atsakingas:** Liudas  
   - Techninės apžiūros būsenos atnaujinimas  
   - Duomenų redagavimas  

5. **Admin panelė**  
   **Atsakingas:** Nedas  
   **Statusas:** DONE  
   - Visų vartotojų (USER) sąrašo peržiūra  
   - Vartotojų rolės keitimas (`USER ↔ ADMIN`)  

0. **Exit** – programos uždarymas  
**Atsakingas:** Nedas (DONE)

---

## 📊 Projekto pristatymai

- **Idėjos skaidrės:** Nedas (DONE)  
- **Galutinio projekto pristatymo skaidrės:** Liudas ir Kristijonas  

---

## 🖥️ Kompiliavimas ir paleidimas

### 🍎 macOS

**Kompiliavimas:**

gcc main.c login.c admin.c crypto.c -o project

**Paleidimas:**
./project

### 🪟 Windows

(Reikalingas įdiegtas MinGW / GCC)

**Kompiliavimas:**
gcc main.c login.c admin.c crypto.c -o project.exe

**Paleidimas:**
project.exe
arba
.\project.exe

---

##📚 Naudojamos technologijos
**Programavimo kalba:** C
**Kompiliatoriai:**
clang (macOS)
gcc (Windows / MinGW)
**Duomenų saugojimas:** tekstiniai .txt failai
**Architektūra:** modulinė (protokolų principu)
