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

import sky4s.guideuino.PacketSymbol;

//interface PacketSymbol {
//	public final static char PacketStart=12;
//	public final static char PacketEnd=13;
//}

public class TCPClient implements PacketSymbol {

	static String getCommand(ByteBuffer bytebuf) {
		int limit = bytebuf.limit();
		if (bytebuf.get(0) == PacketStart
				&& bytebuf.get(limit - 1) == PacketEnd) {
			int size = limit - 2;
			StringBuilder buf = new StringBuilder();
			for (int x = 0; x < size; x++) {
				buf.append((char) bytebuf.get(x + 1));
			}
			// System.out.println(buf.toString());
			return buf.toString();
		} else {
			return null;
		}

	}

	public static void main(String argv[]) throws Exception {

		SocketChannel channel = SocketChannel.open();
		channel.connect(new InetSocketAddress("192.168.56.101", 4567));
		while (!channel.finishConnect()) {
			// wait, or do something else...
			Thread.sleep(100);
		}

		ByteBuffer inbuf = ByteBuffer.allocate(256);
		ByteBuffer outbuf = ByteBuffer.allocate(256);

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
						String command = getCommand(inbuf);
						switch (command) {
						case "screencap":
							System.out.println(command);
							break;
							default:
								System.out.println("Unknow command!");
								break;
						}
						// int limit = inbuf.limit();
						// if (inbuf.get(0) == 12
						// && inbuf.get(inbuf.limit() - 1) == 13) {
						// int size = inbuf.limit() - 2;
						// StringBuilder buf = new StringBuilder();
						// for (int x = 0; x < size; x++) {
						// buf.append((char) inbuf.get(x + 1));
						// }
						// System.out.println(buf.toString());
						// } else {
						// System.out.println(inbuf.toString());
						// }
						// System.out.println("read: " + inbuf.get(0) + " "
						// + inbuf.get(1));
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
			Thread.sleep(100);
		}

	}
}