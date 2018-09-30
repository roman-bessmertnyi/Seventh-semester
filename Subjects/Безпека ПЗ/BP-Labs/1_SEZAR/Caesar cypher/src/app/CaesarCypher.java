package app;

public class CaesarCypher {
	public static void main(String args[]) {
		String strIn;
		String strRussian = "אבגדהו¸זחטיךכלםמןנסעףפץצקרשüûת‎‏ÿ ";
		String strEnglish = "abcdefghijklmnopqrstuvwxyz ";
		String strUsed = strEnglish;
		char[] chUsed = strUsed.toCharArray();
		String strOut = "";
		strIn = "YMJEGTTPENXESTYEF FNQFGQJ"; // enter text here
		int encrypt = -1; // encrypt if 1 or decrypt if -1
		strIn = strIn.toLowerCase();
		int strLength = strIn.length();
		char chIn[] = strIn.toCharArray();
		int shift = 5; // shift

		System.out.println();
		System.out.println("Encrypted text is");
		for (int i = 0; i < strLength; i++) {
			int position = strUsed.indexOf(chIn[i]);
			position = (position+shift*encrypt)%strUsed.length();
			if (position < 0) position+=strUsed.length();
			strOut += chUsed[position];
		}
		strOut = strOut.toUpperCase();
		System.out.println(strOut);
	}
}
