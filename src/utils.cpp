/*

  This file is a part of BoGoEngine project.

  Copyright (C) 2012 Dương H. Nguyễn <cmpitg@gmail.com>
  Copyright (C) 2012 Duong Quang Ha <contact@haqduong.net>

  BoGoEngine is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  BoGoEngine is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with BoGoEngine.  If not, see <http://www.gnu.org/licenses/>.

*/

// The code needs to be extremely polished

#include "utils.hpp"
#include <iostream>

namespace BoGo {

    using namespace std;
    using namespace Glib;

#ifdef _
#undef _
#endif
#define _(x) (ustring ("") + x)

#ifdef __
#undef __
#endif
#define __(x) (ustring ("") + x).c_str ()

    bool containsP (ustring str, ustring needle, bool ignoreCase) {
        if (ignoreCase) {
            str = str.lowercase ();
            needle = needle.lowercase ();
        }
        return str.find (needle) != ustring::npos;
    }

    bool containsP (string str, ustring needle, bool ignoreCase) {
        return containsP (_(str), needle, ignoreCase);
    }

    bool containsP (const gchar *str, ustring needle, bool ignoreCase) {
        return containsP (_(str), needle, ignoreCase);
    }

    bool containsP (ustring str, string needle, bool ignoreCase) {
        return containsP (str, _(needle), ignoreCase);
    }

    bool containsP (string str, string needle, bool ignoreCase) {
        return containsP (_(str), _(needle), ignoreCase);
    }

    bool containsP (const gchar *str, string needle, bool ignoreCase) {
        return containsP (_(str), _(needle), ignoreCase);
    }

    bool containsP (ustring str, guint needle, bool ignoreCase) {
        return containsP (str, _(needle), ignoreCase);
    }

    bool containsP (string str, guint needle, bool ignoreCase) {
        return containsP (_(str), _(needle), ignoreCase);
    }

    bool containsP (const gchar *str, guint needle, bool ignoreCase) {
        return containsP (_(str), _(needle), ignoreCase);
    }

    bool containsP (ustring str, const gchar *needle, bool ignoreCase) {
        return containsP (str, _(needle), ignoreCase);
    }

    bool containsP (string str, const gchar *needle, bool ignoreCase) {
        return containsP (_(str), _(needle), ignoreCase);
    }

    bool containsP (const gchar *str, const gchar *needle, bool ignoreCase) {
        return containsP (_(str), _(needle), ignoreCase);
    }

    long find (ustring s, ustringArrayT a) {
        for (long i = 0; i < a.size (); i++)
            if (a[i] == s)
                return i;
        return -1;
    }

    bool containsP (ustringArrayT a, ustring s) {
        return find (s, a) != -1;
    }

    ustring removeMarksFromLastWord (ustring text) {
        _size_t_ pos = getLastPseudoWordPos (text);

        if (pos == ustring::npos)
            return text;

        ustring word = text.substr (pos);
        return text.replace (pos, text.size () - pos,
                             removeAllMarksFromWord (word));
    }

    ustring removeAllMarksFromWord (ustring word) {
        ustring res = "";
        for (_size_t_ i = 0; i < word.length (); i++)
            res += removeMarkFromChar (word[i]);
        return res;
    }

    ustring removeAllMarksFromWord (string word) {
        return removeAllMarksFromWord (_(word));
    }

    ustring removeAllMarksFromWord (const gchar *word) {
        return removeAllMarksFromWord (_(word));
    }

    ustring removeMarkFromWord (ustring word, _size_t_ pos) {
        ustring ch = _(word[pos]);
        return word.replace (pos, 1, removeMarkFromChar (ch));
    }

    ustring removeMarkFromWord (string word, _size_t_ pos) {
        return removeMarkFromWord (_(word), pos);
    }

    ustring removeMarkFromWord (const gchar *word, _size_t_ pos) {
        return removeMarkFromWord (_(word), pos);
    }

    ustring removeAccentFromWord (ustring word) {
        ustring res;
        for (_size_t_ i = 0; i < word.length (); i++)
            res += removeAccentFromChar (word[i]);
        return res;
    }

    ustring removeAccentFromWord (string word) {
        return removeAccentFromWord (_(word));
    }

