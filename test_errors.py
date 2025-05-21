import subprocess
import os

# Dossier contenant les fichiers .cub
cub_dir = "assets/map/errors"
cub_files = [f for f in os.listdir(cub_dir) if not f.startswith(".")]

# Nom de ton exécutable (modifie si nécessaire)
EXECUTABLE = "./cub3D"

# Tester chaque fichier
print("=== Tests d'erreurs cub3D ===\n")
for file in cub_files:
    path = os.path.join(cub_dir, file)
    try:
        result = subprocess.run(
            [EXECUTABLE, path],
            capture_output=True,
            text=True,
            timeout=5
        )
        
        error_detected = (
            result.returncode != 0 or
            "Error" in result.stdout or
            "Error" in result.stderr
        )

        if error_detected:
            print(f"✅ {file} → erreur bien détectée")
        else:
            print(f"❌ {file} → aucune erreur détectée (ATTENDUE)")
            print(f"   ↳ stdout: {result.stdout.strip()}")
            print(f"   ↳ stderr: {result.stderr.strip()}")

    except subprocess.TimeoutExpired:
        print(f"⏱️ {file} → Temps d'exécution dépassé (probable blocage)")

    except Exception as e:
        print(f"⚠️ {file} → Erreur lors du test : {e}")

print("\n=== Fin des tests ===")
