use std::net::TcpStream;
use std::io::{self, Read, Write};
use std::str;

fn main() -> io::Result<()> {
    let mut stream = TcpStream::connect("127.0.0.1:12345")?;
    println!("Connected to the server!");

    let msg = "Hello, server!";
    stream.write_all(msg.as_bytes())?;
    let mut buffer = [0; 1024];
    let nbytes = stream.read(&mut buffer)?;
    let received_msg = str::from_utf8(&buffer[..nbytes]).unwrap();

    println!("Received echo: {}", received_msg);
    Ok(())
}