    ustring removeAccentFromWord (const gchar *word) {
        return removeAccentFromWord (_(word));
    }

    InputMethodT makeStandardIM (guint imID) {
        if (imID < NUMBER_OF_IMS)
            return makeIMFromString (IMs[imID]);
        return InputMethodT();
    }

    InputMethodT standardizeIM (InputMethodT im) {
        // Add * when necessary
        for (guint i = 0; i < im.size (); i++)
            if (im[i].length () < 3)
                im[i] = _(im[i][0]) + _("*") + _(im[i][1]);
        return im;
    }

    InputMethodT makeIMFromString (ustring imStr) {
        InputMethodT im;
        _size_t_ eolPos;
        ustring transPortion;
        ustring specialToken = (imStr.find (" -> ") != ustring::npos) ?
            _(" -> ") : _(" ");

        while (imStr.length () > 1) {
            eolPos = imStr.find ("\n");
            transPortion = imStr.substr (0, eolPos);
            imStr = imStr.replace (0, eolPos + 1, "");
            im = addTransform
                (im, transPortion.replace (1, specialToken.length (), ""));
        }
        return standardizeIM (im);
    }

    InputMethodT makeIMFromString (const gchar * imStr) {
        return makeIMFromString (_(imStr));
    }

    InputMethodT makeIMFromString (string imStr) {
        return makeIMFromString (_(imStr));
    }

    InputMethodT makeIM (guint count, ...) {
        const gchar *trans;
        InputMethodT im;
        va_list transList;
        va_start (transList, count);

        for (guint i = 0; i < count; i++) {
            trans = va_arg (transList, const gchar *);
            im = addTransform (im, _(trans));
        }

        va_end (transList);
        return im;
    }

    InputMethodT addTransform (InputMethodT im, ustring trans) {
        im.push_back (trans);
        return im;
    }

    InputMethodT addTransform (InputMethodT im, const gchar *trans) {
        return addTransform (im, _(trans));
    }

    ustring toString (InputMethodT im) {
        ustring res;
        for (guint i = 0; i < im.size (); i++)
            res += _(im[i][0]) + " -> " + _(im[i][1]) + _(im[i][2]) + "\n";
        return res;
    }

    ustring addMarkToChar (ustring ch, Marks mark) {
        bool isUp = isUpperCase (ch);
        _size_t_ accent = getAccentFromChar (ch);

        _size_t_ pos = LettersMayChangeMarks.find
            (removeAccentFromChar (ch).lowercase ());
        if (pos != ustring::npos) {
            ch = addAccentToChar
                (_(LettersWithMarks
                   [mark * LettersWithoutMarks.length () + pos]),
                 accent);
            if (isUp)
                ch = ch.uppercase ();
        }
        return ch;
    }

    ustring addMarkToChar (string ch, Marks mark) {
        return addMarkToChar (_(ch), mark);
    }

    ustring addMarkToChar (const gchar *ch, Marks mark) {
        return addMarkToChar (_(ch), mark);
    }

    ustring addMarkToChar (guint ch, Marks mark) {
        return addMarkToChar (_(ch), mark);
    }

    ustring lastChar (ustring s) {
        return (s.length () > 0) ? _(s[s.length () - 1]) : _("");
    }

    ustring lastChar (string s) {
        return lastChar (_(s));
    }

    ustring lastChar (const gchar *s) {
        return lastChar (_(s));
    }

    ustring firstChar (ustring s) {
        return (s.length () > 0) ? _(s[0]) : _("");
    }

    ustring firstChar (string s) {
        return firstChar (_(s));
    }

    ustring firstChar (const gchar *s) {
        return firstChar (_(s));
    }

    bool analyseWordCheckSpecialConsonants (ustringArrayT word,
                                            ustring consonant) {
        return lastChar (word[0]).lowercase () == _(consonant[0]) &&
            firstChar (word[1]).lowercase () == _(consonant[1]);
    }

    bool analyseWordCheckSpecialConsonants (ustringArrayT word,
                                            const gchar *consonant) {
        return analyseWordCheckSpecialConsonants (word, _(consonant));
    }

