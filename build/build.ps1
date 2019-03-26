$PROJECT_DIR = $env:PROJECT_DIR
$BUILD_CONFIGURATION = $env:BUILD_CONFIGURATION

if (!$PROJECT_DIR) {
    $PROJECT_DIR = Get-Location
}

if (!$BUILD_CONFIGURATION) {
    $BUILD_CONFIGURATION = 'Debug'
}

$OUT_DIR="$PROJECT_DIR/bin/$BUILD_CONFIGURATION"
New-Item -ItemType Directory -Force -Path "$OUT_DIR" | Out-Null

$SOURCE = [array]@(Get-ChildItem $PROJECT_DIR/src/*.c)

Write-Host "Project folder:" $PROJECT_DIR
Write-Host "Build configuration:" $BUILD_CONFIGURATION
Write-Host "Building..."

$BUILD_CONFIGURATION = $BUILD_CONFIGURATION.ToUpper()

gcc -g -Wall -o "$OUT_DIR/bignumlib.exe" -D"$BUILD_CONFIGURATION" -D'WINDOWS' -I $PROJECT_DIR/include -I $PROJECT_DIR/src $SOURCE

Write-Host "Done."
