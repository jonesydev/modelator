'''
Created on Dec 31, 2021

@author: jonesy

get-text-democracy-digest.py

Is passed a blog post link from get-links-democracy-digest.py.
Returns the text of that blog post.
'''

from bs4 import BeautifulSoup
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from pymongo import MongoClient
import time

source_query = {"source" : "Democracy Digest"}

# Get database connection and perform query.
try:
  client = MongoClient("mongodb://localhost:27017")
  corpus_db = client["corpus"]
  source_col = corpus_db["sources"]
  #source_query = {"source" : "Democracy Digest"}
  source_doc = source_col.find_one(source_query)
  source_url = source_doc["source_url"]  
  filter_col = corpus_db["filters"]
  #filter_query = {"source" : "Democracy Digest"}
  filter_doc = filter_col.find_one(source_query)
  filter_list = filter_doc["list"]
except Exception:
  print("Could not connect to database.")

# Get webdriver.
try:
  options = webdriver.ChromeOptions()
  options.add_argument("--ignore-certificate-errors")
  options.add_argument("--incognito")
  driver = webdriver.Chrome(options=options)
except Exception:
  print("Could not get webdriver.")
    
##############################################
# Everything above this point happens once.
# Everything below happens for each link.
##############################################

#url = "https://www.demdigest.org/memorial-closure-shifts-russia-from-autocracy-to-dictatorship/"
#url = "https://www.demdigest.org/vietnams-pivot-netizens-demand-right-know/"
url = "https://www.demdigest.org/isis-ideology-matters/"

#def create_soup_object(url):
try:
  driver.get(url)
  soup = BeautifulSoup(driver.page_source, "lxml")
  #set_blog_data(soup)
except Exception as err:
  print("Could not create soup object: ", err)

#def set_blog_data(soup):
source = "Democracy Digest"
source_url = "demdigest.org"
title_selector = soup.find("h1", class_ = "entry-title")
text_selector = soup.find_all(["p", "li"], recursive=True)
year_selector = soup.find("time")
title = title_selector.text
year = year_selector.text[-4:]
text = ""
tags = soup.find_all("a", class_ = "tag-cloud-link")
blog_items = []

for item in text_selector:
  if item.text not in filter_list:
    text = text + item.text       
        
blog_data = {
  "source" : source,
  "source_url" : source_url,
  "title" : title,
  "year" : year,
  "text" : text
}

blog_items.append(blog_data)

print(blog_data["source"])
print(blog_data["source_url"])
print(blog_data["title"])
print(blog_data["year"])
print(blog_data["text"])

#create_soup_object(url)
#set_blog_data()