    ustringArrayT analyseWord (ustring str) {
        typedef bool (*_TrivialPointerToFunctions_) (ustring);

        ustringArrayT res(3);
        _TrivialPointerToFunctions_ testFuncs[3] =
            { isConsonant, isVowel, isConsonant };

        // First part: Consonant 1
        // Second part: Vowel
        // Third part: Consonant 2

        for (int part = 2; part >= 0; part --) {
            res[part] = "";
            while (str.length () > 0 &&
                   testFuncs[part] (_(str[str.length () - 1]))){
                res[part] = _(str[str.length () -1]) + res[part];
                str.replace (str.length () -1, 1, "");
            }
        }

        // push the remaining part into res[0]
        res[0] = str + res[0];

        // Special case: "qu" and "gi" are considered consonants
        if (analyseWordCheckSpecialConsonants (res, "qu") ||
            analyseWordCheckSpecialConsonants (res, "gi")) {
            res[0] += _(res[1][0]);
            res[1] = res[1].replace (0, 1, "");
        }

        return res;
    }

    ustringArrayT analyseWord (string str) {
        return analyseWord (_(str));
    }

    ustringArrayT analyseWord (const gchar *str) {
        return analyseWord (_(str));
    }

    bool isVowel (ustring ch) {
        return PlainVowels.find (toPlainLetter (ch.lowercase ()))
            != ustring::npos;
    }

    bool isVowel (const gchar *ch) {
        return isVowel (_(ch));
    }

    bool isVowel (string ch) {
        return isVowel (_(ch));
    }

    bool isVowel (guint ch) {
        return isVowel (_(ch));
    }

    bool isConsonant (ustring ch) {
        // Only vowel is special, so non-alphabet characters are
        // counted as consonants
        return !isVowel (ch);
    }

    bool isConsonant (const gchar *ch) {
        return isConsonant (_(ch));
    }

    bool isConsonant (string ch) {
        return isConsonant (_(ch));
    }

    bool isConsonant (guint ch) {
        return isConsonant (_(ch));
    }

    _size_t_ getMarkedCharPos (ustring ch) {
        _size_t_ mark =
            LettersWithMarks.find (removeAccentFromChar (ch.lowercase ()));

        if (mark != ustring::npos)
            mark %= LettersWithoutMarks.length ();

        return mark;
    }

    _size_t_ getMarkedCharPos (string ch) {
        return getMarkedCharPos (_(ch));
    }

    _size_t_ getMarkedCharPos (const gchar *ch) {
        return getMarkedCharPos (_(ch));
    }

    _size_t_ getMarkedCharPos (guint ch) {
        return getMarkedCharPos (_(ch));
    }

    ustring removeMarkFromChar (ustring ch) {
        bool isUp = isUpperCase (ch);

        _size_t_ pos = getMarkedCharPos (ch);
        _size_t_ accent = getAccentFromChar (ch);

        if (pos != ustring::npos)
            ch = addAccentToChar (_(LettersWithoutMarks[pos]), accent);

        if (isUp)
            ch = ch.uppercase ();
        return ch;
    }

    ustring removeMarkFromChar (string ch) {
        return removeMarkFromChar (_(ch));
    }

    ustring removeMarkFromChar (const gchar *ch) {
        return removeMarkFromChar (_(ch));
    }

    ustring removeMarkFromChar (guint ch) {
        return removeMarkFromChar (_(ch));
    }

    Accents getAccentFromChar (ustring ch) {
        _size_t_ accent = VowelsWithAccents.find (ch.lowercase ());

        if (accent != ustring::npos)
            accent %= NUMBER_OF_ACCENTS;
        else
            accent = NO_ACCENT;

        return accent;
    }

    Accents getAccentFromChar (string ch) {
        return getAccentFromChar (_(ch));
    }

    Accents getAccentFromChar (const gchar *ch) {
        return getAccentFromChar (_(ch));
    }

    Accents getAccentFromChar (guint ch) {
        return getAccentFromChar (_(ch));
    }

    ustring toPlainLetter (ustring ch) {
        ch = removeAccentFromChar (removeMarkFromChar (ch));
        return ch;
    }

    ustring toPlainLetter (const gchar *ch) {
        return toPlainLetter (_(ch));
    }

