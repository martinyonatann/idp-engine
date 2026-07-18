````markdown
# IDP Engine

> A C++ Intelligent Document Processing (IDP) engine focused on document quality analysis, preprocessing, OCR, and structured data extraction.

## Vision

Build a production-ready IDP engine that can:

- Analyze document quality
- Detect and correct document perspective
- Enhance images for OCR
- Extract structured information from documents
- Support multiple document types (KTP, NPWP, Passport, Invoice, etc)

---

# Development Roadmap

## Phase 1 — Image Loading

**Status:** Completed

### Features

- Load image from file
- Validate image
- Display image information
- Save processed image

### Modules

```text
image/
```

### Implemented

- Image Loader

---

## Phase 2 — Image Quality Analysis

**Status:** Completed

### Modules

```text
quality/
```

### Implemented

- Brightness Analyzer
- Blur Analyzer
- Resolution Analyzer

### Example Output

```text
Brightness
Status : PASS
Value  : 126.4

Blur
Status : PASS
Value  : 542.8

Resolution
Status : PASS
Value  : 660
```

---

## 🚧 Phase 3 — Document Detection

Detect document boundaries inside an image.

### Modules

```text
document/
```

### Planned

- Edge Detection
- Contour Detection
- Largest Contour Selection
- Quadrilateral Detection

---

## 🚧 Phase 4 — Crop

Crop the detected document.

### Modules

```text
image/
```

### Planned

- Crop by Rectangle
- Crop by Four Points

---

## 🚧 Phase 5 — Perspective Correction

Correct skewed document images.

### Modules

```text
document/
```

### Planned

- Perspective Transform
- Warp Perspective

---

## 🚧 Phase 6 — Resize

Resize document while maintaining aspect ratio.

### Modules

```text
image/
```

### Planned

- Resize
- Scale
- Aspect Ratio Preservation

---

## 🚧 Phase 7 — Image Enhancement

Improve image quality before OCR.

### Modules

```text
image/
```

### Planned

- Grayscale
- CLAHE
- Adaptive Threshold
- Gaussian Blur
- Denoise
- Sharpen

Pipeline:

```text
Image
    │
    ▼
Grayscale
    │
    ▼
CLAHE
    │
    ▼
Threshold
    │
    ▼
Sharpen
```

---

## 🚧 Phase 8 — OCR Engine

Extract text from processed documents.

### Modules

```text
ocr/
```

### Planned

- OCR Engine Interface
- Tesseract Integration
- PaddleOCR Integration (Future)
- OCR Result Model

---

## 🚧 Phase 9 — Document Classification

Automatically identify document type.

### Modules

```text
classifier/
```

### Planned

- KTP
- NPWP
- Passport
- Invoice
- Driver License
- Others

---

## 🚧 Phase 10 — Field Extraction

Extract structured information from OCR results.

### Modules

```text
extractor/
```

### Planned

#### KTP

- NIK
- Name
- Address
- Gender
- Religion
- Occupation

#### Invoice

- Invoice Number
- Date
- Supplier
- Total Amount

#### Passport

- Passport Number
- Name
- Nationality
- Expiry Date

---

# Project Structure

```text
include/
└── idp/
    ├── image/
    ├── quality/
    ├── document/
    ├── ocr/
    ├── classifier/
    └── extractor/

src/
└── idp/
    ├── image/
    ├── quality/
    ├── document/
    ├── ocr/
    ├── classifier/
    └── extractor/
```

---

# Design Principles

- Feature-based module organization
- Separate Analyzer and Processor responsibilities
- One class, one responsibility
- Keep APIs simple and extensible
- Avoid premature optimization
- Prefer composition over inheritance

---

# Processing Pipeline

```text
Load Image
    │
    ▼
Quality Analysis
    │
    ▼
Document Detection
    │
    ▼
Crop
    │
    ▼
Perspective Correction
    │
    ▼
Resize
    │
    ▼
Image Enhancement
    │
    ▼
OCR
    │
    ▼
Document Classification
    │
    ▼
Field Extraction
```

---

# Long-Term Goals

- High-performance C++ engine
- Modular architecture
- OCR engine abstraction
- Multi-document support
- Production-ready SDK
- REST/gRPC wrapper
- Cross-platform (Linux, macOS, Windows)
- AI-ready document understanding
````
