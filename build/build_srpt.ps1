# Define usage function
function usage {
    @"
    Usage: build_srpt [option]
    Builds the executable server and client files for development

    -a          compiles both server and client files
    -c          compiles only the client file
    -s          compiles only the server file
"@
    exit 0
}

# Define compile_client function
function compile_client {
    Set-Location ..
    & g++ -o build\client client\client_main.cpp client\client.cpp common\message.cpp -lws2_32
}

# Define compile_server function
function compile_server {
    Set-Location ..
    & g++ -o build\server server\server_main.cpp server\server.cpp common\message.cpp -lws2_32
}

# Check if no arguments are provided
if ($args.Length -lt 1) {
    usage
    exit 1
}

# Check for help option
if ($args -contains "--help" -or $args -contains "-h") {
    usage
    exit 0
}

# Process options
foreach ($arg in $args) {
    switch ($arg) {
        "-a" {
            compile_client
            compile_server
            break
        }
        "-c" {
            compile_client
            break
        }
        "-s" {
            compile_server
            break
        }
        default {
            Write-Host "Unknown option: $arg"
            usage
            exit 1
        }
    }
}