    ustring toPlainLetter (string ch) {
        return toPlainLetter (_(ch));
    }

    ustring toPlainLetter (guint ch) {
        return toPlainLetter (_(ch));
    }

    ustring addAccentToChar (ustring ch, Accents accent) {
        bool isUp = isUpperCase (ch);
        ch = ch.lowercase ();

        _size_t_ pos = Vowels.find (ch);
        if (pos != ustring::npos)
            ch = _(VowelsWithAccents[pos * NUMBER_OF_ACCENTS + accent]);

        if (isUp)
            ch = ch.uppercase ();
        return ch;
    }

    ustring addAccentToChar (const gchar *ch, Accents accent) {
        return addAccentToChar (_(ch), accent);
    }

    ustring addAccentToChar (guint ch, Accents accent) {
        return addAccentToChar (_(ch), accent);
    }

    ustring addAccentToChar (string ch, Accents accent) {
        return addAccentToChar (_(ch), accent);
    }

    _size_t_ getVowelPos (ustring ch) {
        _size_t_ pos = VowelsWithAccents.find (ch.lowercase ());
        if (pos != ustring::npos)
            pos /= NUMBER_OF_ACCENTS;
        else if (Vowels.find (ch.lowercase ()) != pos)
            pos = Vowels.find (ch.lowercase ());
        return pos;
    }

    _size_t_ getVowelPos (const gchar *ch) {
        return getVowelPos (_(ch));
    }

    _size_t_ getVowelPos (string ch) {
        return getVowelPos (_(ch));
    }

    _size_t_ getVowelPos (guint ch) {
        return getVowelPos (_(ch));
    }

    ustring removeAccentFromChar (ustring ch) {
        bool isUp = isUpperCase (ch);
        ch = ch.lowercase ();

        _size_t_ posVowel = getVowelPos (ch);
        if (posVowel != ustring::npos)
            ch = _(Vowels[posVowel]);

        if (isUp)
            ch = ch.uppercase ();
        return ch;
    }

    ustring removeAccentFromChar (const gchar *ch) {
        return removeAccentFromChar (_(ch));
    }

    ustring removeAccentFromChar (string ch) {
        return removeAccentFromChar (_(ch));
    }

    ustring removeAccentFromChar (guint ch) {
        return removeAccentFromChar (_(ch));
    }

    bool isLetter (ustring ch) {
        return
            LowerCaseLetters.find (toPlainLetter (ch).lowercase ())
            != ustring::npos;
    }

    bool isLetter (string ch) {
        return isLetter (_(ch));
    }

    bool isLetter (const gchar *ch) {
        return isLetter (_(ch));
    }

    bool isLetter (guint ch) {
        return isLetter (_(ch));
    }

    bool isWordBreak (ustring ch, guint BackspaceChar) {
        // A char is a word-break if and only if tt's a non-letter
        // character and not a Backspace.
        return !isLetter (ch.lowercase ()) && ch != _(BackspaceChar);
    }

    bool isWordBreak (const gchar *ch, guint BackspaceChar) {
        return isWordBreak (_(ch), BackspaceChar);
    }

    bool isWordBreak (string ch, guint BackspaceChar) {
        return isWordBreak (_(ch), BackspaceChar);
    }

    bool isWordBreak (guint ch, guint BackspaceChar) {
        return isWordBreak (_(ch), BackspaceChar);
    }

    bool isUpperCase (ustring ch) {
        return ch.uppercase () == ch;
    }

    bool isUpperCase (string ch) {
        return isUpperCase (_(ch));
    }

    bool isUpperCase (const gchar *ch) {
        return isUpperCase (_(ch));
    }

    bool isUpperCase (guint ch) {
        return isUpperCase (_(ch));
    }

    bool isLowerCase (ustring ch) {
        return !isUpperCase (ch);
    }

    bool isLowerCase (string ch) {
        return isLowerCase (_(ch));
    }

    bool isLowerCase (const gchar *ch) {
        return isLowerCase (_(ch));
    }

    bool isLowerCase (guint ch) {
        return isLowerCase (_(ch));
    }

