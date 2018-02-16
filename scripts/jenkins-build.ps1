Param(
[string]$compiler="msvc",
[string]$type="Debug",
[string]$oldtarget="rtype.exe")

function print_settings($compiler,$type)
{
  Write-Host "compiler: $compiler"
  Write-Host "type: $type"
}

function remove_old_build($oldtarget, $type)
{
    Remove-Item ./build-$type -Force -Recurse 2>&1 | out-null
    Remove-Item ./test-result -Force -Recurse 2>&1 | out-null
    Remove-Item ./bin/$type -Force -Recurse 2>&1 | out-null
    Remove-Item ./bin/*.dll -Force 2>&1 | out-null
    Remove-Item ./bin/$oldtarget -Force 2>&1 | out-null
}

function build($type)
{
    mkdir build-$type
    Set-Location build-$type
    $cmd = "-DCMAKE_BUILD_TYPE=$type"
    $localpath = Join-Path $env:VCPKG_ROOT '/scripts/buildsystems/vcpkg.cmake'
    $localpath = $localpath -replace "\\", "/"
    cmake -DCMAKE_TOOLCHAIN_FILE="$localpath" $cmd -DCORE_BUILD_TESTS=ON -G "Visual Studio 15 2017 Win64" ..
    if ($LASTEXITCODE -ne 0) {
        Write-Host "cmake generation failed"
        exit 127
    }
    cmake --build . --config $type -- /verbosity:minimal /maxcpucount:3
    if ($LASTEXITCODE -ne 0) {
        Write-Host "build fail."
        exit 127
    }
}

function run_xunit_impl($type)
{
   foreach ($file in get-ChildItem *-test.exe) {
    $var = $file.name
    Write-Output $var
    & ./$var --gtest_output="xml:$var-windows-$type-result.xml"
    }
}

function run_xunit($type)
{
    Set-Location ..
    Set-Location bin
    run_xunit_impl
    Set-Location ..
}

function run_ctest($type)
{
   Set-Location build-$type
   ctest --no-compress-output -T Test -C $type
   Set-Location ..
}

function publish_result($type)
{
    mkdir test-result
    Set-Location test-result
    mkdir ctest
    Set-Location ..
    Copy-Item bin/*.xml test-result/
    Copy-Item build-$type/Testing/*/*.xml test-result/ctest
}

function run($compiler, $type, $oldtarget) {
   remove_old_build $oldtarget $type
   build $type
   run_xunit $type
   run_ctest $type
   publish_result $type
}

print_settings $compiler $type
run $compiler $type $oldtarget

