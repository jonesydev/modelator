'''
Created on Dec 31, 2021

@author: jonesy

get-links-democracy-digest.py

Compile a list of blog post links from each page of the Democracy Digest website.
Each link will be passed to get-text-democracy-digest.py to get the text of that blog post. 
'''

from bs4 import BeautifulSoup
from selenium import webdriver
from selenium.webdriver.common.by import By
from pymongo import MongoClient
from numpy import number
from dns.name import root
from dbus import connection

# Get database connection.
with open("config.xml", "r") as c:
  config = c.read()
  groot = BeautifulSoup(config, features="html.parser")
  tag = groot.mongodb.host
  connection_string = tag.string
  #print(tag.string)
  #print(tag["name"])
  #print(tag["port"])
  
try:
  #client = MongoClient("mongodb://localhost:27017")
  client = MongoClient(connection_string)
  corpus_db = client["corpus"]
  source_col = corpus_db["sources"]
  source_query = {"source" : "Democracy Digest"}
  source_doc = source_col.find_one(source_query)
  source_url = source_doc["source_url"]
  print(source_url)
except Exception:
  print("Could not connect to database.")

options = webdriver.ChromeOptions()
options.add_argument("--ignore-certificate-errors")
options.add_argument("--incognito")

driver = webdriver.Chrome(options=options)
page_url = source_url
#page_url = "https://www.demdigest.org/"

driver.get(page_url)
soup = BeautifulSoup(driver.page_source, "lxml")
links = []
number_of_pages = 1


for i in range(number_of_pages):
  driver.get(page_url)
  soup = BeautifulSoup(driver.page_source, "lxml")
  volume_links = soup.find_all("a", rel = "bookmark")
  next_page = soup.find("a", class_ = "next")
  
  if len(volume_links) > 0:
    for volume_link in volume_links:
      temp_url = volume_link["href"]
      links.append(temp_url)
      print(temp_url)      
  else:
    print(len(volume_links))    
    print("no issues")
    
  print(next_page["href"])
  page_url = next_page["href"]
  driver.find_element(By.PARTIAL_LINK_TEXT, "Next ").click()