    ustring toRawText (ustring text) {
        return removeAllMarksFromWord (removeAccentFromWord (text)).lowercase();
    }

    ustring toRawText (string text) {
        return toRawText (_(text));
    }

    ustring toRawText (const gchar *text) {
        return toRawText (_(text));
    }

    ustring toEnglishText (ustring str) {
        return removeAllMarksFromWord (removeAccentFromWord (str));
    }

    ustring removeAccentFromLastWord (ustring str) {
        ustringArrayT comp = analyseWord (str);
        if (comp[2].size () > 2)
            return str;
        comp[1] = removeAccentFromWord (comp[1]);
        return comp[0] + comp[1] + comp[2];
    }

    _size_t_ findSpecialVowel (ustring text) {
        for (_size_t_ pos = 0; pos < text.size (); pos++) {
            if (containsP (SpecialVowels,
                           toRawText (_(text[pos]))))
                return pos;
        }
        return ustring::npos;
    }

    _size_t_ findSpecialVowel (string text) {
        return findSpecialVowel (_(text));
    }

    _size_t_ findSpecialVowel (const gchar *text) {
        return findSpecialVowel (_(text));
    }

    ustring addAccentToWord (ustring word, Accents accent) {
        // // Case: removing accent
        // if (accent == NO_ACCENT)
        //     return removeAccentFromWord (word);

        // Analyzing the word into 3 components
        // comp[0] = consonantPiece #1
        // comp[1] = vowelPiece
        // comp[2] = consonantPiece #2
        ustringArrayT comp = analyseWord (word);
        comp[1] = removeAccentFromWord (comp[1]);
        ustring vowelPiece = comp[1];
        ustring consonantPiece = comp[2];
        ustring newChar;

        // Case: no vowels
        if (vowelPiece.size () == 0)
            return word;

        // Case #1: vowelPiece contains special vowel ("ăâơê")
        _size_t_ posToPlaceAccent = findSpecialVowel (vowelPiece);
        if (posToPlaceAccent != ustring::npos) {
            // Do nothing, the position is right
        }

        // Case #2: consonantPiece exists
        else if (consonantPiece.size () > 0)
            posToPlaceAccent = vowelPiece.size () - 1;

        // Case #3: vowelPiece contains 3 letters
        else if (vowelPiece.size () == 3)
            posToPlaceAccent = 1;

        // Otherwise
        else
            posToPlaceAccent = 0;

        return comp[0] +
            vowelPiece.replace (posToPlaceAccent, 1,
                                addAccentToChar (
                                    vowelPiece[posToPlaceAccent],
                                    accent)) +
            consonantPiece;
    }

    ustring addAccentToWord (string word, Accents accent) {
        return addAccentToWord (_(word), accent);
    }

    ustring addAccentToWord (const gchar *word, Accents accent) {
        return addAccentToWord (_(word), accent);
    }

    bool endsWith (ustring text, ustring pattern) {
        // Ignore case
        _size_t_ pos = text.lowercase ().rfind (pattern.lowercase ());
        return pos != ustring::npos && (text.size () - pos == pattern.size ());
    }

    bool hasValidEndingConsonantsP (ustring word) {
        if (word.size () == 0 || isVowel (lastChar (word)))
            return true;

        for (guint i = 0; i < NUMBER_OF_VALID_ENDING_CONSONANTS; i++)
            if (endsWith (word, ValidEndingConsonants[i]))
                return true;
        return false;
    }

    _size_t_ getLastPseudoWordPos (ustring text) {
        // Get the position of the beginning of the last word in a
        // text by consecutively finding: longest consonant piece,
        // longest vowel piece, and check for special cases.

        _size_t_ result = text.size () - 1;
        while (result > 0 && isConsonant (text[result]))
            result--;

        // Case: all letters are consonants
        if (result == 0 && isConsonant (text[0]))
            return ustring::npos;

        // Case: invalid ending consonants
        if (!hasValidEndingConsonantsP (text.substr (result + 1)));

        while (result > 0 && isVowel (text[result]))
            result--;

        // Case: all consonants
        if (result == 0 && isVowel (text[0]))
            return 0;

        result++;

        // Special cases: "qu" and "gi"
        if (result > 0) {
            ustring maybeSpecial =
                (_(text[result - 1]) + _(text[result])).lowercase ();
            if (maybeSpecial == "qu" || maybeSpecial == "gi")
                return (result + 1) >= text.size () ?
                    ustring::npos : (result + 1);
        }

        return result;
    }

