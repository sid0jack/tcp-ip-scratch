use std::net::{TcpListener, TcpStream};
use std::io::{Read, Write};
use std::str;

fn handle_client(mut stream: TcpStream) -> std::io::Result<()> {
    println!("Connection established with {}", stream.peer_addr()?);
    let mut buffer = [0; 1024];

    // Read data from the stream
    let nbytes = stream.read(&mut buffer)?;
    let msg = str::from_utf8(&buffer[..nbytes]).unwrap();
    println!("Received: {}", msg);

    // Echo back the received message
    stream.write_all(msg.as_bytes())?;
    Ok(())
}

fn main() -> std::io::Result<()> {
    let listener = TcpListener::bind("0.0.0.0:12345")?;
    println!("Server listening on port 12345");

    for stream in listener.incoming() {
        match stream {
            Ok(stream) => {
                if let Err(e) = handle_client(stream) {
                    eprintln!("Error handling client: {}", e);
                }
            }
            Err(e) => {
                eprintln!("Connection failed: {}", e);
            }
        }
    }
    Ok(())
}
