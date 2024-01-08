import streamlit as st
import pandas as pd
import os
from nltk.tokenize import word_tokenize
from nltk.stem import PorterStemmer
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.metrics.pairwise import linear_kernel
import nltk

nltk.download('punkt')

# Get the current directory of the script
current_directory = os.path.dirname(__file__)

# Construct the path relative to the current directory
file_path = os.path.join(current_directory, 'Medicine_Details.csv')

# Read the CSV file
data = pd.read_csv(file_path)

# Tokenization and stemming
def process_text(text):
    tokens = word_tokenize(text.lower())
    stemmer = PorterStemmer()
    processed_tokens = [stemmer.stem(token) for token in tokens if token.isalnum()]
    return ' '.join(processed_tokens)

# Apply tokenization and stemming to each column
for column in data.columns:
    data[column] = data[column].astype(str).apply(lambda x: process_text(x))

# Create a new DataFrame for displaying processed text
processed_data = data.copy()

# Combine all columns into a single column for TF-IDF
data['combined_text'] = data.apply(lambda row: ' '.join(row), axis=1)

# Create a TF-IDF vectorizer
tfidf_vectorizer = TfidfVectorizer()

# Fit and transform the data to generate the TF-IDF matrix
tfidf_matrix = tfidf_vectorizer.fit_transform(data['combined_text'])

# Fungsi untuk melakukan pencarian menggunakan TF-IDF
def tfidf_search(query):
    processed_query = process_text(query)
    query_vector = tfidf_vectorizer.transform([processed_query])

    # Calculate cosine similarity between query and documents
    cosine_similarities = linear_kernel(query_vector, tfidf_matrix).flatten()
    related_docs_indices = cosine_similarities.argsort()[::-1]
    return data.iloc[related_docs_indices]

# Streamlit web interface
st.title('Search Engine medicine')

# User input query
query = st.text_input('Masukkan kata kunci pencarian:', '')

# Display processed text
st.subheader('Hasil Text Processing:')

if not query:
    st.write("Masukkan kata kunci pencarian untuk melihat hasil text processing.")
else:
    processed_query = process_text(query)
    st.write("Query yang diproses:", processed_query)

# Search when button is pressed
if st.button('Cari'):
    # Search results
    results = tfidf_search(query)
    # Display search results in a table
    st.subheader('Hasil Pencarian:')
    st.write(results)
