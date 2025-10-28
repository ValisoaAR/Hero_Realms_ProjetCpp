# Script de compilation Hero Realms

Write-Host "===== Compilation Hero Realms =====" -ForegroundColor Cyan

# Créer les répertoires
$null = New-Item -ItemType Directory -Force -Path build

# Compiler toutes les sources
$sources = @(
    "src/Game/Cartes/Carte.cpp",
    "src/Game/Cartes/CarteData.cpp",
    "src/Game/Cartes/Action.cpp",
    "src/Game/Cartes/Champion.cpp",
    "src/Game/Cartes/Objet.cpp",
    "src/Game/Systeme/Capacite.cpp",
    "src/Game/Systeme/Effet.cpp",
    "src/Game/Systeme/Effet_data.cpp",
    "src/Game/Systeme/Faction.cpp",
    "src/Game/Systeme/Ressources.cpp",
    "src/Game/Zones/ZoneDeCarte.cpp",
    "src/Game/Zones/Marche.cpp",
    "src/Game/Zones/TablePartie.cpp",
    "src/Game/Core/Joueur.cpp",
    "src/Game/Core/GameController.cpp",
    "src/Game/Core/GameView.cpp",
    "src/Game/Utils/SimpleRng.cpp",
    "main.cpp"
)

$objects = @()
$success = $true

foreach ($src in $sources) {
    $objName = [System.IO.Path]::GetFileNameWithoutExtension($src) + ".o"
    $objPath = "build/$objName"
    $objects += $objPath
    
    Write-Host "Compiling $src..." -ForegroundColor Yellow
    g++ -std=c++17 -Iinclude -c $src -o $objPath 2>&1 | Out-Host
    
    if ($LASTEXITCODE -ne 0) {
        $success = $false
        Write-Host "ERROR compiling $src" -ForegroundColor Red
        break
    }
}

if ($success) {
    Write-Host "`nLinking..." -ForegroundColor Yellow
    g++ -std=c++17 -o build/hero.exe $objects
    
    if ($LASTEXITCODE -eq 0) {
        Write-Host "`n===== BUILD SUCCESS =====" -ForegroundColor Green
        Write-Host "Executable: build/hero.exe" -ForegroundColor Green
    } else {
        Write-Host "`nERROR during linking" -ForegroundColor Red
    }
} else {
    Write-Host "`n===== BUILD FAILED =====" -ForegroundColor Red
}
