nCols <- 3;
colSep <- 20;
colWidth <- 320;
rowSep <- 10;
colMargin <- 10;
rowMargin <- 10;

function Input(value) {
	try {
		if (isServer == false) {
			strtest = strtest2;
			return;
		}
	} catch (exception) {
		switch (value & 0xFFFF0000) {
			case 0x01000000: //SCANNER_OPEN
				break;
			case 0x01010000: //SCANNER_SCAN
				getconsttable()["entindex_scanned"] <- value & 0x0000FFFF;
				break;
			case 0x01FF0000: //SCANNER_CLOSE
				break;
			case 0x02000000: //SILENCER_OPEN
				break;
			case 0x02010000: //SILENCER_SILENCE
				getconsttable()["entindex_silenced"] <- value & 0x0000FFFF;
				break;
			case 0x02FF0000: //SILENCER_CLOSE
				break;
			case 0x03000000: //BIOCHEMIST_OPEN
				break;
			case 0x03010000: //BIOCHEMIST_HEAL
				getconsttable()["entindex_healed"] <- value & 0x0000FFFF;
				break;
			case 0x03020000: //BIOCHEMIST_KILL
				getconsttable()["entindex_killed"] <- value & 0x0000FFFF;
				break;
			case 0x03FF0000: //BIOCHEMIST_CLOSE
				break;
			case 0x04000000: //SHIELD_OPEN
				break;
			case 0x04010000: //SHIELD_GIVE_MECHA
				getconsttable()["entindex_mecha_given"] <- value & 0x0000FFFF;
				break;
			case 0x04FF0000: //SHIELD_CLOSE
				break;
			case 0x05000000: //INFECTOR_OPEN
				break;
			case 0x05010000: //INFECTOR_ABET
				getconsttable()["entindex_abeted"] <- value & 0x0000FFFF;
				break;
			case 0x05FF0000: //INFECTOR_CLOSE
				break;
			default:
				printl("Error value of SendInput():\t" + value);
				break;
		}
	}
}

function TrimString(text, font) {
	for (local i = text.len(); i > 4; i--) {
		if (self.GetTextWide(font, text.slice(0, i)) <= colWidth) {
			text = text.slice(0, i);
			break;
		}
	}
	return text;
}