    _size_t_ getLastPseudoWordPos (string text) {
        return getLastPseudoWordPos (_(text));
    }

    _size_t_ getLastPseudoWordPos (const gchar *text) {
        return getLastPseudoWordPos (_(text));
    }

    ustring addAccentToText (ustring text, Accents accent) {
        _size_t_ pos = getLastPseudoWordPos (text);

        // Case: no word inside text
        if (pos == ustring::npos)
            return text;

        ustring firstPart = text.substr (0, pos);
        ustring lastWord = text.substr (pos);

        // cerr << " >> " << __(firstPart) << " ++ " << __(lastWord) << endl
        //      << hasValidEndingConsonantsP (lastWord) << endl
        //      << __(addAccentToWord (lastWord, accent)) << endl;

        if (hasValidEndingConsonantsP (lastWord))
            return firstPart + addAccentToWord (lastWord, accent);
        else
            return text;
    }

    ustring addAccentToText (string text, Accents accent) {
        return addAccentToText (_(text), accent);
    }

    ustring addAccentToText (const gchar *text, Accents accent) {
        return addAccentToText (_(text), accent);
    }

    ustring addMarkToWord (ustring word, Marks mark, gchar letter) {
        if (mark == NO_MARK)
            return removeAllMarksFromWord (word);

        letter = _(letter).lowercase ()[0];
        _size_t_ pos = ustring::npos;
        ustring lowCaseWord = removeAccentFromWord (word).lowercase ();

        // 1. Find the last position of the letter corresponding
        // to the mark
        if (letter == '*') {
            bool found = false;
            for (_size_t_ i = word.size () - 1; i != 0; i--) {
                if (canAddMarkToLetterP (_(lowCaseWord[i]), mark)) {
                    pos = i;
                    found = true;
                    break;
                }
            }
            if (!found) {
                if (canAddMarkToLetterP (_(lowCaseWord[0]), mark))
                    pos = 0;
                else
                    pos = ustring::npos;
            }
        }
        else {
            pos = lowCaseWord.find (_(letter));
            if (letter == 'u' &&
                pos < word.size () - 1 &&
                (lowCaseWord[pos + 1] == 'u' ||
                 lowCaseWord[pos + 1] == 'o'))
                pos++;
        }

        // cerr << "Word: " << __(word) << " -> "
        //      << pos << endl;

        // 1'. In case there is no letter to add mark to
        if (pos == ustring::npos)
            return word;

        // Special case: "qu"
        bool quCase =
            ((pos > 0 && lowCaseWord[pos] == 'u' &&
              lowCaseWord[pos - 1] == 'q') ||
             (pos > 1 && lowCaseWord[pos - 1] == 'u' &&
              lowCaseWord[pos - 2] == 'q'));

        // 2. Special case: "ưu" and "ươ"
        if (!quCase && pos >= 1 && mark == HORN) {
            ustring maybeSpecial =
                _(lowCaseWord[pos - 1]) + _(lowCaseWord[pos]);
            if (maybeSpecial == "uu")
                return word.replace (pos - 1, 1,
                                     addMarkToChar (word[pos - 1], HORN));
            if (maybeSpecial == "uo")
                return word.replace (pos - 1, 2,
                                     addMarkToChar (word[pos - 1], HORN) +
                                     addMarkToChar (word[pos], HORN));
        }

        // 2'. Special case: "au", "ao", "ua", and "oa"
        if (!quCase && (mark == BREVE || mark == HORN)) {
            ustring maybeSpecial1 = "";
            ustring maybeSpecial2 = "";
            if (pos > 0)
                maybeSpecial1 = _(lowCaseWord[pos - 1]) + _(lowCaseWord[pos]);
            if (pos < word.size () - 1)
                maybeSpecial2 = _(lowCaseWord[pos]) + _(lowCaseWord[pos + 1]);

            // cerr << "Word: " << __(word) << " -> "
            //      << __(maybeSpecial1) << " -> "
            //      << __(maybeSpecial2) << endl;

            if (maybeSpecial1 == "au" || maybeSpecial1 == "ao" ||
                maybeSpecial2 == "au" || maybeSpecial2 == "ao" ||
                ((maybeSpecial1 == "ua" || maybeSpecial2 == "ua") &&
                 mark != HORN) ||
                ((maybeSpecial1 == "oa" || maybeSpecial2 == "oa") &&
                 mark != BREVE))
                return word;
        }

        // 2''. Add mark the char, care not about the case since
        // addMarkToChar has taken care of that
        ustring newLetter = addMarkToChar (word[pos], mark);
        return word.replace (pos, 1, newLetter);
    }

