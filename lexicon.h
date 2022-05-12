#ifndef _lexicon_h
#define _lexicon_h
#include <QFile>
#include <iterator>
#include <set>
#include <string>

class Lexicon {
public:

    Lexicon();
    Lexicon(const std::string& filename);
    Lexicon(QFile &qFile);
    virtual ~Lexicon();
    bool add(const std::string& word);
    void addWordsFromFile(const std::string& filename);
    void clear();
    bool contains(const std::string& word) const;

    /*
     * Method: containsPrefix
     * Usage: if (lex.containsPrefix(prefix)) ...
     * ------------------------------------------
     * Returns true if any words in the lexicon begin with <code>prefix</code>.
     * Like <code>containsWord</code>, this method ignores the case of letters
     * so that "MO" is a prefix of "monkey" or "Monday".
     * The empty string is a prefix of every string, so this method returns
     * true when passed the empty string.
     */
    bool containsPrefix(const std::string& prefix) const;
    bool equals(const Lexicon& lex2) const;
    bool isEmpty() const;
    void mapAll(void (*fn)(std::string)) const;
    void mapAll(void (*fn)(const std::string&)) const;
    template <typename FunctorType>
    void mapAll(FunctorType fn) const;
    bool remove(const std::string& word);
    /*
     * Method: removePrefix
     * Usage: lex.removePrefix(prefix);
     * ---------------------
     * Removes all words from the lexicon that begin with the given prefix.
     * Returns true if the prefix was previously contained in the lexicon;
     * in other words, if any words were removed.
     * If the empty string is passed, since all words begin with the empty
     * string, all words will be removed and this method will
     * return true if the lexicon was non-empty prior to the call.
     */
    bool removePrefix(const std::string& prefix);
    int size() const;
    std::set<std::string> toStlSet() const;
private:
    struct TrieNode {
    public:
        TrieNode() {
            m_isWord = false;
            for (int i = 0; i < 26; i++) {
                m_children[i] = nullptr;
            }
        }

        // pre: letter is between 'a' and 'z' in lowercase
        inline TrieNode*& child(char letter) {
            return m_children[letter - 'a'];
        }

        inline int childCount() {
            int count = 0;
            for (int i = 0; i < 26; i++) {
                if (m_children[i] != nullptr) {
                    count++;
                }
            }
            return count;
        }

        inline bool isLeaf() {
            for (int i = 0; i < 26; i++) {
                if (m_children[i] != nullptr) {
                    return false;
                }
            }
            return true;
        }

        inline bool isWord() {
            return m_isWord;
        }

        inline void setWord(bool value) {
            m_isWord = value;
        }

    private:
        bool m_isWord;
        TrieNode* m_children[26];   // 0=a, 1=b, 2=c, ..., 25=z
    };

    /*
     * private helper functions, including
     * recursive helpers to implement public add/contains/remove
     */
    bool addHelper(TrieNode*& node, const std::string& word, const std::string& originalWord);
    bool containsHelper(TrieNode* node, const std::string& word, bool isPrefix) const;
    void deepCopy(const Lexicon& src);
    void deleteTree(TrieNode* node);
    bool removeHelper(TrieNode*& node, const std::string& word, const std::string& originalWord, bool isPrefix);
    void removeSubtreeHelper(TrieNode*& node, const std::string& originalWord);

    /* instance variables */
    TrieNode* m_root;
    int m_size;
    std::set<std::string> m_allWords;   // secondary structure of all words for foreach;
                                   // basically a cop-out so I can loop over words

public:

    Lexicon(const Lexicon& src);
    Lexicon& operator =(const Lexicon& src);

    /* Iterator */
    using const_iterator = std::set<std::string>::const_iterator;
    const_iterator begin() const { return m_allWords.begin(); }
    const_iterator end() const { return m_allWords.end(); }
    const_iterator cbegin() const { return m_allWords.cbegin(); }
    const_iterator cend() const { return m_allWords.cend(); }
};

template <typename FunctorType>
void Lexicon::mapAll(FunctorType fn) const {
    for(std::string word : m_allWords) {
        fn(word);
    }
}

#endif
