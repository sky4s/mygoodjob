package tcp;

//public class TCPClient {
//
//}

import java.io.*;
import java.net.*;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.SocketChannel;
import java.util.Iterator;
import java.util.Set;

public class TCPClient {
	public static void main(String argv[]) throws Exception {

		SocketChannel channel = SocketChannel.open();
		channel.connect(new InetSocketAddress("192.168.56.101", 4567));
		while (!channel.finishConnect()) {
			// wait, or do something else...
			Thread.sleep(100);
		}

		ByteBuffer inbuf = ByteBuffer.allocate(2);
		ByteBuffer outbuf = ByteBuffer.allocate(2);

		Selector selector = Selector.open();
		channel.configureBlocking(false);
		channel.register(selector, SelectionKey.OP_READ | SelectionKey.OP_WRITE);
		short moveCount = 0;
		boolean readed = false;

		System.out.println("START:");
		while (true) {
			int readyChannels = selector.select();
			if (readyChannels == 0) {
				// System.out.println("continue");
				continue;
			}
			Set<SelectionKey> selectedKeys = selector.selectedKeys();
			Iterator<SelectionKey> keyIterator = selectedKeys.iterator();
			while (keyIterator.hasNext()) {
				SelectionKey key = keyIterator.next();
				if (key.isAcceptable()) {
					// a connection was accepted by a ServerSocketChannel.
					System.out.println("accept");

				} else if (key.isConnectable()) {
					// a connection was established with a remote server.
					System.out.println("connect");
				} else if (key.isReadable()) {
					// a channel is ready for reading

					if (channel.read(inbuf) != -1) {
						inbuf.flip();
						System.out.println("read: " + inbuf.get(0) + " "
								+ inbuf.get(1));
						inbuf.clear();
						readed = true;
					}

				} else if (key.isWritable() && readed) {
					// a channel is ready for writing

					outbuf.clear();
					outbuf.putShort(moveCount++);
					outbuf.flip();

					int writelength = channel.write(outbuf);
					System.out.println("write: " + moveCount + "/"
							+ (writelength = channel.write(outbuf)));
					
					readed = false;
				}
				keyIterator.remove();
			}
//			Thread.sleep(100);
		}

	}
}