    ustring addMarkToWord (string word, Marks mark, gchar letter) {
        return addMarkToWord (_(word), mark, letter);
    }

    ustring addMarkToWord (const gchar *word, Marks mark, gchar letter) {
        return addMarkToWord (_(word), mark, letter);
    }

    ustring addMarkToText (ustring text, Marks mark, gchar letter) {
        // mark == BAR is the special case
        if (mark == BAR || hasValidEndingConsonantsP (text))
            return addMarkToWord (text, mark, letter);
        else
            return text;
    }

    bool canAddMarkToLetterP (ustring letter, Marks mark) {
        return containsP (ValidLettersToMark[mark],
                          toPlainLetter (letter).lowercase ());
    }

    bool canAddMarkToLetterP (const gchar *letter, Marks mark) {
        return canAddMarkToLetterP (_(letter), mark);
    }

    bool canAddMarkToWordP (ustring word, Marks mark) {
        bool result = false;

        for (int i = 0; i < word.length (); i ++) {
            result = result || canAddMarkToLetterP (_(word[i]), mark);
        }

        return result;
    }

    ustring getTransformResult (ustring key_trans) {
        ustring trans = key_trans.erase (0, 1);
        while (trans[0] == ' ' ) {
            trans.erase(0, 1);
        }
        return trans;
    }

    ustringArrayT findTransform (ustring ch, InputMethodT im) {
        ustringArrayT trans;
        for (guint i = 0; i < im.size(); i++) {
            ustring tr = im[i];
            if (ch == _(tr[0])) {
                trans.push_back (tr);
            }
        }
        return trans;
    }

    ustringArrayT refineTransform (ustringArrayT oldTransform, ustring word) {
        ustringArrayT newTransform;

        for (guint i = 0; i < oldTransform.size(); i++) {
            const gchar *trans = oldTransform[i].c_str ();
            TransformTypeT tmpMarkOrAccent = getTransformType (trans[2]);
            TransformT tmpTrans = getTransform (trans[2]);

            if (tmpMarkOrAccent == TRANSFORM_MARK) {
                if (canAddMarkToWordP (word, tmpTrans)) {
                    newTransform.push_back (oldTransform[i]);
                }
            }
            else {
                newTransform.push_back (oldTransform[i]);
            }
        }

        return newTransform;
    }

    ustring addChar (ustring str, ustring ch) {
        return str + ch;
    }

    Accents getAccentFromWord (ustring word) {
        for (_size_t_ i = 0; i < word.size (); i++) {
            Accents c = getAccentFromChar (__(word[i]));
            if (c != NO_ACCENT)
                return c;
        }
        return NO_ACCENT;
    }

    TransformTypeT getTransformType (const gchar transChar) {
        switch (transChar) {
        case '^':
        case '+':
        case 'v':
        case '-':
            return TRANSFORM_MARK;
        default:
            return TRANSFORM_ACCENT;
        }
    }

    TransformT getTransform (const gchar transChar) {
        switch (transChar) {
        case '^':
            return HAT;
        case '+':
            return HORN;
        case 'v':
            return BREVE;
        case '-':
            return BAR;
        case '\\':
            return GRAVE;
        case '/':
            return ACUTE;
        case '?':
            return HOOK;
        case '~':
            return TILDE;
        case '.':
            return DOT;
        case '_':
            return NO_ACCENT;
        }
        return INVALID_TRANSFORM;
    }


#undef _
#undef __
}
