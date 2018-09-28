package app;

public class CaesarCypher {
	public static void main(String args[]) {
		String strIn;
		String strRussian = "àáâãäå¸æçèéêëìíîïğñòóôõö÷øùüûúışÿ ";
		char[] chRussian = strRussian.toCharArray();
		String strOut = "";
		strIn = "Ï×ÓÄÒÉÄÕÅ¨Ó×ÅÉ×Ä×Ó×ÄÉÖ×"; // enter text here
		int encrypt = -1; // encrypt if 1 or decrypt if -1
		strIn = strIn.toLowerCase();
		int strLength = strIn.length();
		char chIn[] = strIn.toCharArray();
		int shift = 5; // shift

		System.out.println();
		System.out.println("Encrypted text is");
		for (int i = 0; i < strLength; i++) {
			int position = strRussian.indexOf(chIn[i]);
			position = (position+shift*encrypt)%strRussian.length();
			if (position < 0) position+=strRussian.length();
			strOut += chRussian[position];
		}
		strOut = strOut.toUpperCase();
		System.out.println(strOut);
	}
}
